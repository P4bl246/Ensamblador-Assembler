# HACK COMPUTER ARCHITECTURE
The HACK computer is a simple computer composed of a CPU, a ROM, and a 16-bit bus RAM.

[NAND2TETRIS SITE WHERE YOU WILL FIND ALL THE RESOURCES AND SLIDES](https://www.nand2tetris.org/course)

-------------------------------------------------------
## CPU Architecture

-------------------------------------------------------
The **CPU** is composed of:
* ALU (Arithmetic Logic Unit)
* PC (Program Counter)
* Registers (A and D)

## RAM Architecture

-------------------------------------------------------
The **RAM** is composed of:
* 24576 Registers

These *registers* are divided into 3:
* *General-purpose* registers (0-16383)
* *Reserved* registers for the *display* (16384-24575)
* Register *reserved* for the *keyboard* (24576)

## ROM Architecture

-------------------------------------------------------
The **ROM** is composed of:
* 32767 Registers

***NOTE:*** The **ROM** is where the *assembly language* (HACK) or the *binary directly* is loaded, that is, the instructions
# FLOW

-------------------------------------------------------
ROM->CPU->RAM

![image](https://github.com/user-attachments/assets/1b1d242e-1812-4baa-af41-4f233b039d01)

[HERE YOU CAN SEE THE DETAILED ARCHITECTURE OF *NAND2TETRIS*](https://drive.google.com/file/d/1Z_fxYmmRNXTkAzmZ6YMoX9NXZIRVCKiw/view)

##ALU
----------------------------------------------------
The ALU has 6 control bits that, depending on their state (0 or 1), activate a function

![image](https://github.com/user-attachments/assets/8dd81865-69c0-42df-952f-d8495d953836)

[ALU NADN2TETRIS DETAILED](https://drive.google.com/file/d/1ie9s3GjM2TrvL7PrEZJ00gEwezgNLOBm/view)

* zx = x = 0 (*set x to 0*)
* nx = !x (*negate X*)
* zy = z = 0 (*set Y to 0*)
* ny = !y ​​(*negate Y*)
* f = +(if it is 1) & (if it is 0)
* no = !f (that is, it negates what comes out of f)

**NOTE:** In the assembler we are not going to use *zr* or *ng* so I am not presenting it here

### Explanation
So we see that in the architecture the inputs of the ALU are X and Y, and we can see that the *X* input in the CPU is always the **D register** and the *Y* are the **M or A registers** (***M is the value of the current address, that is, the value of the current memory address or what is stored in the RAM***)

![image](https://github.com/user-attachments/assets/4e0670ad-81f7-4904-a1a7-623acfb09157)

This is why we see X and Y in the *pattern structure* and not A, M, and D, because we don't see them as registers but as inputs to the *ALU* and depending on the 6 control bits it is decided what the ALU does because these are the ones it receives, and they do the same with the operators, we are only interested in the operator and what its binary representation is, which we obtain from the COMP table that does not give NAND2TETRIS, and we obtain the binary values ​​of each operator.

(These are the ones marked)

![image](https://github.com/user-attachments/assets/e87e0a3a-3e17-40aa-a614-13cda23bbaae)

If we look at the image in the operators, there is a pattern. For example, in the *!* operator, we can see that the last bit is always 1, and in the subtraction, we see that the last 2 are always 1. There is another special active bit depending on whether X or Y is before the **-** operator, and other patterns in other operators.

We can also see that depending on how the operator is, that is, if it is before or after the operand, there is a certain pattern. For example, if it is before, only the operand and the negative value, which is 3 (000011), are placed. There are also exceptions, such as in constants (0 and 1).

These are the reasons why the *patrón* values ​​placed in *valores* are those (although they can be altered as long as the entire code is adjusted to obtain the desired result), and these are integers, because we don't want to deal with their binary representation, but rather with integers, which is easier to handle. Then we can convert this to binary.

## ADDING NEW OPERATORS

--------------------------------------------------------------
Understanding this, you can now understand how to add *new operators* by defining what their binary is and putting this as an integer in the *patrón* structure and its value in *valores*, and then adding it to the end of the `operador function` with which that value is added or what integer to return, and with their different possible cases in which the operator comes before and after, and in the case of constants (all possible cases and their integer representation), and that's it. You could add new operators.

**EXAMPLE:**

1. If I wanted to add the NAND operator, I would first look for its binary representation:

`NAND = 010100` (because we do !(X & Y) = !X & !Y)

2. I look for its decimal representation:

`010100 = 20`

4. I add this to the table:

`NAND;`

In `values`, I add

`.NAND = 20;`

4. We go to the last case of the `operador` function and enter our new operator with its possible combinations (where we will represent this with the `$` symbol).

~~~
if(previous == '$'){
if(*current == 'M' || *current == 'A'){
return values. NAND + 22;//because it's 110100
}
else if(*current == 'D'){
...
}
~~~
And that's it, in this case, as before, where only this operator should be used and we would have to add the new condition to `analisis sintáctico` to prevent it from writing something like A$D (*it's not possible because I made it so that it only has one operator before the operand*)

## RECOMMENDATIONS AND CONSIDERATIONS

------------------------------------------------------------

* It is recommended to take the ***NAND2TETRIS part 1*** course to *fully understand* and thoroughly each part of the **CPU** and the **ALU**, it can be found on Coursera

* In ***syntactical analysis*** there are *restrictions of The maximum number of addresses* that can be entered is due to what we saw earlier about the number of registers in the **ROM** (*which is the maximum number that can be represented by 16 bits*)

[NAND2TETRIS COURSE PART 1](https://www.coursera.org/learn/build-a-computer)
