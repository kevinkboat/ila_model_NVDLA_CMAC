// File: main.cc
#include <cmac.h>

#include <ilang/ilang++.h>
#include <ilang/util/log.h>
#include <iostream>
#include <ilang/vtarget-out/vtarget_gen.h>
using namespace std;

using namespace ilang;

/// the function to generate configuration
VerilogVerificationTargetGenerator::vtg_config_t SetConfiguration();

void verify_cmac(Ila& model, VerilogVerificationTargetGenerator::vtg_config_t vtg_cfg, const std::vector<std::string> & design_files); 

int main(int argc, char* argv[]) {
  SetToStdErr(1);

  cout << "start";
  // get the ILA model
  auto cmac = GetCMACIla("cmac");

  ILA_INFO << "#instr: " << cmac.instr_num();
  for (auto i = 0; i < cmac.instr_num(); i++) {
    ILA_INFO << cmac.instr(i);
  }

  ILA_INFO << "#state: " << cmac.state_num();
  for (auto i = 0; i < cmac.state_num(); i++) {
    ILA_INFO << cmac.state(i);
  }

  ILA_INFO << "#input: " << cmac.input_num();
  for (auto i = 0; i < cmac.input_num(); i++) {
    ILA_INFO << cmac.input(i);
  }

  std::vector<std::string> cmac_design_files = {
    "NV_NVDLA_cmac_top.v"
  };

  auto vtg_cfg = SetConfiguration();

  verify_cmac(cmac, vtg_cfg, cmac_design_files);

  return 0;
}

