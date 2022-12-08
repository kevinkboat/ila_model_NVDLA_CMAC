// File: cmac.cc
#include <cmac.h>

#include <ilang/ilang++.h>
#include <ilang/util/log.h>
#include <iostream>
#include <ilang/vtarget-out/vtarget_gen.h>
using namespace std;

using namespace ilang;

/// the function to generate configuration
VerilogVerificationTargetGenerator::vtg_config_t SetConfiguration();

void verify_cmac(Ila& model, 
  VerilogVerificationTargetGenerator::vtg_config_t vtg_cfg,
  const std::vector<std::string> & design_files); 

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

void verify_cmac(
  Ila& model, 
  VerilogVerificationTargetGenerator::vtg_config_t vtg_cfg,
  const std::vector<std::string> & design_files
   ) {
  VerilogGeneratorBase::VlgGenConfig vlg_cfg;
  vlg_cfg.pass_node_name = true;
  vtg_cfg.ForceInstCheckReset = true;
  vtg_cfg.MemAbsReadAbstraction = true;

  std::string RootPath    = "..";
  std::string VerilogPath = RootPath    + "/nvdla/cmac/";
  std::string IncludePath = VerilogPath + "include/";
  std::string RefrelPath  = RootPath    + "/refinement/";
  std::string OutputPath  = RootPath    + "/verification/";

  std::vector<std::string> path_to_design_files;
  for(auto && f : design_files)
    path_to_design_files.push_back( VerilogPath + f );
  

  VerilogVerificationTargetGenerator vg(
      {IncludePath},                                         // one include path
      path_to_design_files,                                  // designs
      "NV_NVDLA_cmac",                               // top_module_name
      RefrelPath + "ref-rel-var-map-cmac.json",                // variable mapping
      RefrelPath + "ref-rel-inst-cond-cmac.json",              // conditions of start/ready
      OutputPath,                                            // output path
      model.get(),                                           // model
      VerilogVerificationTargetGenerator::backend_selector::JASPERGOLD, // backend: JASPERGOLD
      vtg_cfg,  // target generator configuration
      vlg_cfg); // verilog generator configuration

  vg.GenerateTargets();
}

VerilogVerificationTargetGenerator::vtg_config_t SetConfiguration() {

  // set ilang option, operators like '<' will refer to unsigned arithmetics
  SetUnsignedComparison(true); 
  
  VerilogVerificationTargetGenerator::vtg_config_t ret;
  ret.CosaSolver = "btor";
  ret.CosaPyEnvironment = "~/cosaEnv/bin/activate";
  ret.CosaPath = "~/CoSA";
  ret.CosaGenTraceVcd = true;
  ret.CosaAddKeep = false;

  /// other configurations
  ret.PortDeclStyle = VlgVerifTgtGenBase::vtg_config_t::NEW;
  ret.CosaGenJgTesterScript = true;
  //ret.CosaOtherSolverOptions = "--blackbox-array";
  //ret.ForceInstCheckReset = true;

  return ret;
}

