module ALUCt(

    input rst,

    input[5:0] funct,

    input[1:0] alu_ct_op,

    output reg[3:0] alu_ct

    );

    always @ (*)
        if(!rst)
            alu_ct = 0;
        else
            case(alu_ct_op)
                2'b00:alu_ct=4'b0010;
                2'b01:alu_ct=4'b0110;
                2'b10:begin case(funct)
                        6'b100001:alu_ct=4'b0010;
                        default:alu_ct=0;
                    endcase end
                default:alu_ct =0;
            endcase
endmodule