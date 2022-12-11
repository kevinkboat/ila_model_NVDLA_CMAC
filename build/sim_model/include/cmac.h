#include <fstream>
#include <systemc.h>
#include <map>
#include <unordered_map>
struct MemAddrHashFunc {
  std::size_t operator() (int const& addr) const noexcept {
    return addr;
  }
};
SC_MODULE(cmac) {
  std::ofstream instr_log;
  std::ofstream instr_update_log;
  int GetInstrCntr();
  void IncrementInstrCntr();
  void LogInstrSequence(const std::string& instr_name, const long int&);
  sc_in<sc_biguint<1>> cmac_done_in;
  sc_biguint<1> cmac_done;
  sc_in<sc_biguint<1>> cmac_output_ack_in;
  sc_biguint<1> cmac_output_ack;
  sc_in<sc_biguint<8>> cmac_status_in;
  sc_biguint<8> cmac_status;
  sc_in<sc_biguint<1024>> cmac_csc_data_int16_in;
  sc_biguint<1024> cmac_csc_data_int16;
  sc_in<sc_biguint<16384>> cmac_csc_weights_int16_in;
  sc_biguint<16384> cmac_csc_weights_int16;
  sc_in<sc_biguint<1>> cmac_cmac_a_csb_vld_in;
  sc_biguint<1> cmac_cmac_a_csb_vld;
  sc_in<sc_biguint<1>> cmac_cmac_a_csb_write_in;
  sc_biguint<1> cmac_cmac_a_csb_write;
  sc_in<sc_biguint<32>> cmac_cmac_a_csb_data_in;
  sc_biguint<32> cmac_cmac_a_csb_data;
  sc_in<sc_biguint<22>> cmac_cmac_a_csb_addr_in;
  sc_biguint<22> cmac_cmac_a_csb_addr;
  sc_biguint<6> cmac_step_num;
  bool cmac_cmac_partial_sum_rdy;
  bool cmac_done_with_computation;
  sc_biguint<1024> cmac_cmac_weight_15;
  sc_biguint<1024> cmac_cmac_weight_14;
  sc_biguint<1024> cmac_cmac_weight_13;
  sc_biguint<1024> cmac_cmac_weight_12;
  sc_biguint<1024> cmac_cmac_weight_11;
  sc_biguint<1024> cmac_cmac_weight_10;
  sc_biguint<1024> cmac_cmac_weight_9;
  sc_biguint<1024> cmac_cmac_weight_8;
  sc_biguint<1024> cmac_cmac_weight_7;
  sc_biguint<1024> cmac_cmac_weight_6;
  sc_biguint<1024> cmac_cmac_weight_5;
  sc_biguint<1024> cmac_cmac_weight_4;
  sc_biguint<1024> cmac_cmac_weight_3;
  sc_biguint<1024> cmac_cmac_weight_2;
  sc_biguint<1024> cmac_cmac_weight_1;
  sc_biguint<1024> cmac_cmac_weight_0;
  sc_biguint<16> cmac_partial_sum_10;
  sc_biguint<16> cmac_partial_sum_9;
  sc_biguint<16> cmac_partial_sum_8;
  sc_biguint<16> cmac_partial_sum_7;
  sc_biguint<16> cmac_partial_sum_6;
  sc_biguint<16> cmac_partial_sum_5;
  sc_biguint<16> cmac_partial_sum_4;
  sc_biguint<16> cmac_partial_sum_3;
  sc_biguint<16> cmac_partial_sum_2;
  sc_biguint<16> cmac_partial_sum_1;
  sc_biguint<16> cmac_partial_sum_0;
  sc_biguint<1> cmac_cmac_a_csb_data_vld;
  sc_biguint<1> cmac_cmac_a_csb_rdy;
  sc_biguint<16> cmac_partial_sum_11;
  sc_biguint<16> cmac_partial_sum_12;
  sc_biguint<16> cmac_partial_sum_13;
  sc_biguint<16> cmac_partial_sum_14;
  sc_biguint<16> cmac_partial_sum_15;
  sc_biguint<8> cmac_status_to_cacc;
  sc_biguint<1> cmac_wait_for_ack;
  sc_biguint<2> cmac_cmac_a_state;
  sc_biguint<2> cmac_cmac_a_s_status0;
  sc_biguint<2> cmac_cmac_a_s_status1;
  sc_biguint<1> cmac_cmac_a_s_producer;
  sc_biguint<1> cmac_cmac_a_s_consumer;
  sc_biguint<1> cmac_group0_cmac_a_d_op_en;
  sc_biguint<32> cmac_group0_cmac_a_d_misc_cfg;
  sc_biguint<1> cmac_group1_cmac_a_d_op_en;
  sc_biguint<32> cmac_group1_cmac_a_d_misc_cfg;
  void compute();
  bool decode_cmac_Done2Idle_0();
  bool decode_cmac_Pend2Done();
  bool decode_cmac_Start();
  bool decode_cmac_cmac_a_set_config_group0();
  bool decode_cmac_cmac_a_set_producer();
  bool decode_cmac_cmac_a_set_start_group0();
  bool decode_cmac_cmac_compute_partial_sums();
  bool decode_cmac_cmac_load_weights();
  void setup_initial_condition();
  void update_cmac_Done2Idle_0();
  void update_cmac_Pend2Done();
  void update_cmac_Start();
  void update_cmac_cmac_a_set_config_group0();
  void update_cmac_cmac_a_set_producer();
  void update_cmac_cmac_a_set_start_group0();
  void update_cmac_cmac_compute_partial_sums();
  void update_cmac_cmac_load_weights();
  bool valid_cmac();
  SC_HAS_PROCESS(cmac);
  cmac(sc_module_name name_) : sc_module(name_) {
    SC_METHOD(compute);
    sensitive << cmac_done_in << cmac_output_ack_in << cmac_status_in << cmac_csc_data_int16_in << cmac_csc_weights_int16_in << cmac_cmac_a_csb_vld_in << cmac_cmac_a_csb_write_in << cmac_cmac_a_csb_data_in << cmac_cmac_a_csb_addr_in;
  }
};
