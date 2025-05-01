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
* f = +(si es 1) & (si es 0)
* no = !f (es decir niega lo que sale de f)
**NOTA:**En el ensamblador no vamos a utilizar *zr* ni *ng* entonces no lo presento aqui

### Explicación
Entonces vemos que en la arquitectura las entradas de el ALU son X y Y, y podemos observar que la entrada *X* en la CPU siempre es el **registro D** y la *Y* son los **registros M o A** (***M es el valor de la dirección actual, es decir el valor de la direccion de memoria actual o lo que almacena en la RAM***)

![image](https://github.com/user-attachments/assets/4e0670ad-81f7-4904-a1a7-623acfb09157)

Por esto vemos en la *estructura patron* X y Y y no A, M y D, porque no los vemos como registros sino como entradas de la *ALU* y dependiendo de los 6 bits de control se decide que hace la ALU porque estos sonlos que esta recibe, y con los operadores hacen lo mismo, solo nos interes el operador y cual es su representación binaria, que al obtenemos de la tabla de COMP que no da NAND2TETRIS, y obtnemeos los valores binarios de cada operador.

(Son los que estan marcados)

![image](https://github.com/user-attachments/assets/e87e0a3a-3e17-40aa-a614-13cda23bbaae)

Si obseravamos en la imagen en los operaradores hay un patron por ejemplo en el operador *!* podemos observar que el ultimo bit siempre esta en 1, y en la resta vemos que los ultimos 2 simpre estan en 1, y hay otro bit activo especial dependiendo de si X o Y esta antes de el operador **-**, y otros patrones de otros operadores. 

También podemos observa que dependiendo de como este el operador, es decir si esta antes o depues de el operando hay un cierto patron, como que si esta antes solo se pone el operando y el valor negativo que es 3 (000011), y tambien excepciones como en las constantes (0 y 1).

Estas son las razones por las que en los valores de *patron* puestos en *valores* son esos (aunque se pueden alterar siempre y cuando se ajuste todo el codigo para obtner el resultado deseado), y estos son enteros, porque no queremos tratar su representación binaria, sino entera que es mas facil de manejar, y luego podemos pasar esta a binario.

## AGREGAR NUEVOS OPERADORES

--------------------------------------------------------------
Entendiendo esto ahora puedes entender como agruegar *nuevos operadores* definiendo cual es su binario y poner este en entero en la *estructura patron* y su valor en *valores*, y luego agregarlo a el final de `función operador` con que se suma ese valor o que entero retornar y con sus diferenes casos posibles en el que el operador va antes y depues y en el caso de la constantes (todos los casos posibles y su representacion en entero) y listo asi podrian agreguar nuevos operadores.

## RECOMENDACIONES Y CONSIDERACIONES

------------------------------------------------------------
* Para mejorar la compresión de porque hay algunas partes en la `función operador` como ~(A+1) debe entender que es el **complemento a 2, y complemento a 1**, para binario y como se resta en binario
  
* Se recomienda hacer el curso de ***NAND2TETRIS parte 1*** para *entender completamente* y a fondo cada parte de la **CPU** y la **ALU**, este se encuentra en coursera

* En el ***analisis sintactico*** hay *restricciones de el maximo de direcciones* que puede ingresarse por lo que ya vimos anteriormente de la cantidad de registros que hay en la **ROM** (*que es la cantidad maxima que puede ser representada por 16 bits*)

[CURSO NAND2TETRIS PARTE 1](https://www.coursera.org/learn/build-a-computer)
