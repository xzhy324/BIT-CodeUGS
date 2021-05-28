`timescale 1ns / 1ps

module sequenceDetector(CLK, RESET , X, Y, state);
    input CLK,RESET,X;
    output Y;
    output reg[1:0] state;
    parameter A = 2'b00, B = 2'b01, C = 2'b11, D = 2'b10;
    reg Y;
    
    // 当前状态定周期更新
    always @(posedge CLK)
    begin 
        if (RESET)
            state <= A;
       case (state)
            A:
                begin
                    Y = 0;
                    if(~X) state <= B;
                    else state <= A;
                end
                
            B:
                if(~X) state <= C;
                else state <= A;
            C:
                if(~X) state <= D;
                else state <= A;
            D:
                if(~X) Y = 1;
                else state <= A;
    end
endmodule
