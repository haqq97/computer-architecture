//MUHAMMAD TAHA HAQQANI, SECTION 501
// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/04/Mult.asm

// Do multiplication of R0 and R1 and stores the result in R2.
// (R0, R1, R2 refer to RAM[0], RAM[1], and RAM[2], respectively.)
//ALGORITHM: 3*5 = (3*2) + (3*2) + (3*1) 
@R1 
D = M
@RESULT //initialize result  = 0
M = 0 
@COUNTER //initialize counter = 0
M = D

@END //if counter = 0, jump to end
D; JEQ

(LOOP)
@2
D = A
@COUNTER
D = M - D //check if counter - 2 < 0

@ADD //if counter - 2 < 0 add R0 to result
D; JLT

@R0
D = M<1 //multiply R0 by 2
@RESULT
M = D + M //add to result
@2
D = A
@COUNTER
M = M - D //decrement counter by 2
D = M
@END 
D; JEQ //if counter reaches 0, jumpto end
@LOOP
0;JMP

(ADD)
@R0
D = M
@RESULT
M = D + M //add R0 to result
(END)
@RESULT
D = M
@R2 //store result in R2
M = D
(DONE)
@DONE
0;JMP