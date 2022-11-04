module f1_fsm #(

) (
    input  logic       rst,
    input  logic       en,
    input  logic       clk,
    output logic [7:0] dout
);

    typedef enum {S_1, S_2, S_3, S_4, S_5, S_6, S_7, S_8, S_0} state;
    state current_state = S_0, next_state;

    always_ff @(posedge clk)
        if (rst) current_state <= S_0;
        else     current_state <= next_state;
    
    always_comb
    begin
        if (en) begin
            case (current_state)
                S_0: next_state = S_1;
                S_1: next_state = S_2;
                S_2: next_state = S_3;
                S_3: next_state = S_4;
                S_4: next_state = S_5;
                S_5: next_state = S_6;
                S_6: next_state = S_7;
                S_7: next_state = S_8;
                S_8: next_state = S_0;
                default: next_state = S_0;
            endcase

            case (current_state)
                S_0: dout = 8'b0;
                S_1: dout = 8'b1;
                S_2: dout = 8'b11;
                S_3: dout = 8'b111;
                S_4: dout = 8'b1111;
                S_5: dout = 8'b11111;
                S_6: dout = 8'b111111;
                S_7: dout = 8'b1111111;
                S_8: dout = 8'b11111111;
                default: dout = 8'b0;
            endcase
        end

    end
        

endmodule
