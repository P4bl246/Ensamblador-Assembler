 # ARQUITECTURA DE LA COMPUTAODRA HACK
La computadora HACK es una computadora simple compuesta por una CPU, una ROM y una RAM de buses de 16 bits

[SITIO NAND2TETRIS DONDE ENCONTRARAN TODOS LOS RECURSOS Y DIAPOSITIVAS](https://www.nand2tetris.org/course)

-------------------------------------------------------
## Arquitectura CPU

-------------------------------------------------------
La **CPU** esta compuesta de:
* ALU (Unidad Aritmetica Lógica)
* PC (Program Counter)
* Registros (A y D)

## Arquitectura RAM

-------------------------------------------------------
La **RAM** esta compuesta de:
* 24576 Registros
Estos *registros* se dividen en 3:
* Registros de *uso general* (0-16383)
* Registros *reservados* para la *pantalla* (16384-24575)
* Registro *reservado* para el *teclado* (24576)

## Arquitectura ROM

-------------------------------------------------------
la **ROM** esta compuesta de:
* 32767 Registros

***NOTA:*** En la **ROM** es donde se carga el *lenguaje ensamblador* (HACK) o el *binario directamente* es decir las instrucciones
# FLUJO
-------------------------------------------------------
ROM->CPU->RAM

![image](https://github.com/user-attachments/assets/1b1d242e-1812-4baa-af41-4f233b039d01)

[AQUI PUEDEN VER LA ARQUITECTURA DETALLADA DE *NAND2TERIS*](https://drive.google.com/file/d/1Z_fxYmmRNXTkAzmZ6YMoX9NXZIRVCKiw/view)

## ALU
----------------------------------------------------
La ALU tiene 6 bits de control que dependiendo de su estado (0 o 1) se activa una función

![image](https://github.com/user-attachments/assets/8dd81865-69c0-42df-952f-d8495d953836)

[ALU NADN2TETRIS DETALLADO](https://drive.google.com/file/d/1ie9s3GjM2TrvL7PrEZJ00gEwezgNLOBm/view)

* zx = x = 0 (*poner x a 0*)
* nx = !x (*negar X*)
* zy = z = 0 (*poner Y a 0*)
* ny = !y (*negar Y*)

**NOTA:**En el ensamblador no vamos a utilizar *zr* ni *ng* entonces no lo presento aqui

### Explicación
Entonces vemos que en la arquitectura las entradas de el ALU son X y Y, y podemos observar que la entrada *X* en la CPU siempre es el **registro D** y la *Y* son los **registros M o A** (***M es el valor de la dirección actual, es decir el valor de la direccion de memoria actual o lo que almacena esta en la RAM***)

![image](https://github.com/user-attachments/assets/4e0670ad-81f7-4904-a1a7-623acfb09157)
