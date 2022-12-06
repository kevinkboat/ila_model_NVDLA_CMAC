// File: cmac_input.cc

#include <ilang/ilang++.h>
#include <cmac_config.h>

namespace ilang {

     void DefineCMACOutput(Ila& m) {
        
        //////////////////////////////////////////////////////////////////////////////
        ///  TO CSB
        //////////////////////////////////////////////////////////////////////////////

        // CMAC_A
        m.NewBvState("cmac_a_csb_rdy", 1);
        m.NewBvState("cmac_a_csb_data_vld", 1)

        // CMAC_B
        m.NewBvState("cmac_b_csb_rdy", 1);
        m.NewBvState("cmac_b_csb_data_vld", 1)

        //////////////////////////////////////////////////////////////////////////////
        ///  TO CACC 
        //////////////////////////////////////////////////////////////////////////////

        // MAC cell outputs
        for (auto i = 0; i < 16; i++) {
            m.NewBvState("partial_sum_" + (std::to_string(i)), 16)
        }

        m.NewBvState("status", NVDLA_CMAC_PIPELINE_STATUS_WIDTH) 

    }

} // namespace ilang 