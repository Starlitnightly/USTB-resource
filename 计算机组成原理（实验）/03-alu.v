module ALU(

input rst,

input[3:0] alu_ct,

input[31:0] alu_src1,alu_src2,

output alu_zero,

output reg [31:0] alu_res

    );

    assign alu_zero=(alu_res==0)?1:0;

    always @ (*)
        if (!rst) begin
            alu_res= 32'b0;
        end
        else begin
            case(alu_ct)
                4'b0010:alu_res=alu_src1+alu_src2;
                4'b0110:alu_res=alu_src1-alu_src2;
                default:alu_res=32'b0;
            endcase
    end
endmodule