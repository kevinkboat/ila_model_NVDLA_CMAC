#include <systemc>
#include <iostream>
#include <sstream>
#include <fstream>
#include <sstream>
#include <iomanip>

#include "nlohmann/json.hpp"
#include "cmac.h"

using json = nlohmann::json;

std::string file_in;
std::string file_out;

// Module for reading inputs into ILA model
SC_MODULE(Source) {
  sc_in<bool> clk{"clk"};
  
  sc_out<sc_biguint<22>> cmac_cmac_a_csb_addr;
  sc_out<sc_biguint<32>> cmac_cmac_a_csb_data;
  sc_out<sc_biguint<1>> cmac_cmac_a_csb_write;    
  sc_out<sc_biguint<1>> cmac_cmac_a_csb_vld;

  sc_out<sc_biguint<16384>> cmac_csc_weights_int16;
  sc_out<sc_biguint<1024>> cmac_csc_data_int16;
  sc_out<sc_biguint<8>> cmac_status;

  sc_out<sc_biguint<1>> cmac_output_ack;
  sc_out<sc_biguint<1>> cmac_done;
  
  sc_out< sc_biguint<1> > input_done;

  SC_CTOR(Source) {
    SC_THREAD(source_input);
    sensitive << clk.pos();
  }

  void source_input() {
    // reset the port
    cmac_cmac_a_csb_addr = "0x004";
    cmac_cmac_a_csb_data = 0;
    cmac_cmac_a_csb_write = 0;    
    cmac_cmac_a_csb_vld = 0;
    cmac_csc_weights_int16 = 0;
    cmac_csc_data_int16 = 0;
    cmac_status = 0;
    cmac_output_ack = 0;
    cmac_done = 0;

    input_done = 0;
    
    // read program fragment from file
    std::ifstream fin;
    fin.open(file_in, ios::in);
    
    json cmd_seq;
    cmd_seq = json::parse(fin);

    // Pass the command to the ports
    for (size_t i = 0; i < cmd_seq["program fragment"].size(); i++) {
    //   for (size_t j = 0; j < 16; j++) {
    //     sdp_cacc_data[j] = cmd_seq["program fragment"][i]["cacc_data_" + std::to_string(j)].get<int>();
    //   }
    // }

    cmac_cmac_a_csb_addr = std::stoi((cmd_seq["program fragment"][i]["cmac_cmac_a_csb_addr"].get<std::string>()).c_str(), nullptr, 16);
    
    cmac_cmac_a_csb_data = cmd_seq["program fragment"][i]["cmac_cmac_a_csb_data"].get<int>();
    cmac_cmac_a_csb_write = cmd_seq["program fragment"][i]["cmac_cmac_a_csb_write"].get<int>();    
    cmac_cmac_a_csb_vld = cmd_seq["program fragment"][i]["cmac_cmac_a_csb_vld"].get<int>();
    // cmac_csc_weights_int16 = cmd_seq["program fragment"][i]["cmac_csc_weights_int16"].get<int>();
    cmac_csc_weights_int16 = std::stoi((cmd_seq["program fragment"][i]["cmac_csc_weights_int16"].get<std::string>()).c_str(), nullptr, 16);
    cmac_csc_data_int16 = cmd_seq["program fragment"][i]["cmac_csc_data_int16"].get<int>();
    cmac_status = cmd_seq["program fragment"][i]["cmac_status"].get<int>();
    cmac_output_ack = cmd_seq["program fragment"][i]["cmac_output_ack"].get<int>();
    cmac_done = cmd_seq["program fragment"][i]["cmac_done"].get<int>();

    wait(10, SC_NS);
    
    }

    input_done = 1;
    std::cout << "read_file" << std::flush;

  }

};

SC_MODULE(testbench) {
  // SC_HAS_PROCESS(testbench);
  cmac cmac_inst;
  Source src;

  sc_clock clk;

  sc_out<sc_biguint<22>> cmac_cmac_a_csb_addr_signal{"cmac_cmac_a_csb_addr_signal"};
  sc_out<sc_biguint<32>> cmac_cmac_a_csb_data_signal{"cmac_cmac_a_csb_data_signal"};
  sc_out<sc_biguint<1>> cmac_cmac_a_csb_write_signal{"cmac_cmac_a_csb_write_signal"};    
  sc_out<sc_biguint<1>> cmac_cmac_a_csb_vld_signal{"cmac_cmac_a_csb_vld_signal"};

  sc_out<sc_biguint<16384>> cmac_csc_weights_int16_signal{"cmac_csc_weights_int16_signal"};
  sc_out<sc_biguint<1024>> cmac_csc_data_int16_signal{"cmac_csc_data_int16_signal"};
  sc_out<sc_biguint<8>> cmac_status_signal{"cmac_status_signal"};

  sc_out<sc_biguint<1>> cmac_output_ack_signal{"cmac_output_ack_signal"};
  sc_out<sc_biguint<1>> cmac_done_signal{"cmac_done_signal"};
  
  sc_out< sc_biguint<1> > input_done{"input_done"};

  SC_CTOR(testbench) :
    clk("clk", 1, SC_NS),
    cmac_inst("cmac_inst"),
    src("source")
  {
    // Read in signals from the prog_frag file
    src.clk(clk);

    src.cmac_cmac_a_csb_addr(cmac_cmac_a_csb_addr_signal);
    src.cmac_cmac_a_csb_data(cmac_cmac_a_csb_data_signal);
    src.cmac_cmac_a_csb_write(cmac_cmac_a_csb_write_signal);    
    src.cmac_cmac_a_csb_vld(cmac_cmac_a_csb_vld_signal);
    src.cmac_csc_weights_int16(cmac_csc_weights_int16_signal);
    src.cmac_csc_data_int16(cmac_csc_data_int16_signal);
    src.cmac_status(cmac_status_signal);
    src.cmac_output_ack(cmac_output_ack_signal);
    src.cmac_done(cmac_done_signal);

    src.input_done(input_done);

    // Link with the sdp.h SystemC model

    cmac_inst.cmac_cmac_a_csb_addr_in(cmac_cmac_a_csb_addr_signal);
    cmac_inst.cmac_cmac_a_csb_data_in(cmac_cmac_a_csb_data_signal);
    cmac_inst.cmac_cmac_a_csb_write_in(cmac_cmac_a_csb_write_signal);    
    cmac_inst.cmac_cmac_a_csb_vld_in(cmac_cmac_a_csb_vld_signal);
    cmac_inst.cmac_csc_weights_int16_in(cmac_csc_weights_int16_signal);
    cmac_inst.cmac_csc_data_int16_in(cmac_csc_data_int16_signal);
    cmac_inst.cmac_status_in(cmac_status_signal);
    cmac_inst.cmac_output_ack_in(cmac_output_ack_signal);
    cmac_inst.cmac_done_in(cmac_done_signal);

    SC_THREAD(run);
  }

  // Run the SystemC simuation and log outputs
  void run() {
    cmac_inst.instr_log.open("instr_log_conv.txt", ofstream::out | ofstream::trunc);
    cmac_inst.instr_update_log.open("instr_update_log_conv.txt", ios::out | ios::trunc);

    std::cout << "start running" << std::endl;
    std::cout << "*********** simulation start ***********" << std::endl;
    wait(10, SC_NS);

    while (input_done == 0) {
		  std::cout << "current simulation time: " << '\t' << sc_time_stamp() << "\r" << std::flush;
      wait(10, SC_NS);
    }
    wait(1000, SC_NS);

    // Log final outputs
    std::ofstream fout;
    fout.open(file_out, ios::out | ios::trunc);
 
    fout << "    addr => " << std::hex << "0x" << cmac_inst.cmac_cmac_a_csb_addr << std::endl; 
    fout << "    step_num => " << std::dec << cmac_inst.cmac_step_num << std::endl; 
    fout << "    cmac_cmac_a_state => " << std::dec << cmac_inst.cmac_cmac_a_state << std::endl; 
    fout << "    done_with_computation => " << std::boolalpha << cmac_inst.cmac_done_with_computation << std::endl; 
    fout << "    cmac_cmac_partial_sum_rdy => " << std::boolalpha << cmac_inst.cmac_cmac_partial_sum_rdy << std::endl; 
    fout << std::endl; 

    fout << "    cmac_csc_data_int16 => " << std::hex << "0x" << cmac_inst.cmac_csc_data_int16 << std::endl; 
    fout << std::endl; 

    fout << "    cmac_partial_sum_0 => " << std::hex << "0x" << cmac_inst.cmac_partial_sum_0 << std::endl; 
    fout << "    cmac_partial_sum_1 => " << std::hex << "0x" << cmac_inst.cmac_partial_sum_1 << std::endl; 
    fout << "    cmac_partial_sum_2 => " << std::hex << "0x" << cmac_inst.cmac_partial_sum_2 << std::endl; 
    fout << "    cmac_partial_sum_3 => " << std::hex << "0x" << cmac_inst.cmac_partial_sum_3 << std::endl; 
    fout << "    cmac_partial_sum_4 => " << std::hex << "0x" << cmac_inst.cmac_partial_sum_4 << std::endl; 
    fout << "    cmac_partial_sum_5 => " << std::hex << "0x" << cmac_inst.cmac_partial_sum_5 << std::endl; 
    fout << "    cmac_partial_sum_6 => " << std::hex << "0x" << cmac_inst.cmac_partial_sum_6 << std::endl; 
    fout << "    cmac_partial_sum_7 => " << std::hex << "0x" << cmac_inst.cmac_partial_sum_7 << std::endl; 
    fout << "    cmac_partial_sum_8 => " << std::hex << "0x" << cmac_inst.cmac_partial_sum_8 << std::endl; 
    fout << "    cmac_partial_sum_9 => " << std::hex << "0x" << cmac_inst.cmac_partial_sum_9 << std::endl; 
    fout << "    cmac_partial_sum_10 => " << std::hex << "0x" << cmac_inst.cmac_partial_sum_10 << std::endl; 
    fout << "    cmac_partial_sum_11 => " << std::hex << "0x" << cmac_inst.cmac_partial_sum_11 << std::endl; 
    fout << "    cmac_partial_sum_12 => " << std::hex << "0x" << cmac_inst.cmac_partial_sum_12 << std::endl; 
    fout << "    cmac_partial_sum_13 => " << std::hex << "0x" << cmac_inst.cmac_partial_sum_13 << std::endl; 
    fout << "    cmac_partial_sum_14 => " << std::hex << "0x" << cmac_inst.cmac_partial_sum_14 << std::endl; 
    fout << "    cmac_partial_sum_15 => " << std::hex << "0x" << cmac_inst.cmac_partial_sum_15 << std::endl; 
    fout << std::endl; 

    fout << "    cmac_cmac_weight_0 => " << std::hex << "0x" << cmac_inst.cmac_cmac_weight_0 << std::endl; 
    fout << "    cmac_cmac_weight_1 => " << std::hex << "0x" << cmac_inst.cmac_cmac_weight_1 << std::endl; 
    fout << "    cmac_cmac_weight_2 => " << std::hex << "0x" << cmac_inst.cmac_cmac_weight_2 << std::endl; 
    fout << "    cmac_cmac_weight_3 => " << std::hex << "0x" << cmac_inst.cmac_cmac_weight_3 << std::endl; 
    fout << "    cmac_cmac_weight_4 => " << std::hex << "0x" << cmac_inst.cmac_cmac_weight_4 << std::endl; 
    fout << "    cmac_cmac_weight_5 => " << std::hex << "0x" << cmac_inst.cmac_cmac_weight_5 << std::endl; 
    fout << "    cmac_cmac_weight_6 => " << std::hex << "0x" << cmac_inst.cmac_cmac_weight_6 << std::endl; 
    fout << "    cmac_cmac_weight_7 => " << std::hex << "0x" << cmac_inst.cmac_cmac_weight_7 << std::endl; 
    fout << "    cmac_cmac_weight_8 => " << std::hex << "0x" << cmac_inst.cmac_cmac_weight_8 << std::endl; 
    fout << "    cmac_cmac_weight_9 => " << std::hex << "0x" << cmac_inst.cmac_cmac_weight_9 << std::endl; 
    fout << "    cmac_cmac_weight_10 => " << std::hex << "0x" << cmac_inst.cmac_cmac_weight_10 << std::endl; 
    fout << "    cmac_cmac_weight_11 => " << std::hex << "0x" << cmac_inst.cmac_cmac_weight_11 << std::endl; 
    fout << "    cmac_cmac_weight_12 => " << std::hex << "0x" << cmac_inst.cmac_cmac_weight_12 << std::endl; 
    fout << "    cmac_cmac_weight_13 => " << std::hex << "0x" << cmac_inst.cmac_cmac_weight_13 << std::endl; 
    fout << "    cmac_cmac_weight_14 => " << std::hex << "0x" << cmac_inst.cmac_cmac_weight_14 << std::endl; 
    fout << "    cmac_cmac_weight_15 => " << std::hex << "0x" << cmac_inst.cmac_cmac_weight_15 << std::endl;
    

    fout.close();
    std::cout << "outputs have been stored at " << file_out << std::endl;

    wait(100000, SC_NS);
    std::cout << '\n' << std::endl;
    std::cout << "************* sc_stop **************" << std::endl;

    cmac_inst.instr_log.close();
    sc_stop(); 

  }
};

int sc_main(int argc, char *argv[]) {
  if (argc != 3) {
      std::cout << "Usage: my_driver [prog_frag_in_path] [result_out_dump_path]" << std::endl;
      return 0;
  } else {
      file_in = argv[1];
      file_out = argv[2];
  }

  // Dummy ports
  sc_signal <sc_biguint<22>> cmac_cmac_a_csb_addr_main;
  sc_signal <sc_biguint<32>> cmac_cmac_a_csb_data_main;
  sc_signal <sc_biguint<1>> cmac_cmac_a_csb_write_main;    
  sc_signal <sc_biguint<1>> cmac_cmac_a_csb_vld_main;
  sc_signal <sc_biguint<16384>> cmac_csc_weights_int16_main;
  sc_signal <sc_biguint<1024>> cmac_csc_data_int16_main;
  sc_signal <sc_biguint<8>> cmac_status_main;
  sc_signal <sc_biguint<1>> cmac_output_ack_main;
  sc_signal <sc_biguint<1>> cmac_done_main;
  sc_signal < sc_biguint<1> > input_done_main;

  // Begin simulation
  std::cout << "test start" << std::endl;
  testbench tb("tb");

  // Linking to dummy ports
  tb.cmac_cmac_a_csb_addr_signal(cmac_cmac_a_csb_addr_main);
  tb.cmac_cmac_a_csb_data_signal(cmac_cmac_a_csb_data_main);
  tb.cmac_cmac_a_csb_write_signal(cmac_cmac_a_csb_write_main);    
  tb.cmac_cmac_a_csb_vld_signal(cmac_cmac_a_csb_vld_main);
  tb.cmac_csc_weights_int16_signal(cmac_csc_weights_int16_main);
  tb.cmac_csc_data_int16_signal(cmac_csc_data_int16_main);
  tb.cmac_status_signal(cmac_status_main);
  tb.cmac_output_ack_signal(cmac_output_ack_main);
  tb.cmac_done_signal(cmac_done_main);

  tb.input_done(input_done_main);

  sc_start();

  return 0;

}

