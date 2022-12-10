#include <cmac.h>
bool cmac::decode_cmac_Pend2Done() {
sc_biguint<2> local_var_1 = 1;
bool local_var_2 = (cmac_cmac_a_state == local_var_1);
sc_biguint<1> local_var_4 = 1;
bool local_var_5 = (cmac_output_ack == local_var_4);
bool local_var_6 = (local_var_2 & local_var_5);
auto& univ_var_6 = local_var_6;
return univ_var_6;
}
void cmac::update_cmac_Pend2Done() {
sc_biguint<2> local_var_1 = 3;
sc_biguint<2> local_var_2 = 2;
auto local_var_3 = (cmac_done_with_computation) ? local_var_1 : local_var_2;
auto local_var_3_nxt_holder = local_var_3;
cmac_cmac_a_state = local_var_3_nxt_holder;
#ifdef ILATOR_VERBOSE
instr_update_log << "No." << std::dec << GetInstrCntr() << '\t' << "Pend2Done state updates:" << std::endl;
instr_update_log << "    cmac_cmac_a_state => " << std::hex << "0x" << cmac_cmac_a_state << std::endl; 
instr_update_log << std::endl;
#endif
}
