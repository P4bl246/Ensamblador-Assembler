 README-Ensambaldor Hack en C
 # COMPILADOR/ENSAMBLADOR HACK EN C
  **Autor:** Pablo Riveros Perea
  
  **Proyecto:** Ensamblador Hack
  
  **Repositorio:**  [https://github.com/P4bl246]
  
  ------------------------------------------------------
 ## Dependencias

 ------------------------------------------------------
 Debe tener intalado *Dev C++/C* version 4.9 o posteriores, o un *compilador de C moderno*.
 
 [Instale Dev C++/C](https://sourceforge.net/projects/dev-cpp/)

 Librerias externas requeridas: 
  * `stdio.h` 
  * `stdlib.h` 
  * `string.h` 
 
 (no nesecita instalarlas si ya tiene *Dev C++/C* o un compilador moderno ya que normalmente estan integradas.)
 
## Instalación

------------------------------------------------------
1. Descargue la libreria `ensamblando.h` y el *ejecutable* `ensamblador.c` en la **misma carpeta** o **ruta** que la de el *compilador*.

2. Abra el ejecutable, y ingrese el nombre completo de su archivo .asm como argumento de la función `archivoA_txt` (el archivo debe de estar también en la *misma ruta*)
   
3. Ejecute el codigo y abra el archivo `archivoHack.hack` donde se encuentra el binario.

***NOTA:*** Todos los *archivos temporales*, y el archivo final *archivHack.hack* seran *creados localmente en la ruta*

**Recomendaciones de intalación**

* Cree una carpeta aparte para el *compildor* donde también va a poner la libreria `ensamblando.h` y su ejecutable `ensamblador.c`.
 
* Asegurese de **no** tener en la *misma ruta* (carpeta) otros *archivos* ***.txt*** debido a que podrian tener le *mismo nombre* que otros *archivos temporales* de el *ensamblador* y podria *eliminar su contenido* o haber *erroes en la ejecucion de el programa*

## Uso

------------------------------------------------------
Este programa esta *diseñado* para ensamblar lengueaje ensamblador HACK, o uno similar

**Ejemplo:**
~~~
@R0
D=M+1
A=D
@2
0;JMP
~~~

* Dentro de la libreria las etiquetadas en sus comentarios como **Funcion interna**, quieren decir que son **funciones pensadas para utilizar en la propia librería y no para uso fuera de esta**, pero si lo desea puede usararlas fuera de esta

* Si hay algún **error** para ver en donde fue el **error** con su numero de línea debe abrir el archivo ***copia.txt***

* Si quiere ver la ***tabla de símbolos*** abra el archivo **tabla.txt**

* Este programa **no** tiene las *mismas restricciones* que NAND2TETRIS en cuanto a la parte de *ensamblaje* de **COMP**(cálculo de las instrucciones C), debido a que puede agregar operaciones como 0+D o D+0, o otras recíprocas, debido a que luego esto se ajusta a el binario con su representación binaria.

  **EJEMPLO:**
  
  D+1 = 001111
  
  1+D = 001111

## Recomendaciones, Observaciones y Consideraciones

 ------------------------------------------------
* Este programa fue diseñado para ser ejecutado en un entorno de *Windows* por eso utiliza comandos de sistema como **CLS**, si se quiere utilizar para *MacOs* debe adaptar algunas partes de el código donde este *system("CLS")* por **CLEAR**
  
* ***Si por alguna razón hay algún error a el crear o abrir un archivo revise la seguridad de windows y desactive el analisis en tiempo real o permita a el compilador manipular archivos***

* Antes de revisar el codigo (de la libreria `ensamblando.h` principalmente), se recomienda tener **concimiento de la arquitectura de la *CPU* y la *ALU*** para entender ciertos fragmentos de el codigo como la parte de **ENSAMBLAJE**, esto estara en el [ARQUITECTURA.md](https://github.com/P4bl246/Ensamblador/blob/e50e91bbd4e8a84b83cbad30191bdc36ba5f4548/ARQUITECTURA.md) (*donde también se explicara porque hay ciertas operaciones y restricciones y como podrian integrarse más operaciones*).

* El diseño y creación de este programa se centra en la funcionalidad y escalabilidad y no tanto en la optimización (aunque se utilizan buenas practicas), esto es abierto a quien quiera mejorar el codigo optimizandolo de muchas maneras.

   **Ejemplos:**
    * Se podria mejorar la busqueda de valores en la tabla de simbolos por medio de *tablas hash*, en lugar de *busqueda lineal*.
    * Se podrian modular muchos bloques de código repetido como a el tomar el numero de linea.
 
* Este prgrama fue creado como proyecto final de la primera parte de el curso ***NAND2TETRIS*** por lo que para *ejecutar* el archivo *.hack* debe instalar el software de *NAND2TETRIS*
   [SOFTWARE DE NAND2TETRIS](https://www.nand2tetris.org/software)
  
   * Pasos para ejecutarlo en **Windows**
     
  1. Descomprima el archivo .zip
  
  2. Ingrese a la carpeta *nand2Tetris*

     ![image](https://github.com/user-attachments/assets/c79bfabc-fa18-473f-8a2d-430c16a5152c)
  
  3. Ingrese a *tools*
  
     ![image](https://github.com/user-attachments/assets/3d02e465-eb4d-4e3c-a30c-56852bfecdab)
  
  4. Abra *CPUEmulator.bat*
  
     ![image](https://github.com/user-attachments/assets/dd05c2ea-fe7c-45ab-b3a2-a39e5c8c57f9)

  5. Seleccione *Load ROM* o *Cargar Archivo*, y seleccione el archivo .hack y ejecute dando click en *>>* o *>*
     
     ![image](https://github.com/user-attachments/assets/49a07fc2-2d1d-4054-a7f1-43fb40156316)

**NOTA:** Para MacOs es lo mismo solo que ingresas a **_MACOSX** en lugar de **nand2Tetris**

-------------------------------------------------
