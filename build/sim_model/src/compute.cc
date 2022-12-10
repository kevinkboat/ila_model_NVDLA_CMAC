#include <iomanip>
#include <cmac.h>
#include <chrono>
static int instr_cntr = 0;
int cmac::GetInstrCntr() {
  return instr_cntr;
}
void cmac::IncrementInstrCntr() {
  instr_cntr++;
}
void cmac::LogInstrSequence(const std::string& instr_name, const long int& exec_time) {
  instr_log << "Instr No. " << std::setw(8) << GetInstrCntr() << '\t';
  instr_log << instr_name << " is activated\t";
  instr_log << "exec_time: " << exec_time * 1e-3 << " us\n";
  IncrementInstrCntr();
}
static bool g_initialized = false;
void cmac::compute() {
if (!g_initialized) {
  setup_initial_condition();
  g_initialized = true;
}
cmac_cmac_a_csb_addr = cmac_cmac_a_csb_addr_in.read();
cmac_cmac_a_csb_data = cmac_cmac_a_csb_data_in.read();
cmac_cmac_a_csb_write = cmac_cmac_a_csb_write_in.read();
cmac_cmac_a_csb_vld = cmac_cmac_a_csb_vld_in.read();
cmac_csc_weights_int16 = cmac_csc_weights_int16_in.read();
cmac_csc_data_int16 = cmac_csc_data_int16_in.read();
cmac_status = cmac_status_in.read();
cmac_output_ack = cmac_output_ack_in.read();
cmac_done = cmac_done_in.read();
if (valid_cmac() && decode_cmac_cmac_a_set_producer()) {
#ifdef ILATOR_PROFILING
  auto start = std::chrono::high_resolution_clock::now();
#endif
  update_cmac_cmac_a_set_producer();
  
#ifdef ILATOR_PROFILING
  auto stop = std::chrono::high_resolution_clock::now();
  auto exec_time = std::chrono::duration_cast<std::chrono::nanoseconds>(stop-start).count();
  LogInstrSequence("cmac_a_set_producer", exec_time);
#endif
}
if (valid_cmac() && decode_cmac_cmac_a_set_start_group0()) {
#ifdef ILATOR_PROFILING
  auto start = std::chrono::high_resolution_clock::now();
#endif
  update_cmac_cmac_a_set_start_group0();
  
#ifdef ILATOR_PROFILING
  auto stop = std::chrono::high_resolution_clock::now();
  auto exec_time = std::chrono::duration_cast<std::chrono::nanoseconds>(stop-start).count();
  LogInstrSequence("cmac_a_set_start_group0", exec_time);
#endif
}
if (valid_cmac() && decode_cmac_cmac_a_set_config_group0()) {
#ifdef ILATOR_PROFILING
  auto start = std::chrono::high_resolution_clock::now();
#endif
  update_cmac_cmac_a_set_config_group0();
  
#ifdef ILATOR_PROFILING
  auto stop = std::chrono::high_resolution_clock::now();
  auto exec_time = std::chrono::duration_cast<std::chrono::nanoseconds>(stop-start).count();
  LogInstrSequence("cmac_a_set_config_group0", exec_time);
#endif
}
if (valid_cmac() && decode_cmac_Start()) {
#ifdef ILATOR_PROFILING
  auto start = std::chrono::high_resolution_clock::now();
#endif
  update_cmac_Start();
  
#ifdef ILATOR_PROFILING
  auto stop = std::chrono::high_resolution_clock::now();
  auto exec_time = std::chrono::duration_cast<std::chrono::nanoseconds>(stop-start).count();
  LogInstrSequence("Start", exec_time);
#endif
}
if (valid_cmac() && decode_cmac_Pend2Done()) {
#ifdef ILATOR_PROFILING
  auto start = std::chrono::high_resolution_clock::now();
#endif
  update_cmac_Pend2Done();
  
#ifdef ILATOR_PROFILING
  auto stop = std::chrono::high_resolution_clock::now();
  auto exec_time = std::chrono::duration_cast<std::chrono::nanoseconds>(stop-start).count();
  LogInstrSequence("Pend2Done", exec_time);
#endif
}
if (valid_cmac() && decode_cmac_Done2Idle_0()) {
#ifdef ILATOR_PROFILING
  auto start = std::chrono::high_resolution_clock::now();
#endif
  update_cmac_Done2Idle_0();
  
#ifdef ILATOR_PROFILING
  auto stop = std::chrono::high_resolution_clock::now();
  auto exec_time = std::chrono::duration_cast<std::chrono::nanoseconds>(stop-start).count();
  LogInstrSequence("Done2Idle_0", exec_time);
#endif
}
if (valid_cmac() && decode_cmac_cmac_load_weights()) {
#ifdef ILATOR_PROFILING
  auto start = std::chrono::high_resolution_clock::now();
#endif
  update_cmac_cmac_load_weights();
  
#ifdef ILATOR_PROFILING
  auto stop = std::chrono::high_resolution_clock::now();
  auto exec_time = std::chrono::duration_cast<std::chrono::nanoseconds>(stop-start).count();
  LogInstrSequence("cmac_load_weights", exec_time);
#endif
}
if (valid_cmac() && decode_cmac_cmac_compute_partial_sums()) {
#ifdef ILATOR_PROFILING
  auto start = std::chrono::high_resolution_clock::now();
#endif
  update_cmac_cmac_compute_partial_sums();
  
#ifdef ILATOR_PROFILING
  auto stop = std::chrono::high_resolution_clock::now();
  auto exec_time = std::chrono::duration_cast<std::chrono::nanoseconds>(stop-start).count();
  LogInstrSequence("cmac_compute_partial_sums", exec_time);
#endif
}
while (1) {
  int schedule_counter = 0;
  if (schedule_counter == 0) {
    break;
  }
}
}
