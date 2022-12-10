#include <cmac.h>
bool cmac::decode_cmac_cmac_a_set_start_group1() {
sc_biguint<2> local_var_1 = 0;
univ_var_1 = (sc_biguint<22>(cmac_cmac_a_csb_addr), sc_biguint<2>(local_var_1));
auto local_var_3 = univ_var_1.range(11, 0);
sc_biguint<12> local_var_4 = 8;
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
sc_biguint<1> local_var_19 = 1;
bool local_var_20 = (cmac_cmac_a_s_producer == local_var_19);
bool local_var_21 = (local_var_17 & local_var_20);
sc_biguint<1> local_var_23 = 0;
bool local_var_24 = (cmac_group1_cmac_a_d_op_en == local_var_23);
bool local_var_25 = (local_var_21 & local_var_24);
auto& univ_var_4 = local_var_25;
return univ_var_4;
}
void cmac::update_cmac_cmac_a_set_start_group1() {
auto local_var_1 = cmac_cmac_a_csb_data.range(0, 0);
auto local_var_1_nxt_holder = local_var_1;
cmac_group1_cmac_a_d_op_en = local_var_1_nxt_holder;
#ifdef ILATOR_VERBOSE
instr_update_log << "No." << std::dec << GetInstrCntr() << '\t' << "cmac_a_set_start_group1 state updates:" << std::endl;
instr_update_log << "    cmac_group1_cmac_a_d_op_en => " << std::hex << "0x" << cmac_group1_cmac_a_d_op_en << std::endl; 
instr_update_log << std::endl;
#endif
}
