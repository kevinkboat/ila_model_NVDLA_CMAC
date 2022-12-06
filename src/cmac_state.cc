// File: cmac_state.cc

#include <ilang/ilang++.h>
#include <cmac_config.h>

namespace ilang {

    void DefineCMACState(Ila& m){

        //////////////////////////////////////////////////////////////////////////////
        ///  REGISTER STATES
        //////////////////////////////////////////////////////////////////////////////
        
        m.NewBvState("cmac_a_state", 2)
        m.NewBvState("cmac_b_state", 2)

        //////////////////////////////////////////////////////////////////////////////
        ///  REGISTER CONFIGS
        //////////////////////////////////////////////////////////////////////////////

        // 0x7000
        m.NewBvState(NVDLA_CMAC_A_S_STATUS_0, NVDLA_CMAC_A_S_STATUS_WIDTH)
        m.NewBvState(NVDLA_CMAC_A_S_STATUS_1, NVDLA_CMAC_A_S_STATUS_WIDTH)

        // 0x7004
        m.NewBvState(NVDLA_CMAC_A_S_PRODUCER, NVDLA_CMAC_A_S_PRODUCER_WIDTH)
        m.NewBvState(NVDLA_CMAC_A_S_CONSUMER, NVDLA_CMAC_A_S_CONSUMER_WIDTH)

        // 0x8000
        m.NewBvState(NVDLA_CMAC_B_S_STATUS_0, NVDLA_CMAC_B_S_STATUS_WIDTH)
        m.NewBvState(NVDLA_CMAC_B_S_STATUS_1, NVDLA_CMAC_B_S_STATUS_WIDTH)

        // 0x8004
        m.NewBvState(NVDLA_CMAC_B_S_PRODUCER, NVDLA_CMAC_B_S_PRODUCER_WIDTH)
        m.NewBvState(NVDLA_CMAC_B_S_CONSUMER, NVDLA_CMAC_B_S_CONSUMER_WIDTH)

        // Duplicated Register Group
        for (auto i = 0; i < 2; i++) {
            // 0x7008
            m.NewBvState("group" + (std::to_string(i)) + "_" + NVDLA_CMAC_A_D_OP_ENABLE, NVDLA_CMAC_A_D_OP_ENABLE_WIDTH)
            // 0x700c
            m.NewBvState("group" + (std::to_string(i)) + "_" + NVDLA_CMAC_A_D_MISC_CFG, NVDLA_CMAC_A_D_MISC_CFG_WIDTH)

            // 0x8008
            m.NewBvState("group" + (std::to_string(i)) + "_" + NVDLA_CMAC_B_D_OP_ENABLE, NVDLA_CMAC_B_D_OP_ENABLE_WIDTH)
            // 0x800c
            m.NewBvState("group" + (std::to_string(i)) + "_" + NVDLA_CMAC_B_D_MISC_CFG, NVDLA_CMAC_B_D_MISC_CFG_WIDTH)
        }

        //////////////////////////////////////////////////////////////////////////////
        ///  MAC ARRAY STATES
        //////////////////////////////////////////////////////////////////////////////

        for (auto i = 0; i < 16; i++) {
            m.NewBvState("cmac_weight_" + (std::to_string(i)), NVDLA_CMAC_WT_BLOCK_SIZE_INT16)
        }

    }


} // namespace ilang 