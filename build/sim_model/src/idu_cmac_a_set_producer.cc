#include <cmac.h>
bool cmac::decode_cmac_cmac_a_set_producer() {
sc_biguint<2> local_var_1 = 0;
univ_var_1 = (sc_biguint<22>(cmac_cmac_a_csb_addr), sc_biguint<2>(local_var_1));
auto local_var_3 = univ_var_1.range(11, 0);
sc_biguint<12> local_var_4 = 4;
bool local_var_5 = (local_var_3 == local_var_4);
sc_biguint<1> local_var_7 = 1;
bool local_var_8 = (cmac_cmac_a_csb_rdy == local_var_7);
sc_biguint<1> local_var_10 = 1;
bool local_var_11 = (cmac_cmac_a_csb_vld == local_var_10);
bool local_var_12 = (local_var_8 & local_var_11);
bool local_var_13 = (local_var_5 & local_var_12);
sc_biguint<1> local_var_15 = 1;
bool local_var_16 = (cmac_cmac_a_csb_write == local_var_15);
bool local_var_17 = (local_var_13 & local_var_16);
auto& univ_var_2 = local_var_17;
return univ_var_2;
}
void cmac::update_cmac_cmac_a_set_producer() {
auto local_var_1 = cmac_cmac_a_csb_data.range(0, 0);
auto local_var_1_nxt_holder = local_var_1;
cmac_cmac_a_s_producer = local_var_1_nxt_holder;
#ifdef ILATOR_VERBOSE
instr_update_log << "No." << std::dec << GetInstrCntr() << '\t' << "cmac_a_set_producer state updates:" << std::endl;
instr_update_log << "    cmac_cmac_a_s_producer => " << std::hex << "0x" << cmac_cmac_a_s_producer << std::endl; 
instr_update_log << std::endl;
#endif
}
