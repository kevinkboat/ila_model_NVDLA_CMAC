// File: cmac_input.cc

#include <ilang/ilang++.h>
#include <cmac_config.h>

namespace ilang {

    void DefineCMACInput(Ila& m){

        //////////////////////////////////////////////////////////////////////////////
        ///  FROM CSB
        //////////////////////////////////////////////////////////////////////////////

        // Note CMAC_A and CMAC_B have their own CSB interfaces

        // CSB_A Group        
        m.NewBvInput("cmac_a_csb_addr", 22); // Address is 16 bits, aligned to word boundary. So why is size 22?
        m.NewBvInput("cmac_a_csb_data", 32);
        m.NewBvInput("cmac_a_csb_write", 1);
        m.NewBvInput("cmac_a_csb_vld", 1);

        // CSB_B Group
        m.NewBvInput("cmac_b_csb_addr", 22);
        m.NewBvInput("cmac_b_csb_data", 32);
        m.NewBvInput("cmac_b_csb_write", 1);
        m.NewBvInput("cmac_b_csb_vld", 1);

        //////////////////////////////////////////////////////////////////////////////
        ///  FROM CSC
        //////////////////////////////////////////////////////////////////////////////
        
        m.NewBvInput("csc_weights_int16", 16 * NVDLA_CMAC_WT_BLOCK_SIZE_INT16);
        m.NewBvInput("csc_data_int16", 1 * NVDLA_CMAC_WT_BLOCK_SIZE_INT16);        // will be multiple of 1024
        m.NewBvInput("status", NVDLA_CMAC_PIPELINE_STATUS_WIDTH);
    }

} // namespace ilang 