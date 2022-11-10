module f1_light_complete #(

) (
    input logic clk,
    input logic rst,
    input logic trigger,
    output logic [7:0] dout
);

logic [6:0] K;
/* verilator lint_off UNOPTFLAT */
logic cmd_seq;
logic cmd_delay;
logic tick;
logic time_out;

lfsr PSNG (
    .rst (rst),
    .en (1),
    .clk (clk),
    .dout (K)
);

delay delay (
    .n (K),
    .trigger (cmd_delay),
    .clk (clk),
    .rst (rst),
    .time_out (time_out)
);

clktick onesec (
    .N (54),
    .en (cmd_seq),
    .rst (rst),
    .clk (clk),
    .tick (tick)
);

f1_fsm fsm (
    .rst (rst),
    .en (cmd_seq ? tick : time_out),
    .trigger (trigger),
    .clk (clk),
    .cmd_seq (cmd_seq),
    .cmd_delay (cmd_delay),
    .dout (dout)
);

endmodule
