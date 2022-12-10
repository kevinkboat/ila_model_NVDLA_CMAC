#include <systemc>
#include <iostream>
#include <sstream>
#include <fstream>
#include <sstream>
#include <iomanip>

#include "nlohmann/json.hpp"
#include "hlscnn.h"
#define FMT_HEADER_ONLY
#include "fmt/format.h"

// headers for converter
#include <ac_int.h>
#include <ac_fixed.h>
#include <ac_math.h>

typedef ac_fixed<16 , 9 , true, AC_TRN, AC_SAT> conv_activation_t;

using json = nlohmann::json;

std::string file_in;
std::string file_out;

SC_MODULE(Source) {
  sc_in<bool> clk{"clk"};

  sc_out< sc_biguint<1> > hlscnn_if_wr;
  sc_out< sc_biguint<1> > hlscnn_if_rd;
  sc_out< sc_biguint<32> > hlscnn_addr_in;
  sc_out< sc_biguint<8> > hlscnn_data_in[16];

  sc_out< sc_biguint<1> > input_done;

  SC_CTOR(Source) {
    SC_THREAD(source_input);
    sensitive << clk.pos();
  }

  void source_input() {
    // reset the port
    hlscnn_if_wr = 0;
    hlscnn_if_rd = 0;
    hlscnn_addr_in = 0;
    for (auto i = 0; i < 16; i++) {
      hlscnn_data_in[i] = 0;
    }

    input_done = 0;
    // read program fragment from file
    std::ifstream fin;
    fin.open(file_in, ios::in);
    
    //parse the json file
    json cmd_seq;
    fin >> cmd_seq;
    std::string data_format;

    // pass the command to the ports
    for (int i = 0; i < cmd_seq["program fragment"].size(); i++) {
      std::string mode = cmd_seq["program fragment"][i]["mode"].get<std::string>();
      if (mode.compare("W") == 0) {
        hlscnn_if_rd = 0;
        hlscnn_if_wr = 1;
      } else {
        hlscnn_if_rd = 1;
        hlscnn_if_wr = 0;
      }
      // fetch the address
      std::string addr = cmd_seq["program fragment"][i]["addr"].get<std::string>();
      hlscnn_addr_in = std::stoi(addr, nullptr, 16);
      // extract each data byte from data
      std::string data = cmd_seq["program fragment"][i]["data"].get<std::string>();
      data_format.clear();
      if (data.length() <= 34) {
        data_format.append(34 - data.length(), '0');
        data_format.append(data.substr(2));
      } else {
        data_format.append(data.substr(data.length()-32));
      }
      for (int j = 0; j < 16; j++) {
        hlscnn_data_in[j] = std::stoi(data_format.substr(30-2*j,2), nullptr, 16);
      }
      wait(10, SC_NS);
    }

    input_done = 1;
}

};

SC_MODULE(testbench) {
  // SC_HAS_PROCESS(testbench);
  hlscnn hlscnn_inst;
  Source src;

  sc_clock clk;
  sc_signal< sc_biguint<1> > hlscnn_if_wr_signal;
  sc_signal< sc_biguint<1> > hlscnn_if_rd_signal;
  sc_signal< sc_biguint<32> > hlscnn_addr_signal;
  sc_signal< sc_biguint<8> > hlscnn_data_signal[16];

  sc_signal< sc_biguint<1> > input_done;

  SC_CTOR(testbench) :
    clk("clk", 1, SC_NS),
    hlscnn_inst("hlscnn_inst"),
    src("source")
  {
    // binding the signals
    src.clk(clk);
    src.hlscnn_if_rd(hlscnn_if_rd_signal);
    src.hlscnn_if_wr(hlscnn_if_wr_signal);
    src.hlscnn_addr_in(hlscnn_addr_signal);
    for (int i = 0; i < 16; i++) {
      src.hlscnn_data_in[i](hlscnn_data_signal[i]);
    }
    src.input_done(input_done);

    // // connecting signals to hlscnn
    hlscnn_inst.hlscnn_top_slave_if_rd_in(hlscnn_if_rd_signal);
    hlscnn_inst.hlscnn_top_slave_if_wr_in(hlscnn_if_wr_signal);
    hlscnn_inst.hlscnn_top_slave_addr_in_in(hlscnn_addr_signal);
    hlscnn_inst.hlscnn_top_slave_data_in_0_in(hlscnn_data_signal[0]);
    hlscnn_inst.hlscnn_top_slave_data_in_1_in(hlscnn_data_signal[1]);
    hlscnn_inst.hlscnn_top_slave_data_in_2_in(hlscnn_data_signal[2]);
    hlscnn_inst.hlscnn_top_slave_data_in_3_in(hlscnn_data_signal[3]);
    hlscnn_inst.hlscnn_top_slave_data_in_4_in(hlscnn_data_signal[4]);
    hlscnn_inst.hlscnn_top_slave_data_in_5_in(hlscnn_data_signal[5]);
    hlscnn_inst.hlscnn_top_slave_data_in_6_in(hlscnn_data_signal[6]);
    hlscnn_inst.hlscnn_top_slave_data_in_7_in(hlscnn_data_signal[7]);
    hlscnn_inst.hlscnn_top_slave_data_in_8_in(hlscnn_data_signal[8]);
    hlscnn_inst.hlscnn_top_slave_data_in_9_in(hlscnn_data_signal[9]);
    hlscnn_inst.hlscnn_top_slave_data_in_10_in(hlscnn_data_signal[10]);
    hlscnn_inst.hlscnn_top_slave_data_in_11_in(hlscnn_data_signal[11]);
    hlscnn_inst.hlscnn_top_slave_data_in_12_in(hlscnn_data_signal[12]);
    hlscnn_inst.hlscnn_top_slave_data_in_13_in(hlscnn_data_signal[13]);
    hlscnn_inst.hlscnn_top_slave_data_in_14_in(hlscnn_data_signal[14]);
    hlscnn_inst.hlscnn_top_slave_data_in_15_in(hlscnn_data_signal[15]);


    SC_THREAD(run);
  }

  double convert_act_to_double(sc_biguint<16> in) {
    ac_int<16, false> ac_in = in.to_uint();
    conv_activation_t out_act;
    out_act.set_slc<16>(0, ac_in);
    return out_act.to_double();
  }

  void run() {
    hlscnn_inst.instr_log.open("./sim_info/instr_log_conv.txt", ofstream::out | ofstream::trunc);
    hlscnn_inst.instr_update_log.open("./sim_info/instr_update_log_conv.txt", ios::out | ios::trunc);

    std::cout << "start running" << std::endl;
    std::cout << "*********** simulation start ***********" << std::endl;
    wait(10, SC_NS);

    while (input_done == 0) {
		  std::cout << "current simulation time: " << '\t' << sc_time_stamp() << "\r" << std::flush;
      wait(10, SC_NS);
    }

    wait(100000, SC_NS);
    std::cout << '\n' << std::endl;
    std::cout << "************* sc_stop **************" << std::endl;
    hlscnn_inst.instr_log.close();
    hlscnn_inst.instr_update_log.close();

    json v_result;
    json double_result;
    std::stringstream v_data_ss;
    for (auto it = hlscnn_inst.hlscnn_virtual_output_memory.rbegin();
        it != hlscnn_inst.hlscnn_virtual_output_memory.rend(); ++it) {
      double_result[fmt::format("0x{:08X}", it->first.to_uint())] = 
        convert_act_to_double(it->second);
    }
    std::ofstream fout;
    // fout.open(file_out, std::ios::out | std::ios::trunc);
    // fout << std::setw(2) << v_result;
    // fout.close();

    fout.open(file_out, std::ios::out | std::ios::trunc);
    fout << std::setw(2) << double_result;
    fout.close();
    
    sc_stop();
  }
};

int sc_main(int argc, char *argv[]) {
  if (argc != 3) {
      std::cout << "Usage: hlscnn_asm_sim_driver [prog_frag_in_path] [result_out_dump_path]" << std::endl;
      return 0;
  } else {
      file_in = argv[1];
      file_out = argv[2];
  }
  std::cout << "test start" << std::endl;
  testbench tb("tb");
  sc_start();

  return 0;
}