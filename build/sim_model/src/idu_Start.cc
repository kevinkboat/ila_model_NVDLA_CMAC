#include <cmac.h>
bool cmac::decode_cmac_Start() {
sc_biguint<2> local_var_1 = 0;
bool local_var_2 = (cmac_cmac_a_state == local_var_1);
sc_biguint<1> local_var_4 = 0;
bool local_var_5 = (cmac_cmac_a_s_consumer == local_var_4);
sc_biguint<1> local_var_7 = 1;
bool local_var_8 = (cmac_group0_cmac_a_d_op_en == local_var_7);
bool local_var_9 = (local_var_5 & local_var_8);
bool local_var_10 = (local_var_2 & local_var_9);
auto& univ_var_4 = local_var_10;
return univ_var_4;
}
void cmac::update_cmac_Start() {
sc_biguint<2> local_var_0 = 2;
auto local_var_0_nxt_holder = local_var_0;
sc_biguint<16> local_var_1 = 15;
auto local_var_1_nxt_holder = local_var_1;
sc_biguint<6> local_var_2 = 1;
auto local_var_2_nxt_holder = local_var_2;
cmac_cmac_a_state = local_var_0_nxt_holder;
cmac_partial_sum_15 = local_var_1_nxt_holder;
cmac_step_num = local_var_2_nxt_holder;
#ifdef ILATOR_VERBOSE
instr_update_log << "No." << std::dec << GetInstrCntr() << '\t' << "Start state updates:" << std::endl;
instr_update_log << "    cmac_cmac_a_state => " << std::hex << "0x" << cmac_cmac_a_state << std::endl; 
instr_update_log << "    cmac_partial_sum_15 => " << std::hex << "0x" << cmac_partial_sum_15 << std::endl; 
instr_update_log << "    cmac_step_num => " << std::hex << "0x" << cmac_step_num << std::endl; 
instr_update_log << std::endl;
#endif
}
