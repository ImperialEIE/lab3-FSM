# Fail on error or unbounded variable
set -euo pipefail

# cleanup
rm -rf obj_dir
rm -f f1_fsm.vcd

# run Verilator to trnanslate Verilog into C++, incuding the C++ testbench
verilator -Wall --cc --trace f1_fsm.sv --exe f1_fsm_tb.cpp

# Build C++ project via make automatically generated by Verilator
make -j -C obj_dir/ -f Vf1_fsm.mk Vf1_fsm

# run exec
obj_dir/Vf1_fsm
