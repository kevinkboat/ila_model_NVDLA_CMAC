#include <cmac.h>
bool cmac::decode_cmac_cmac_a_set_producer() {
auto local_var_1 = cmac_cmac_a_csb_addr.range(11, 0);
sc_biguint<12> local_var_2 = 4;
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
auto& univ_var_1 = local_var_15;
return univ_var_1;
}
void cmac::update_cmac_cmac_a_set_producer() {
auto local_var_1 = cmac_cmac_a_csb_data.range(0, 0);
auto local_var_1_nxt_holder = local_var_1;
sc_biguint<16> local_var_2 = 7;
auto local_var_2_nxt_holder = local_var_2;
cmac_cmac_a_s_producer = local_var_1_nxt_holder;
cmac_partial_sum_1 = local_var_2_nxt_holder;
#ifdef ILATOR_VERBOSE
instr_update_log << "No." << std::dec << GetInstrCntr() << '\t' << "cmac_a_set_producer state updates:" << std::endl;
instr_update_log << "    cmac_cmac_a_s_producer => " << std::hex << "0x" << cmac_cmac_a_s_producer << std::endl; 
instr_update_log << "    cmac_partial_sum_1 => " << std::hex << "0x" << cmac_partial_sum_1 << std::endl; 
instr_update_log << std::endl;
#endif
}
