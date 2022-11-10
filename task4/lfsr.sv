module lfsr #(

) (
    input  logic       clk,
    input  logic       en,
    input  logic       rst,
    output logic [6:0] dout
);

    logic [7:1] sreg = 7'b1;
    // logic [4:1] sreg = 4'b1'

    always_ff @(posedge clk)
        if (rst)
            // sreg <= 4'b1;
            sreg <= 7'b1;
        else if (en)
            // sreg <= {sreg[6:1], sreg[3] ^ sreg[4]};
            sreg <= {sreg[6:1], sreg[3] ^ sreg[7]};
        else
            sreg <= sreg;

    assign dout = sreg;

endmodule
