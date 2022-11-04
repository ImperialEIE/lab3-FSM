#include "verilated.h"
#include "verilated_vcd_c.h"
#include "Vlfsr.h"
#include "vbuddy.cpp"

#define MAX_SIM_CYC 1e6

int main(int argc, char **argv, char **env) {
    int simcyc;
    int tick;

    Verilated::commandArgs(argc, argv);

    Vlfsr *top = new Vlfsr;

    Verilated::traceEverOn(true);
    VerilatedVcdC *tfp = new VerilatedVcdC;
    top->trace (tfp, 99);
    tfp->open ("lfsr.vcd");

    if (vbdOpen() != 1) return(-1);
    vbdHeader("L3T1: LFSR");
    vbdSetMode(1);

    top->clk = 1;
    top->en = 1;
    top->rst = 0;

    for (simcyc = 0; simcyc < MAX_SIM_CYC; simcyc++) {
        for (tick = 0; tick < 2; tick++) {
            tfp->dump (2 * simcyc + tick);
            top->clk = !top->clk;
            top->eval ();
        }

        if (vbdFlag()) {
            top->en = 1;
            // top->dout++;
        }
        else {
            top->en = 0;
        }


        vbdBar(top->dout & 0xFF);
        vbdHex(1, top->dout & 0xFF);
    }
}
