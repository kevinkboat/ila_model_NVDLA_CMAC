// File: cmac_config.h

#ifndef NVDLA_CMAC_CONFIG_H
#define NVDLA_CMAC_CONFIG_H

namespace ilang {

inline std::string GetVarName(const std::string& var_name0, const std::string& var_name1) {
 
  return var_name0 + var_name1;
}


//////////////////////////////////////////////////////////////////////////////
///  CONFIG REGISTERS
//////////////////////////////////////////////////////////////////////////////

// CMAC_A REGISTERS

// 0x7000
#define NVDLA_CMAC_A_S_STATUS_0 "cmac_a_s_status0"
#define NVDLA_CMAC_A_S_STATUS_1 "cmac_a_s_status1"
#define NVDLA_CMAC_A_S_STATUS_WIDTH 2

// 0x7004
#define NVDLA_CMAC_A_S_PRODUCER "cmac_a_s_producer"
#define NVDLA_CMAC_A_S_CONSUMER "cmac_a_s_consumer"
#define NVDLA_CMAC_A_S_PRODUCER_WIDTH 1
#define NVDLA_CMAC_A_S_CONSUMER_WIDTH 1

// 0x7008
#define NVDLA_CMAC_A_D_OP_ENABLE "cmac_a_d_op_en"
#define NVDLA_CMAC_A_D_OP_ENABLE_WIDTH 1

// 0x700c
#define NVDLA_CMAC_A_D_MISC_CFG "cmac_a_d_misc_cfg"
#define NVDLA_CMAC_A_D_MISC_CFG_WIDTH 32


// CMAC_B REGISTERS

// 0x8000
#define NVDLA_CMAC_B_S_STATUS_0 "cmac_b_s_status0"
#define NVDLA_CMAC_B_S_STATUS_1 "cmac_b_s_status1"
#define NVDLA_CMAC_B_S_STATUS_WIDTH 2

// 0x8004
#define NVDLA_CMAC_B_S_PRODUCER "cmac_b_s_producer"
#define NVDLA_CMAC_B_S_CONSUMER "cmac_b_s_consumer"
#define NVDLA_CMAC_B_S_PRODUCER_WIDTH 1
#define NVDLA_CMAC_B_S_CONSUMER_WIDTH 1

// 0x8008
#define NVDLA_CMAC_B_D_OP_ENABLE "cmac_b_d_op_en"
#define NVDLA_CMAC_B_D_OP_ENABLE_WIDTH 1

// 0x800c
#define NVDLA_CMAC_B_D_MISC_CFG "cmac_b_d_misc_cfg"
#define NVDLA_CMAC_B_D_MISC_CFG_WIDTH 32

//////////////////////////////////////////////////////////////////////////////
/// REGISTERS STATES
//////////////////////////////////////////////////////////////////////////////

#define IDLE BvConst(0,2)
#define PEND BvConst(1,2)
#define BUSY BvConst(2,2)
#define DONE BvConst(3,2)

//////////////////////////////////////////////////////////////////////////////
///  CONSTANTS
//////////////////////////////////////////////////////////////////////////////

#define NVDLA_CMAC_WT_BLOCK_SIZE_INT16  1024    // 64 * 16 bits = 1024 bits
#define NVDLA_CMAC_WT_BLOCK_SIZE_INT8   512     // 64 * 8 bits = 512 bits


#define NVDLA_CMAC_PIPELINE_STATUS_WIDTH  8     // Update


} // namespace ilang

#endif // NVDLA_CMAC_CONFIG_H