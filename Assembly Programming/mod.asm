//MUHAMMAD TAHA HAQQANI, SECTION 501
//Implement a program that calculates the largest common divisor (lcd) of two given non-negative integers, which are
//stored in RAM[0] (R0) and RAM[1] (R1). The lcd is stored in RAM[2] (R2).
//ALGORITHM: Subtract b from a, if (remainder >=0) repeat. Else add b to remainder and store in R2
@R0
D = M

(loop)
@R1
D = D - M 

@loop 
D; JGE //keep subtracting until D is negative

@R1
D = D + M //add the dividend to find the remainder

@R2
M = D

(END)
@END
0;JMP

	