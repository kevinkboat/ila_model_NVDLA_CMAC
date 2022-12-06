// File: cmac_instrs.cc

#include <ilang/ilang++.h>
#include <cmac_config.h>

namespace ilang {

    void DefineCMACInstrs(Ila& m) {

        //////////////////////////////////////////////////////////////////////////////
        ///  INITIAL CONDITIONS
        //////////////////////////////////////////////////////////////////////////////

        // m.AddInit(m.state(NVDLA_CMAC_A_S_STATUS_0) == BvConst(0, 2));
        // m.AddInit(m.state(NVDLA_CMAC_A_S_STATUS_1) == BvConst(0, 2));
        // m.AddInit(m.state(NVDLA_CMAC_B_S_STATUS_0) == BvConst(0, 2));
        // m.AddInit(m.state(NVDLA_CMAC_B_S_STATUS_1) == BvConst(0, 2));

        //////////////////////////////////////////////////////////////////////////////
        ///  CSB TRIGGERED OPS
        //////////////////////////////////////////////////////////////////////////////

        // CMAC_A
        auto cmac_a_csb_addr = Extract(Concat(m.input("cmac_a_csb_addr"), BvConst(0,2)), 11, 0);
        auto cmac_a_csb_valid = (m.state("cmac_a_csb_rdy") == BvConst(1,1)) & (m.input("cmac_a_csb_data_vld") == BvConst(1,1));
        auto cmac_a_csb_write = m.input("cmac_a_csb_write") == BvConst(1,1);
        auto cmac_a_group0_unset = m.state(GetVarName("group0_", NVDLA_CMAC_A_D_OP_ENABLE)) == BvConst(0,1);
        auto cmac_a_group1_unset = m.state(GetVarName("group1_", NVDLA_CMAC_A_D_OP_ENABLE)) == BvConst(0,1);
        auto cmac_a_producer = m.state(NVDLA_CMAC_A_S_PRODUCER);
        auto cmac_a_consumer = m.state(NVDLA_CMAC_A_S_CONSUMER);
        auto cmac_a_state = m.state("cmac_a_state");        
        
        // CMAC_B
        auto cmac_b_csb_addr = Extract(Concat(m.input("cmac_b_csb_addr"), BvConst(0,2)), 11, 0);
        auto cmac_b_csb_valid = (m.state("cmac_b_csb_rdy") == BvConst(1,1)) & (m.input("cmac_b_csb_data_vld") == BvConst(1,1));
        auto cmac_b_csb_write = m.input("cmac_b_csb_write") == BvConst(1,1);
        auto cmac_b_group0_unset = m.state(GetVarName("group0_", NVDLA_CMAC_B_D_OP_ENABLE)) == BvConst(0,1);
        auto cmac_b_group1_unset = m.state(GetVarName("group1_", NVDLA_CMAC_B_D_OP_ENABLE)) == BvConst(0,1);
        auto cmac_b_producer = m.state(NVDLA_CMAC_B_S_PRODUCER);
        auto cmac_b_consumer = m.state(NVDLA_CMAC_B_S_CONSUMER);
        auto cmac_b_state = m.state("cmac_b_state");
        
        // Note: csb_adr is a 3 hex digit number

        // Set Producer
        
        { // CMAC_A Set Producer (addr:004)
            auto instr = m.NewInstr("cmac_a_set_producer");
            instr.SetDecode(cmac_a_csb_addr == 0x004 & cmac_a_csb_valid & cmac_a_csb_write);
            instr.SetUpdate(cmac_a_producer, Extract(m.input("cmac_a_csb_data"), 0, 0));
        }

        { // CMAC_B Set Producer (addr:004)
            auto instr = m.NewInstr("cmac_b_set_producer");
            instr.SetDecode(cmac_b_csb_addr == 0x004 & cmac_b_csb_valid & cmac_b_csb_write);
            instr.SetUpdate(cmac_b_producer, Extract(m.input("cmac_b_csb_data"), 0, 0));
        }

        // Set Start Group
        // Note: NVDLA_CMAC_A_D_OP_ENABLE and NVDLA_CMAC_B_D_OP_ENABLE are distinct strings
        
        { // CMAC_A Set Start Group 0 (addr:008)
            auto instr = m.NewInstr("cmac_a_set_start_group0");
            instr.SetDecode(cmac_a_csb_addr == 0x008 & cmac_a_csb_valid & cmac_a_csb_write & cmac_a_producer == BvConst(0,1) & cmac_a_group0_unset);
            instr.SetUpdate(m.state(GetVarName("group0_", NVDLA_CMAC_A_D_OP_ENABLE)), Extract(m.input("cmac_a_csb_data"), 0, 0));
        }

        { // CMAC_A Set Start Group 1 (addr:008)
            auto instr = m.NewInstr("cmac_a_set_start_group1");
            instr.SetDecode(cmac_a_csb_addr == 0x008 & cmac_a_csb_valid & cmac_a_csb_write & cmac_a_producer == BvConst(1,1) & cmac_a_group1_unset);
            instr.SetUpdate(m.state(GetVarName("group1_", NVDLA_CMAC_A_D_OP_ENABLE)), Extract(m.input("cmac_a_csb_data"), 0, 0));
        }

        { // CMAC_B Set Start Group 0 (addr:008)
            auto instr = m.NewInstr("cmac_b_set_start_group0");
            instr.SetDecode(cmac_b_csb_addr == 0x008 & cmac_b_csb_valid & cmac_b_csb_write & cmac_b_producer == BvConst(0,1) & cmac_b_group0_unset);
            instr.SetUpdate(m.state(GetVarName("group0_", NVDLA_CMAC_B_D_OP_ENABLE)), Extract(m.input("cmac_b_csb_data"), 0, 0));
        }

        { // CMAC_B Set Start Group 1 (addr:008)
            auto instr = m.NewInstr("cmac_b_set_start_group1");
            instr.SetDecode(cmac_b_csb_addr == 0x008 & cmac_b_csb_valid & cmac_b_csb_write & cmac_b_producer == BvConst(1,1) & cmac_b_group1_unset);
            instr.SetUpdate(m.state(GetVarName("group1_", NVDLA_CMAC_B_D_OP_ENABLE)), Extract(m.input("cmac_b_csb_data"), 0, 0));
        }

        // Set Configuration
        
        { // CMAC_A Set Config Group 0 (addr:00c)
            auto instr = m.NewInstr("cmac_a_set_config_group0");
            instr.SetDecode(cmac_a_csb_addr == 0x00c & cmac_a_csb_valid & cmac_a_csb_write & cmac_a_producer == BvConst(0,1) & cmac_a_group0_unset);
            instr.SetUpdate(m.state(GetVarName("group0_", NVDLA_CMAC_A_D_MISC_CFG)), Extract(m.input("cmac_a_csb_data"), 0, 0));
        }

        { // CMAC_A Set Config Group 1 (addr:00c)
            auto instr = m.NewInstr("cmac_a_set_config_group1");
            instr.SetDecode(cmac_a_csb_addr == 0x00c & cmac_a_csb_valid & cmac_a_csb_write & cmac_a_producer == BvConst(1,1) & cmac_a_group1_unset);
            instr.SetUpdate(m.state(GetVarName("group1_", NVDLA_CMAC_A_D_MISC_CFG)), Extract(m.input("cmac_a_csb_data"), 0, 0));
        }

        { // CMAC_B Set Config Group 0 (addr:00c)
            auto instr = m.NewInstr("cmac_b_set_config_group0");
            instr.SetDecode(cmac_b_csb_addr == 0x00c & cmac_b_csb_valid & cmac_b_csb_write & cmac_b_producer == BvConst(0,1) & cmac_b_group0_unset);
            instr.SetUpdate(m.state(GetVarName("group0_", NVDLA_CMAC_B_D_MISC_CFG)), Extract(m.input("cmac_b_csb_data"), 0, 0));
        }

        { // CMAC_B Set Config Group 1 (addr:00c)
            auto instr = m.NewInstr("cmac_b_set_config_group1");
            instr.SetDecode(cmac_b_csb_addr == 0x00c & cmac_b_csb_valid & cmac_b_csb_write & cmac_b_producer == BvConst(1,1) & cmac_b_group1_unset);
            instr.SetUpdate(m.state(GetVarName("group1_", NVDLA_CMAC_B_D_MISC_CFG)), Extract(m.input("cmac_b_csb_data"), 0, 0));
        }

        //////////////////////////////////////////////////////////////////////////////
        ///  MAC CELL OPS
        //////////////////////////////////////////////////////////////////////////////


        auto stripe_ops_left = m.NewBvState("stripe_ops_left", 5) // upper limit of stripe operation is 32 
        auto data_block = m.NewBvState("data_block", NVDLA_CMAC_WT_BLOCK_SIZE_INT16)

        { // Load weights
            auto instr = m.NewInstr("cmac_load_weights");
            instr.SetDecode();
            
            for (auto i = 0; i < 16; i++) {
                auto lo = NVDLA_CMAC_WT_BLOCK_SIZE_INT16 * i;
                auto hi = lo + NVDLA_CMAC_WT_BLOCK_SIZE_INT16 - 1;
                instr.SetUpdate(m.state("cmac_weight_" + (std::to_string(i))), Extract(m.input("csc_weights_int16"), hi, lo));
            }

            // update indicator that op is done
            instr.SetUpdate("stripe_ops_left", m.state("csc_data_int16") / NVDLA_CMAC_WT_BLOCK_SIZE_INT16);
            
            // extract first data block
            instr.SetUpdate("data_block", Extract(m.state("csc_data_int16"), NVDLA_CMAC_WT_BLOCK_SIZE_INT16 - 1, 0));
            
        }

        { // Compute partial sums
            auto instr = m.NewInstr("cmac_compute_partial_sums")

            // need variable to help figure out where to collect data from stripe.
            // cmac_load_weights should resest this variable.

            instr.SetDecode(Ugt(stripe_ops_left, 0));

            auto data_block = Extract(m.state("csc_data_int16"), NVDLA_CMAC_WT_BLOCK_SIZE_INT16 - 1, 0));

            for (auto i = 0; i < 16; i++) {
                // get weight for each MAC cell
                auto wt = m.state("cmac_weight_" + (std::to_string(i)))
                
                // perform convolution
                auto sum = BvConst(0, 16)
                for (auto j = 0; j < 64; j++) {
                    auto lo = 16 * j;
                    auto hi = lo + 16 - 1;
                    sum = sum + (Extract(wt, hi, lo) * Extract(data, hi, lo))
                }

                instr.SetUpdate(m.state("partial_sum_" + (std::to_string(i))), sum);
            }

            // update counter

        }

    }


} // namespace ilang