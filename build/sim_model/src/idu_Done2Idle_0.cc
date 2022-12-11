#include <cmac.h>
bool cmac::decode_cmac_Done2Idle_0() {
sc_biguint<2> local_var_1 = 3;
bool local_var_2 = (cmac_cmac_a_state == local_var_1);
sc_biguint<1> local_var_4 = 1;
bool local_var_5 = (cmac_done == local_var_4);
bool local_var_6 = (local_var_2 & local_var_5);
sc_biguint<1> local_var_8 = 0;
bool local_var_9 = (cmac_cmac_a_s_consumer == local_var_8);
bool local_var_10 = (local_var_6 & local_var_9);
auto& univ_var_6 = local_var_10;
return univ_var_6;
}
void cmac::update_cmac_Done2Idle_0() {
sc_biguint<2> local_var_0 = 0;
auto local_var_0_nxt_holder = local_var_0;
bool local_var_1 = false;
auto local_var_1_nxt_holder = local_var_1;
sc_biguint<1> local_var_2 = 0;
auto local_var_2_nxt_holder = local_var_2;
cmac_cmac_a_state = local_var_0_nxt_holder;
cmac_done_with_computation = local_var_1_nxt_holder;
cmac_group0_cmac_a_d_op_en = local_var_2_nxt_holder;
#ifdef ILATOR_VERBOSE
instr_update_log << "No." << std::dec << GetInstrCntr() << '\t' << "Done2Idle_0 state updates:" << std::endl;
instr_update_log << "    cmac_cmac_a_state => " << std::hex << "0x" << cmac_cmac_a_state << std::endl; 
instr_update_log << "    cmac_done_with_computation => " << std::hex << "0x" << cmac_done_with_computation << std::endl; 
instr_update_log << "    cmac_group0_cmac_a_d_op_en => " << std::hex << "0x" << cmac_group0_cmac_a_d_op_en << std::endl; 
instr_update_log << std::endl;
#endif
}
