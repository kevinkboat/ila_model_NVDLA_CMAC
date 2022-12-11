// File: cmac_instrs.cc

#include <ilang/ilang++.h>
#include <cmac_config.h>
#include <cmath>

namespace ilang {

    void DefineCMACInstrs(Ila& m) {

        //////////////////////////////////////////////////////////////////////////////
        ///  INITIAL CONDITIONS
        //////////////////////////////////////////////////////////////////////////////

        // m.AddInit(m.state(NVDLA_CMAC_A_S_STATUS_0) == BvConst(0, 2));
        // m.AddInit(m.state(NVDLA_CMAC_A_S_STATUS_1) == BvConst(0, 2));
        // m.AddInit(m.state(NVDLA_CMAC_B_S_STATUS_0) == BvConst(0, 2));
        // m.AddInit(m.state(NVDLA_CMAC_B_S_STATUS_1) == BvConst(0, 2));
        m.AddInit(m.state("cmac_a_csb_rdy") == BvConst(1,1));
        m.AddInit(m.state("partial_sum_0") == BvConst(12,16));      
        m.AddInit(m.state("partial_sum_2") == Extract(m.input("cmac_a_csb_addr"), 15, 0));      

        m.AddInit(m.state("cmac_a_state") == IDLE);
        m.AddInit(m.state(NVDLA_CMAC_A_S_PRODUCER) == BvConst(0, NVDLA_CMAC_A_S_PRODUCER_WIDTH));
        m.AddInit(m.state(NVDLA_CMAC_A_S_CONSUMER) == BvConst(0, NVDLA_CMAC_A_S_CONSUMER_WIDTH));
        m.AddInit(m.state(GetVarName("group0_", NVDLA_CMAC_A_D_OP_ENABLE)) == BvConst(0, NVDLA_CMAC_A_D_OP_ENABLE_WIDTH));

        //////////////////////////////////////////////////////////////////////////////
        ///  CSB TRIGGERED OPS
        //////////////////////////////////////////////////////////////////////////////

        // CMAC_A
        auto cmac_a_csb_addr = Extract(m.input("cmac_a_csb_addr"), 11, 0);
        auto cmac_a_csb_valid = (m.state("cmac_a_csb_rdy") == BvConst(1,1)) & (m.input("cmac_a_csb_vld") == BvConst(1,1));
        auto cmac_a_csb_write = m.input("cmac_a_csb_write") == BvConst(1,1);
        auto cmac_a_group0_unset = m.state(GetVarName("group0_", NVDLA_CMAC_A_D_OP_ENABLE)) == BvConst(0,1);
        auto cmac_a_producer = m.state(NVDLA_CMAC_A_S_PRODUCER);
        auto cmac_a_consumer = m.state(NVDLA_CMAC_A_S_CONSUMER);
        auto cmac_a_state = m.state("cmac_a_state");        

        auto done_with_computation = m.NewBoolState("done_with_computation");
        auto cmac_partial_sum_rdy = m.NewBoolState("cmac_partial_sum_rdy");
        auto step_num = m.NewBvState("step_num", 6); // upper limit of stripe operation is 32 (+ 1 operation for load weights)
        auto data_block = m.input("csc_data_int16");
        // auto cmac_partial_sum_rdy = m.NewBoolState("cmac_partial_sum_rdy");
        // m.AddInit(m.state("step_num") == BvConst(0, 6));

        { // CMAC_A Set Producer (addr:004)
            auto instr = m.NewInstr("cmac_a_set_producer");
            instr.SetDecode(cmac_a_csb_addr == 0x004 & cmac_a_csb_valid & cmac_a_csb_write);
            instr.SetUpdate(cmac_a_producer, Extract(m.input("cmac_a_csb_data"), 0, 0));
            instr.SetUpdate(m.state("partial_sum_1"), BvConst(7,16));
        }

        { // CMAC_A Set Start Group 0 (addr:008)
            auto instr = m.NewInstr("cmac_a_set_start_group0");
            instr.SetDecode(cmac_a_csb_addr == 0x008 & cmac_a_csb_valid & cmac_a_csb_write & cmac_a_producer == BvConst(0,1) & cmac_a_group0_unset);
            instr.SetUpdate(m.state(GetVarName("group0_", NVDLA_CMAC_A_D_OP_ENABLE)), Extract(m.input("cmac_a_csb_data"), 0, 0));
            instr.SetUpdate(m.state("partial_sum_2"), BvConst(2,16));
    
        }      
        
        { // CMAC_A Set Config Group 0 (addr:00c)
            auto instr = m.NewInstr("cmac_a_set_config_group0");
            instr.SetDecode(cmac_a_csb_addr == 0x00c & cmac_a_csb_valid & cmac_a_csb_write & cmac_a_producer == BvConst(0,1) & cmac_a_group0_unset);
            instr.SetUpdate(m.state(GetVarName("group0_", NVDLA_CMAC_A_D_MISC_CFG)), Extract(m.input("cmac_a_csb_data"), 0, 0));
            instr.SetUpdate(m.state("partial_sum_15"), BvConst(15,16));
        }

        { // Start from IDLE
            auto instr = m.NewInstr("Start");
            auto group0_ok = cmac_a_consumer == BvConst(0,1) & m.state(GetVarName("group0_", NVDLA_CMAC_A_D_OP_ENABLE)) == BvConst(1,1);
            // auto group1_ok = consumer == BvConst(1,1) & m.state(GetVarName("group1_", NVDLA_CMAC_A_D_OP_ENABLE)) == BvConst(1,1);
            // instr.SetDecode(csc_state == IDLE & (group0_ok | group1_ok));

            instr.SetDecode(cmac_a_state == IDLE & group0_ok);
            instr.SetUpdate(cmac_a_state, BUSY);
            instr.SetUpdate(m.state("partial_sum_15"), BvConst(15,16));

            instr.SetUpdate(m.state("step_num"), BvConst(1, 6));
        }

        { // Pend2Done - waiting for output to be acknowledged before proceeding
            auto instr = m.NewInstr("Pend2Done");
            instr.SetDecode(cmac_a_state == PEND & m.input("output_ack"));
            instr.SetUpdate(cmac_a_state, Ite(done_with_computation, DONE, BUSY));
        }

        { // Done2Idle0
            auto instr = m.NewInstr("Done2Idle_0");
            instr.SetDecode((cmac_a_state == DONE) & m.input("done") & (cmac_a_consumer == BvConst(0,1)));
            
            // instr.SetDecode(cmac_a_state == DONE & m.input("done") & cmac_a_consumer == BvConst(0,1));
            // instr.SetUpdate(cmac_a_consumer, BvConst(1,1));

            // reset done_with_computation
            instr.SetUpdate(cmac_a_state, IDLE);
            instr.SetUpdate(done_with_computation, BoolConst(false));
            instr.SetUpdate(m.state(GetVarName("group0_", NVDLA_CMAC_A_D_OP_ENABLE)), BvConst(0,1));
        }

        //////////////////////////////////////////////////////////////////////////////
        ///  MAC CELL OPS
        //////////////////////////////////////////////////////////////////////////////

        { // Load weights
            auto instr = m.NewInstr("cmac_load_weights");
            instr.SetDecode((cmac_a_state == BUSY) & (m.state("step_num") == BvConst(1, 6)));
            
            for (auto i = 0; i < 16; i++) {
                auto lo = NVDLA_CMAC_WT_BLOCK_SIZE_INT16 * i;
                auto hi = lo + NVDLA_CMAC_WT_BLOCK_SIZE_INT16 - 1;
                instr.SetUpdate(m.state("cmac_weight_" + (std::to_string(i))), Extract(m.input("csc_weights_int16"), hi, lo));
            }

            instr.SetUpdate(m.state("step_num"), BvConst(2, 6));
        }

        { // Compute partial sums
            auto instr = m.NewInstr("cmac_compute_partial_sums");

            instr.SetDecode((cmac_a_state == BUSY) & (m.state("step_num") > BvConst(1, 6)));

            for (auto i = 0; i < 16; i++) {
                // get weight for each MAC cell
                auto wt = m.state("cmac_weight_" + (std::to_string(i)));
                
                // perform convolution
                auto sum = BvConst(0, 16);
                for (auto j = 0; j < 64; j++) {
                    auto lo = 16 * j;
                    auto hi = lo + 16 - 1;
                    sum = sum + Extract(wt, hi, lo) * Extract(data_block, hi, lo);
                }

                instr.SetUpdate(m.state("partial_sum_" + (std::to_string(i))), sum);
            }

            data_block = data_block >> NVDLA_CMAC_WT_BLOCK_SIZE_INT16;

            // update counter
            auto step_num = m.state("step_num");
            done_with_computation = step_num == (m.input("csc_data_int16").bit_width() / NVDLA_CMAC_WT_BLOCK_SIZE_INT16) + 1;
            instr.SetUpdate(m.state("done_with_computation"), done_with_computation);
            instr.SetUpdate(m.state("step_num"), Ite(done_with_computation, BvConst(0, 6), step_num + 1));
            instr.SetUpdate(m.state("cmac_a_state"), PEND);
        }




        // auto cmac_a_group1_unset = m.state(GetVarName("group1_", NVDLA_CMAC_A_D_OP_ENABLE)) == BvConst(0,1);

        // // CMAC_B
        // auto cmac_b_csb_addr = Extract(Concat(m.input("cmac_b_csb_addr"), BvConst(0,2)), 11, 0);
        // auto cmac_b_csb_valid = (m.state("cmac_b_csb_rdy") == BvConst(1,1)) & (m.input("cmac_b_csb_vld") == BvConst(1,1));
        // auto cmac_b_csb_write = m.input("cmac_b_csb_write") == BvConst(1,1);
        // auto cmac_b_group0_unset = m.state(GetVarName("group0_", NVDLA_CMAC_B_D_OP_ENABLE)) == BvConst(0,1);
        // auto cmac_b_group1_unset = m.state(GetVarName("group1_", NVDLA_CMAC_B_D_OP_ENABLE)) == BvConst(0,1);
        // auto cmac_b_producer = m.state(NVDLA_CMAC_B_S_PRODUCER);
        // auto cmac_b_consumer = m.state(NVDLA_CMAC_B_S_CONSUMER);
        // auto cmac_b_state = m.state("cmac_b_state");

        // { // CMAC_B Set Producer (addr:004)
        //     auto instr = m.NewInstr("cmac_b_set_producer");
        //     instr.SetDecode(cmac_b_csb_addr == 0x004 & cmac_b_csb_valid & cmac_b_csb_write);
        //     instr.SetUpdate(cmac_b_producer, Extract(m.input("cmac_b_csb_data"), 0, 0));
        // }

        // { // CMAC_A Set Start Group 1 (addr:008)
        //     auto instr = m.NewInstr("cmac_a_set_start_group1");
        //     instr.SetDecode(cmac_a_csb_addr == 0x008 & cmac_a_csb_valid & cmac_a_csb_write & cmac_a_producer == BvConst(1,1) & cmac_a_group1_unset);
        //     instr.SetUpdate(m.state(GetVarName("group1_", NVDLA_CMAC_A_D_OP_ENABLE)), Extract(m.input("cmac_a_csb_data"), 0, 0));
        // }

        // { // CMAC_B Set Start Group 0 (addr:008)
        //     auto instr = m.NewInstr("cmac_b_set_start_group0");
        //     instr.SetDecode(cmac_b_csb_addr == 0x008 & cmac_b_csb_valid & cmac_b_csb_write & cmac_b_producer == BvConst(0,1) & cmac_b_group0_unset);
        //     instr.SetUpdate(m.state(GetVarName("group0_", NVDLA_CMAC_B_D_OP_ENABLE)), Extract(m.input("cmac_b_csb_data"), 0, 0));
        // }

        // { // CMAC_B Set Start Group 1 (addr:008)
        //     auto instr = m.NewInstr("cmac_b_set_start_group1");
        //     instr.SetDecode(cmac_b_csb_addr == 0x008 & cmac_b_csb_valid & cmac_b_csb_write & cmac_b_producer == BvConst(1,1) & cmac_b_group1_unset);
        //     instr.SetUpdate(m.state(GetVarName("group1_", NVDLA_CMAC_B_D_OP_ENABLE)), Extract(m.input("cmac_b_csb_data"), 0, 0));
        // }

        // { // CMAC_A Set Config Group 1 (addr:00c)
        //     auto instr = m.NewInstr("cmac_a_set_config_group1");
        //     instr.SetDecode(cmac_a_csb_addr == 0x00c & cmac_a_csb_valid & cmac_a_csb_write & cmac_a_producer == BvConst(1,1) & cmac_a_group1_unset);
        //     instr.SetUpdate(m.state(GetVarName("group1_", NVDLA_CMAC_A_D_MISC_CFG)), Extract(m.input("cmac_a_csb_data"), 0, 0));
        // }

        // { // CMAC_B Set Config Group 0 (addr:00c)
        //     auto instr = m.NewInstr("cmac_b_set_config_group0");
        //     instr.SetDecode(cmac_b_csb_addr == 0x00c & cmac_b_csb_valid & cmac_b_csb_write & cmac_b_producer == BvConst(0,1) & cmac_b_group0_unset);
        //     instr.SetUpdate(m.state(GetVarName("group0_", NVDLA_CMAC_B_D_MISC_CFG)), Extract(m.input("cmac_b_csb_data"), 0, 0));
        // }

        // { // CMAC_B Set Config Group 1 (addr:00c)
        //     auto instr = m.NewInstr("cmac_b_set_config_group1");
        //     instr.SetDecode(cmac_b_csb_addr == 0x00c & cmac_b_csb_valid & cmac_b_csb_write & cmac_b_producer == BvConst(1,1) & cmac_b_group1_unset);
        //     instr.SetUpdate(m.state(GetVarName("group1_", NVDLA_CMAC_B_D_MISC_CFG)), Extract(m.input("cmac_b_csb_data"), 0, 0));
        // }
    }

    //////////////////////////////////////////////////////////////////////////////
    ///  HELPER FUNCTIONS
    //////////////////////////////////////////////////////////////////////////////
    
    // // Returns true if bit in specified index is 1, false if 0. Idea is to encode boolean 
    // // variables in the width of bitvectors.
    // bool _SelectBit(const ExprRef& bv, const int& idx){
    //     auto b = Ite(SelectBit(bv, idx) == BvConst(1,1), BvConst(1,1), BvConst(1,2));
    //     return b.bit_width() != -1;
    // }

    // // get int representation of the bitvector
    // int _BvToInt(const ExprRef& bv){
    //     auto len = bv.bit_width();      // should be limited to the max size of an int
    //     int num = 0;
    //     for (int i = 0; i < len; i++){
    //         // Binary to Decimal conversion
    //         if (_SelectBit(bv, i)){
    //             num += static_cast<int>(std::pow(2, i));
    //         }
    //     }
    //     return num;
    // }



} // namespace ilang