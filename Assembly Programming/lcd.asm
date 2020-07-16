//MUHAMMAD TAHA HAQQANI, SECTION 501
//Implement a program that calculates the largest common divisor (lcd) of two given non-negative integers,
//which are stored in RAM[0] (R0) and RAM[1] (R1). The lcd is stored in RAM[2] (R2).
//ALGORITHM: EUCLID ALGORITHM
// B = R1
@R1
D = M
@B 
M = D
// A = R0
@R0
D = M
@A
M = D
//WHILE (A-B >= 0) A = A - B 
(LCD)
(LOOP)
@B
D = D - M

@LOOP
D; JGE

//IF REMAINDER IS 0, A IS THE ANSWER BECAUSE BASE CASE IS LCD(X,0)
//ELSE PERFORM LCD(A,B) WHERE A=B AND B=REMAINDER
//SWAP A WITH B
//SWAP B WITH REMAINDER

@B
D = D + M
@ANSWER
D; JEQ
@REMAINDER
M = D
@B
D = M
@A
M = D
@REMAINDER
D = M
@B
M = D
@A
D = M

@LCD
0; JMP

(ANSWER)
@B
D = M
@R2
M = D
(END)
@END
0;JMP




