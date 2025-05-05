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
int copiarValoresConVariables(FILE *archivoLeer, FILE *archivoEscribir){
	int n= 16;//valor incial de variable y se va incrementando
   int actual = fgetc(archivoLeer);
   char buffer[5]; //cadena de caracteres maximo 5 porque el valor maximo de n es de 5 digitos
   while(actual != EOF){
   	if(n == 16383){
   		printf("Se alcanzo el maximo de variables posibles (16383)\n");
   		fclose(archivoLeer);
   		fclose(archivoEscribir);
   		return 1;
	   }
    sprintf(buffer, "%d", n);  // Convertir el entero 'n' a una cadena
   	  if((char)actual == '@'){
   	  	     actual = fgetc(archivoLeer);//ir a el siguiente caracter despues de @
   	  	    // Verifica si el carácter no es un numero
             if( !((char)actual >= '0' && (char)actual <= '9')){
             	fputs(buffer, archivoEscribir);//poner el valor de la variable
             	fputc(' ', archivoEscribir);//separa el nombre de la variable
             	 while(actual != EOF && (char)actual != '\n' && (char)actual != '\0' && (char)actual != ' '){
             	 	fputc((char)actual, archivoEscribir);
             	 	actual = fgetc(archivoLeer);
				  }
				  if(actual == EOF){
				  	printf("Se llego a el final de el archivo\n"); //salir de la funcion
				  	fclose(archivoLeer);
				  	fclose(archivoEscribir);
				  	return 1;
				  }
				  fputc('\n', archivoEscribir);
			 }
		 }
		 actual = fgetc(archivoLeer);
		 n++;
   }
   fclose(archivoEscribir);	
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

  ## Recommendations, Observations, and Considerations

------------------------------------------------
* Make sure you set your operating system correctly to avoid problems running the program (***supports Windows, macOS, and Unix/Linux***)

**NOTE:** If your *operating system is not supported,* make sure you enter the correct **console** **cleanup** command.

* ***Make sure the file name, variables, and labels do not exceed 1023 characters, as this could lead to data loss and unexpected events, such as replacing variables, since the program only reads up to 1023 characters.***

* ***If for some reason there is an error when creating or opening a file, check Windows security and disable real-time scanning or allow the compiler to manipulate files***

* The *only* case that **the code does not handle** is when there are ***nested block comments***

**EXAMPLE:**
~~~
/* /*This is a nested comment*/D=M
~~~

**EXPLANATION:** The **problem** is that the **code** looks for the `*/` after the start of a block comment (`/*`) is indicated, so in the previous example `D=M` will be treated as an instruction, *even if the main block comment has not been closed*, that is, the *first* `/*`.

**But if we put**

~~~
/* /*This is a nested comment*/D=M*/
~~~

***The code would identify it indirectly because the last `*/` identifies it and warns it as a syntax error in the instruction that is taken `D=M` from the previous example as a C instruction***

***NOTE:*** This is because in *rare cases* this happens and it is a ***practice that is not recommended***, due to cases like those in the previous code that **can occur in other programs not just in this one**

* Before reviewing the code (mainly from the `ensamblando.h` library), it is recommended to have **knowledge of the architecture of the *CPU* and the *ALU*** to understand certain fragments of the code such as the **ASSEMBLY** part, this will be in the [ARCHITECTURE.md](https://github.com/P4bl246/Assembler/blob/e50e91bbd4e8a84b83cbad30191bdc36ba5f4548/ARCHITECTURE.md) (*where the reasons for certain operations and restrictions and how more operations could be integrated will also be explained*).

* The design and creation of this program focuses on functionality and scalability rather than optimization (although best practices are used). This is open to anyone who wants to improve the code by optimizing it in many ways.

**Examples:**
* The search for values ​​in the symbol table could be improved by using *hash tables*, instead of *linear search*.
* Many blocks of repeated code could be modulated, such as taking the line number.

* This program was created as a final project for the first part of the ***NAND2TETRIS*** course, so to *run* the `.hack` file, you must install the *NAND2TETRIS* software or use its *ONLINE IDE*.
[NAND2TETRIS SOFTWARE](https://www.nand2tetris.org/software)

* Steps to run it on **Windows**

1. Unzip the .zip file

2. Go to the *nand2Tetris* folder

![image](https://github.com/user-attachments/assets/c79bfabc-fa18-473f-8a2d-430c16a5152c)

3. Go to *tools*

![image](https://github.com/user-attachments/assets/3d02e465-eb4d-4e3c-a30c-56852bfecdab)

4. Open *CPUEmulator.bat*

![image](https://github.com/user-attachments/assets/dd05c2ea-fe7c-45ab-b3a2-a39e5c8c57f9)

5. Select *Load ROM* or *Load File*, select the `.hack` file, and run it by clicking *>>* or *>*

![image](https://github.com/user-attachments/assets/49a07fc2-2d1d-4054-a7f1-43fb40156316)

**NOTE:** For macOS, it's the same. that you enter **_MACOSX** instead of **nand2Tetris**

* If you are using the **NAND2TETRIS ONLINE IDE**, enter the **CPU Emulator** and load the `.hack` by clicking on the folder icon

![image](https://github.com/user-attachments/assets/9b18f438-43f0-4db7-8735-98b1a8ef9f93)

-------------------------------------------------
