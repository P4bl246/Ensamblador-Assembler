README - C Assembler Hack
# C Compiler/Assembler Hack
**Author:** Pablo Riveros Perea

**Project:** Assembler Hack

**Profile:** [https://github.com/P4bl246]

------------------------------------------------------
## IMPORTANT

***The source code is written in Spanish If you prefer to read it in English, you can use translation extensions in your IDE.***

**SOME EXTENSIONS FOR VScode:**

* [Comment Translate](https://marketplace.visualstudio.com/items?itemName=intellsmi.comment-translate)
  
* [vscode-google-translate](https://marketplace.visualstudio.com/items?itemName=funkyremi.vscode-google-translate)

**NOTE:** If you can't use any extensions for translate in your IDE, you can *make a `codespace` in github* copy this repository or the [source code](ENASAMBLADOR_PAQUETE)

[***Don't know how to create a `codespace`***](https://docs.github.com/en/codespaces/developing-in-a-codespace/creating-a-codespace-for-a-repository)

------------------------------------------------------
## Dependencies

You must have *Dev C++/C* version 5.11 or later, or a *modern C compiler* installed.

[Download Dev C++/C](https://sourceforge.net/projects/orwelldevcpp/)

Required external libraries:
* `stdio.h`
* `stdlib.h`
* `string.h`

(You don't need to install these if you already have *Dev C++/C* or a modern compiler, as they are usually built in.)

**IMPORTANT NOTE:** If you are using **VSCode, you must replace** the *copiarValoresConVariables* function with this implementation.
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
             	 while(actual != EOF && (char)actual != '\n' && (char)actual != '\0' && (char)actual != ' ' && actual != '\r'){
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
1. Download the `ensamblando.h` library and the `Ensamblador.c` executable to the **same folder** or **path** as the *compiler*.

2. Compile and run the *executable*, and enter the ***full name of your .asm file*** as an argument to the `archivoA_txt` function (the file must also be in the *same path*).

3. Compile and run the code and open the `archivoHack.hack` file where the binary is located.

***NOTE:*** All *temporary files* and the final `archivoHack.hack` file will be *created locally in the path*.

**Installation Recommendations**

* Create a separate folder for the *compiler* where you will also place the `ensamblando.h` library and your `Ensamblador.c` executable.

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

* This program does not have the *same restrictions* as NAND2TETRIS regarding the assembly part of **COMP** (calculation of C instructions), because it can add operations like 0+D or D+0, or other equivalents operations, this aplicated for all operators, because this is then adjusted to binary with its binary representation.

**EXAMPLE:**

D+1 = 001111

1+D = 001111

**IMPORTANT NOTE:** The *NAND2TETRIS* emulator does not accept 1-M, which would actually be -M+1, but since it does not accept this binary representation (1+(!Y +1) (***the ALU can process it, but the emulator does not recognize it***)), it is refactored to M-1 (*this is not correct, but it is what the emulator accepts, so every time you enter something like 1-M or 1-D or 1-A, it is refactored to M-1, A-1, D-1*)

* You can test the assembler by downloading the [test game Pong](Pong.asm) in the *same path* as the *compiler and assembler*

## Design Decisions

------------------------------------------------------

### Code Architecture

This assembler is designed as a **single-purpose command-line program** that processes files sequentially through multiple phases. For ease of deployment and compilation, all function implementations are included in the header file `assembling.h`.

**Reason:** This allows users to compile the project with a single command without the need for complex build systems (Makefiles, CMake, etc.). It is ideal for an educational context where the focus should be on understanding assembler, not mastering C build tools.

**Note for developers:** If you wish to use this code as a library in another project, you can easily separate the implementations from the header into a corresponding `.c` file. All function headers are already correctly declared.

### Sequential Processing Pipeline

The assembler processes files in **multiple sequential phases** where each phase prepares the data for the next:

1. **Conversion and Cleaning**: Conversion from .asm to .txt, removal of spaces, comments, and empty lines
2. **Syntax Analysis**: Complete syntax validation before proceeding
3. **Symbol Table Construction**: Identification and organization of labels and variables
4. **Assembly**: Conversion to 16-bit binary machine code

**Reason:** This separation of responsibilities makes each phase simple and focused. Each function does one thing and does it well. Multithreading is not required because:
- Assembler files are small (typically <10,000 lines)
- Processing is extremely fast (milliseconds on modern hardware)
- Phases are inherently sequential (you cannot assemble before building the symbol table)

### Error Handling: Warnings vs. Fatal Errors

The assembler distinguishes between:
- **Warnings**: Problems that do not prevent assembly but that the user should be aware of (e.g., truncation of numbers >5 digits)
- **Fatal Errors**: Problems that would corrupt the output (e.g., exceeding the variable limit)

**Reason:** This allows iterative development where partially correct files can be assembled for testing, similar to how modern compilers can continue after certain errors.

## Recommendations, Observations, and Considerations

------------------------------------------------
* The limit is 32767. This is because it's unsigned, meaning 15 unsigned bits. If you use a signed value, this would be equivalent to dividing this value into two parts (negative and positive). Negative values ​​like -16384 (which is 32767 because in binary it's 111111111111111) are not considered here. Therefore, 32767 = -1 and 16383 (positive) = 011111111111111, and -16384 = 100000000000000). So, if you use a signed value, negative or signed values ​​always start after 16383 (at 16384, where 16384 = -16384 and 16385 = -16383).

* Make sure to specify your operating system. Correct to avoid problems running the program (***supports Windows, macOS, and Unix/Linux***)

**NOTE:** If your operating system is not one that supports this, be sure to use the correct console cleanup command.

* ***Make sure the filename, variable names, and labels do not exceed 1023 characters, as data loss and unexpected events such as variable replacement could occur during program execution, since it only reads up to 1023 characters.***

* ***If for any reason there is an error creating or opening a file, check Windows security and disable real-time scanning or allow the compiler to manipulate files***

* The *only* case that **the code doesn't handle** is when there are ***nested block comments***

**EXAMPLE:**

~~~
/* /*This is a nested comment*/D=M

~~~

**EXPLANATION:** The **problem** is that the **code** looks for the `*/` after the start of a block comment (`/*`). Therefore, in the previous example, `D=M` will be treated as a statement, *even though the main block comment (the *first* `/*`) hasn't been closed.


**But if we put**

~~~
/* /*This is a nested comment*/D=M*/
~~~

***The code would indirectly identify it because the last `*/` identifies and warns of a syntax error in the instruction that is taken as a C instruction, as `D=M` from the previous example.***

***NOTE:*** This is because this happens in *rare cases* and is a ***practice that is not recommended***, due to cases like those in the previous code, which **can occur in other programs, not just this one**.

*Before reviewing the code (mainly from the `assembling.h` library), it is recommended to have **knowledge of the architecture of the *CPU* and the *ALU*** to understand certain parts of the code, such as the **ENSA** section.

-------------------------------------------------

## License

This project is licensed under the MIT License – see the [LICENSE](LICENCIA-LICENSE/LICENSE) file for details.

