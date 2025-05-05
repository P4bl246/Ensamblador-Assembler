README - C Assembler Hack
# C Compiler/Assembler Hack
**Author:** Pablo Riveros Perea

**Project:** Assembler Hack

**Profile:** [https://github.com/P4bl246]

------------------------------------------------------
## Dependencies

------------------------------------------------------
You must have *Dev C++/C* version 5.11 or later, or a *modern C compiler* installed.

[Download Dev C++/C](https://sourceforge.net/projects/orwelldevcpp/)

Required external libraries:
* `stdio.h`
* `stdlib.h`
* `string.h`

(You don't need to install these if you already have *Dev C++/C* or a modern compiler, as they are usually built in.)

**IMPORTANT NOTE:** If you are using **VSCode, you must replace** the *copyValuesWithVariables* function with this implementation.
~~~
int copyValuesWithVariables(FILE *readFile, FILE *writeFile){
int n = 16;//initial value of variable, incrementing it
int current = fgetc(readFile);
char buffer[5]; //character string maximum 5 because the maximum value of n is 5 digits
while(actual != EOF){
if(n == 16383){
printf("The maximum number of possible variables has been reached (16383)\n");
fclose(fileRead);
fclose(fileWrite);
return 1;
}
sprintf(buffer, "%d", n); // Convert the integer 'n' to a string
if((char)current == '@'){
current = fgetc(readFile);//go to the next character after @
// Check if the character is not a number
if( !((char)current >= '0' && (char)current <= '9')){
fputs(buffer, writeFile);//put the value of the variable
fputc(' ', writeFile);//separate the variable name
while(current != EOF && (char)current != '\n' && (char)current != '\0' && (char)current != ' '){
fputc((char)current, writeFile);
current = fgetc(readFile);
}
if(current == EOF){
printf("End of file reached\n"); //exit function
fclose(fileRead);
fclose(fileWrite);
return 1;
}
fputc('\n', fileWrite);
}
}
actual = fgetc(fileRead);
n++;
}
fclose(fileWrite);
return 0;
}
~~~

## Installation

-----------------------------------------------------
1. Download the `assembly.h` library and the `assembler.c` executable to the **same folder** or **path** as the *compiler*.

2. Compile and run the *executable*, and enter the ***full name of your .asm file*** as an argument to the `fileA_txt` function (the file must also be in the *same path*).

3. Compile and run the code and open the `hackfile.hack` file where the binary is located.

***NOTE:*** All *temporary files* and the final `hackfile.hack` file will be *created locally in the path*.

**Installation Recommendations**

* Create a separate folder for the *compiler* where you will also place the `assembly.h` library and your `assembler.c` executable.

* Make sure you **do not** have other ***.txt*** *files* in the *same path* (folder), as they could have the *same name* as other *temporary* assembler files, which could *delete their contents* or cause *errors in the program execution*.

## Usage

------------------------------------------------------
This program is *designed* to assemble in HACK assembly language, or a similar one.

**Example:**
~~~
@R0
D=M+1
A=D
@2
0;JMP
~~~

* Within the library, functions labeled in their comments as **Internal Function** mean that they are **functions designed to be used within the library itself and not for use outside of it**. However, you can use them outside of it if you wish.

* If there is an **error** to see where the **error** occurred with your line number, you must open the file ***copy.txt***

* If you want to see the ***symbol table***, open the file **table.txt**

* This program does not have the *same restrictions* as NAND2TETRIS regarding the assembly part of **COMP** (calculation of C instructions), because it can add operations like 0+D or D+0, or other reciprocal operations, because this is then adjusted to binary with its binary representation.

**EXAMPLE:**

D+1 = 001111

1+D = 001111

**IMPORTANT NOTE:** The *NAND2TETRIS* emulator does not accept 1-M, which would actually be -M+1, but since it does not accept this binary representation (1+(!Y +1) (***the ALU can process it, but the emulator does not recognize it***)), it is refactored to M-1 (*this is not correct, but it is what the emulator accepts, so every time you enter something like 1-M or 1-D or 1-A, it is refactored to M-1, A-1, D-1*)

* You can test the assembler by downloading the [test] game Pong](https://github.com/P4bl246/Ensamblador/blob/0205bb4d452f275c46cd718c1aacd121882d91a9/Pong.asm) in the *same path* as the *compiler and assembler*
