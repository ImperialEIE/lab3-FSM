#include "verilated.h"
#include "verilated_vcd_c.h"
#include "Vf1_light_complete.h"

#include "vbuddy.cpp"     // include vbuddy code
#define MAX_SIM_CYC 100000

int main(int argc, char **argv, char **env) {
  int simcyc;     // simulation clock count
  int tick;       // each clk cycle has two ticks for two edges
  int lights = 0; // state to toggle LED lights

  Verilated::commandArgs(argc, argv);
  // init top verilog instance
  Vf1_light_complete *top = new Vf1_light_complete;
  // init trace dump
  Verilated::traceEverOn(true);
  VerilatedVcdC* tfp = new VerilatedVcdC;
  top->trace (tfp, 99);
  tfp->open ("f1_light_complete.vcd");
 
  // init Vbuddy
  if (vbdOpen()!=1) return(-1);
  vbdHeader("L3T4: F1");
  vbdSetMode(1);        // Flag mode set to one-shot

  // initialize simulation inputs
  top->clk = 1;
  top->rst = 0;
  // top->trigger = 1;

  bool readyToTime;
  bool timingMode;
  bool flag;
  
  // run simulation for MAX_SIM_CYC clock cycles
  for (simcyc=0; simcyc<MAX_SIM_CYC; simcyc++) {
    // dump variables into VCD file and toggle clock
    for (tick=0; tick<2; tick++) {
      tfp->dump (2*simcyc+tick);
      top->clk = !top->clk;
      top->eval ();
    }

    top->rst = (simcyc < 2);    // assert reset for 1st cycle

    vbdBar(top->dout & 0xFF);

    // if (top->dout == 2^8 - 1) readyToTime = true;
    // if (readyToTime && top->dout == 0) {
    //   vbdInitWatch();
    //   timingMode = true;
    //   readyToTime = false;
    // }
    
    // set up input signals of testbench
    flag = vbdFlag();
    if (timingMode && flag) {
      int result = vbdElapsed();
      std::string msec = std::to_string(result);
      msec.insert(msec.begin(), 5 - msec.size(), '0');

      vbdHex(1, (int)(msec[msec.size() - 1] - '0') & 0xFF); // print just digits
      vbdHex(2, (int)(msec[msec.size() - 2] - '0') & 0xFF);
      vbdHex(3, (int)(msec[msec.size() - 3] - '0') & 0xFF);
      vbdHex(4, (int)(msec[msec.size() - 4] - '0') & 0xFF);
      vbdHex(5, (int)(msec[msec.size() - 5] - '0') & 0xFF);
      
      timingMode = false;
    }
    else top->trigger = flag;
    vbdCycle(simcyc);

    if (Verilated::gotFinish() || (vbdGetkey()=='q')) {
      vbdClose();
      tfp->close();
      exit(0);
    } 
  }

  vbdClose();     // ++++
  tfp->close(); 
  exit(0);
}
