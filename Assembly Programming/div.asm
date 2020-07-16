//MUHAMMAD TAHA HAQQANI, SECTION 501
//calculate the quotient from a division operation. 
//The values of dividend a and divisor b are stored in RAM[0] (R0) and RAM[1] (R1), respectively. 
//The dividend a is a non-negative integer, and the divisor b is a positive integer. 
//Store the quotient in RAM[2](R2). Ignore the remainder.
//ALGORITHM: subtract b from a, increment counter, if (remainder >=0) repeat. Else store counter in R2 
@R0
D = M //D = RAM[0] = R0

//counter = -1
@counter
M = -1 //

(loop)
@R1
D = D - M //D = D - RAM[1] 

//increment counter
@counter
M = M + 1 

@loop 
D; JGE //If D >= 0 keep subtracting

//else R2 = counter = quotient
@counter
D = M
@R2
M = D

(END)
@END
0;JMP





