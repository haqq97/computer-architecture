//MUHAMMAD TAHA HAQQANI, SECTION 501
// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/04/Fill.asm

// Runs an infinite loop that listens to the keyboard input. 
// When a key is pressed (any key), the program blackens the screen,
// i.e. writes "black" in every pixel. When no key is pressed, the
// program clears the screen, i.e. writes "white" in every pixel.

//ALGORITHM: if keyboard input not zero, color the registers black while (register != keyboard) else color screen white

// Put your code here.
(START)
@KBD  //A = 24576
D = M //D = RAM[24576]

//if keyboard input not 0 jump to BLACK
@BLACK 
D; JNE 

//white
@COLOR // A = 16
M = 0  // RAM[16] = COLOR = 0

(LOOP)
@SCREEN //A = 16384
D = A //D = 16384

@REG //A = 17 
M = D  //RAM[17] = REG = 16384

(AGAIN)
@COLOR //A = 16
D = M //D = RAM[16] = COLOR =  0/-1

@REG   // A = 17
A = M  // A = RAM[REG] = 16384
M = D  // RAM[REG] = COLOR

@REG
M = M + 1 

@KBD  
D = A //D = 24576
@REG
D = D - M  //D = 24576 - RAM[REG]
@START 
D; JEQ //if D == 0 then JUMP to check keyboard again else move to color the next register

@AGAIN
0; JMP

(BLACK)
@COLOR 
M = -1 //color = 1111111111111111
@LOOP
0; JMP

