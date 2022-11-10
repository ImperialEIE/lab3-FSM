module f1_light #(

) (
    input  logic        clk,
    input  logic        en,
    input  logic        rst,
    input  logic [15:0] N,
    output logic [7:0]  dout
);

logic tick;

clktick timer (
    .N (N),
    .rst(rst),
    .clk(clk),
    .en(1),
    .tick(tick)
);

f1_fsm lights (
    .rst(rst),
    .en(tick),
    .clk(clk),
    .dout(dout)
);

endmodule
