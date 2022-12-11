#include <cmac.h>
bool cmac::decode_cmac_cmac_a_set_start_group0() {
auto local_var_1 = cmac_cmac_a_csb_addr.range(11, 0);
sc_biguint<12> local_var_2 = 8;
bool local_var_3 = (local_var_1 == local_var_2);
sc_biguint<1> local_var_5 = 1;
bool local_var_6 = (cmac_cmac_a_csb_rdy == local_var_5);
sc_biguint<1> local_var_8 = 1;
bool local_var_9 = (cmac_cmac_a_csb_vld == local_var_8);
bool local_var_10 = (local_var_6 & local_var_9);
bool local_var_11 = (local_var_3 & local_var_10);
sc_biguint<1> local_var_13 = 1;
bool local_var_14 = (cmac_cmac_a_csb_write == local_var_13);
bool local_var_15 = (local_var_11 & local_var_14);
sc_biguint<1> local_var_17 = 0;
bool local_var_18 = (cmac_cmac_a_s_producer == local_var_17);
bool local_var_19 = (local_var_15 & local_var_18);
sc_biguint<1> local_var_21 = 0;
bool local_var_22 = (cmac_group0_cmac_a_d_op_en == local_var_21);
bool local_var_23 = (local_var_19 & local_var_22);
auto& univ_var_2 = local_var_23;
return univ_var_2;
}
void cmac::update_cmac_cmac_a_set_start_group0() {
auto local_var_1 = cmac_cmac_a_csb_data.range(0, 0);
auto local_var_1_nxt_holder = local_var_1;
sc_biguint<16> local_var_2 = 2;
auto local_var_2_nxt_holder = local_var_2;
cmac_group0_cmac_a_d_op_en = local_var_1_nxt_holder;
cmac_partial_sum_2 = local_var_2_nxt_holder;
#ifdef ILATOR_VERBOSE
instr_update_log << "No." << std::dec << GetInstrCntr() << '\t' << "cmac_a_set_start_group0 state updates:" << std::endl;
instr_update_log << "    cmac_group0_cmac_a_d_op_en => " << std::hex << "0x" << cmac_group0_cmac_a_d_op_en << std::endl; 
instr_update_log << "    cmac_partial_sum_2 => " << std::hex << "0x" << cmac_partial_sum_2 << std::endl; 
instr_update_log << std::endl;
#endif
}
