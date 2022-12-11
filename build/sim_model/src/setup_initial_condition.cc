#include <cmac.h>
void cmac::setup_initial_condition() {
cmac_cmac_a_csb_addr = 0;
cmac_cmac_a_csb_rdy = 1;
cmac_partial_sum_0 = 12;
cmac_partial_sum_2 = 0;
cmac_cmac_a_state = 0;
cmac_cmac_a_s_producer = 0;
cmac_cmac_a_s_consumer = 0;
cmac_group0_cmac_a_d_op_en = 0;
}
