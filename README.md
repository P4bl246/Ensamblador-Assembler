 README-Ensamblador Hack en C
 # COMPILADOR/ENSAMBLADOR HACK EN C
  **Autor:** Pablo Riveros Perea
  
  **Proyecto:** Ensamblador Hack
  
  **Perfil:**  [https://github.com/P4bl246]
  
  ------------------------------------------------------

**[Don't understand ![English](https://flagcdn.com/w40/gb.png)](README.en.md)**



**NOTA:** Si no puedes usar ninguna extensión para traducir en tu IDE, puedes *crear un `codespace` en github* copiando este repositorio o el [código fuente](ENASAMBLADOR_PAQUETE)

[***No se crear un `codespace`***](https://docs.github.com/es/codespaces/developing-in-a-codespace/creating-a-codespace-for-a-repository)

 ## Dependencias

 ------------------------------------------------------
 Debe tener instalado *Dev C++/C* version 5.11 o posteriores, o un *compilador de C moderno*.
 
 [Descargue Dev C++/C](https://sourceforge.net/projects/orwelldevcpp/)

 Librerias externas requeridas: 
  * `stdio.h` 
  * `stdlib.h` 
  * `string.h` 
 
 (no necesita instalarlas si ya tiene *Dev C++/C* o un compilador moderno ya que normalmente estan integradas.)

**NOTA IMPORTANTE:** Si utiliza **VSCode y tienes problemas con la funcion `copiarValoresConVariables` debe cambiar** la *función* `copiarValoresConVariables` por este implementación
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

## Instalación

------------------------------------------------------
[Guía rápida](https://youtu.be/4FLMwUyRqTg)

1. Descargue la libreria `ensamblando.h` y el *ejecutable* `ensamblador.c` en la **misma carpeta** o **ruta** que la de el *compilador*.

2. Compile y ejecute el *ejecutable*, y ingrese el ***nombre completo de su archivo .asm*** para pasarlo como argumento a la función `archivoA_txt` (el archivo debe de estar también en la *misma ruta*)
   
3. Compile y ejecute el codigo y abra el archivo `archivoHack.hack` donde se encuentra el binario.

***NOTA:*** Todos los *archivos temporales*, y el archivo final `archivHack.hack` seran *creados localmente en la ruta*

**Recomendaciones de instalación**

* Cree una carpeta aparte para el *compilador* donde también va a poner la libreria `ensamblando.h` y su ejecutable `ensamblador.c`.
 
* asegúrese de **no** tener en la *misma ruta* (carpeta) otros *archivos* ***.txt*** debido a que podrian tener le *mismo nombre* que otros *archivos temporales* de el *ensamblador* y podria *eliminar su contenido* o haber *errores en la ejecución de el programa*

## Uso

------------------------------------------------------
Este programa esta *diseñado* para ensamblar lenguaje ensamblador HACK, o uno similar

**Ejemplo:**
~~~
@R0
D=M+1
A=D
@2
0;JMP
~~~

* Dentro de la libreria, las funciones etiquetadas en sus comentarios como **Funcion interna**, quieren decir que son **funciones pensadas para utilizar en la propia librería y no para uso fuera de esta**, pero si lo desea puede usarlas fuera de esta.

* Si hay algún **error** para ver en donde fue el **error** con su numero de línea debe abrir el archivo ***copia.txt***

* Si quiere ver la ***tabla de símbolos*** abra el archivo **tabla.txt**

* Este programa **no** tiene las *mismas restricciones* que NAND2TETRIS en cuanto a la parte de *ensamblaje* de **COMP**(cálculo de las instrucciones C), debido a que puede agregar operaciones como 0+D o D+0, o otras operaciones equivalentes, esto se aplica para todos los operadores, debido a que luego esto se ajusta a el binario con su representación binaria.

  **EJEMPLO:**
  
  D+1 = 001111
  
  1+D = 001111
  
**NOTA IMPORTANTE:** El emulador de *NAND2TETRIS* no acepta 1-M que en realidad seria -M+1 pero como no acepta esta representación binaria (1+(!Y +1) (***la ALU si lo puede procesar pero el emulador no lo reconoce***)) entonces ser refactoriza a M-1 (*no es correcto, pero es lo que acepta el emulador entonces cada vez que se ponga algo como 1-M o 1-D o 1-A se refactoriza a M-1, A-1, D-1*) 

* Puede probar el ensamblador descargando el juego de [prueba Pong](Pong.asm) en la *misma ruta* de el *compilador y ensamblador*

## Decisiones de Diseño

------------------------------------------------------

### Arquitectura del Código

Este ensamblador está diseñado como un **programa de línea de comandos de propósito único** que procesa archivos secuencialmente a través de múltiples fases. Por simplicidad de despliegue y facilidad de compilación, todas las implementaciones de funciones están incluidas en el archivo header `ensamblando.h`.

**Razón:** Esto permite que los usuarios compilen el proyecto con un solo comando sin necesidad de sistemas de construcción complejos (Makefiles, CMake, etc.). Es ideal para un contexto educativo donde el enfoque debe estar en entender el ensamblador, no en dominar herramientas de construcción de C.

**Nota para desarrolladores:** Si deseas usar este código como biblioteca en otro proyecto, puedes fácilmente separar las implementaciones del header a un archivo `.c` correspondiente. Los encabezados de todas las funciones ya están correctamente declarados.

### Pipeline de Procesamiento Secuencial

El ensamblador procesa archivos en **múltiples fases secuenciales** donde cada fase prepara los datos para la siguiente:

1. **Conversión y Limpieza**: Conversión .asm → .txt, eliminación de espacios, comentarios y líneas vacías
2. **Análisis Sintáctico**: Validación completa de sintaxis antes de continuar
3. **Construcción de Tabla de Símbolos**: Identificación y organización de etiquetas y variables
4. **Ensamblaje**: Conversión a código máquina binario de 16 bits

**Razón:** Esta separación de responsabilidades hace que cada fase sea simple y enfocada. Cada función hace una cosa y la hace bien. No se requiere multithreading porque:
- Los archivos de ensamblador son pequeños (típicamente <10,000 líneas)
- El procesamiento es extremadamente rápido (milisegundos en hardware moderno)
- Las fases son inherentemente secuenciales (no puedes ensamblar antes de construir la tabla de símbolos)

### Manejo de Errores: Advertencias vs Errores Fatales

El ensamblador distingue entre:
- **Advertencias**: Problemas que no impiden el ensamblaje pero que el usuario debe conocer (ej: truncamiento de números >5 dígitos)
- **Errores fatales**: Problemas que corromperían la salida (ej: exceder el límite de variables)

**Razón:** Esto permite desarrollo iterativo donde archivos parcialmente correctos pueden ensamblarse para pruebas, similar a cómo los compiladores modernos pueden continuar después de ciertos errores.

## Recomendaciones, Observaciones y Consideraciones

 ------------------------------------------------
* El límite es de 32767, esto se debe a que es sin signo, es decir 15 bits sin signo, si usas signo esto seria igual a dividir este valor en 2 (negativos y positivos) aqui no se tienen en cuenta negativos como -16384(que es 32767 porque en binario es 111111111111111), entonces 32767 = -1 y 16383(positivo) = 011111111111111, y -16384 = 100000000000000), entonces si manejas signo los negativos o con signo, siempre empiezan despues de 16383 (en 16384, donde 16384 = -16384 y 16385= -16383)

* asegúrese de poner su sistema operativo correcto para evitar problemas en la ejecución de el programa (***soporta Windows, MacOs y Unix/Linux***)

  **NOTA:** Si su *sistema operativo no es alguno que soporta* asegúrese de colocar el **comando** de **limpieza de consola** correcto

* ***asegúrese de que el nombre de el archivo, y de sus variables y etiquetas no exceda los 1023 carácteres debido a que podrian perderse datos, y haber eventos inesperados durante la ejecución de el programa, como reemplazar variables, debido a que solo lee hasta 1023 carácteres***.
  
* ***Si por alguna razón hay algún error a el crear o abrir un archivo revise la seguridad de windows y desactive el análisis en tiempo real o permita a el compilador manipular archivos***

* El *único* caso que **no maneja el código** es cuando hay ***comentarios en bloque anidados***

  **EJEMPLO:**
  ~~~
  /* /*Esto es un comentario anidado*/D=M
  ~~~

**EXPLICACIÓN:** El **problema** está en que el **código** busca el `*/` despúes de que se indica el inicio de un comentario en bloque (`/*`) entonces en el ejemplo anterior `D=M` se tratara como una instrucción, *aunque no se hayan cerrado el comentario en bloque principal*, es decir el *primer* `/*`. 

**Pero si pusieramos** 

~~~
/* /*Esto es un comentario anidado*/D=M*/
~~~

***El código lo identificaria indirectamente debido a que el ultimo `*/` lo identifica y avisa como un error de sintaxis de la instrucción que es tomada `D=M` de el ejemplo anterior como instrucción C*** 

***NOTA:*** Esto se debe a que en *raros casos* sucede esto y es una ***práctica que no se recomienda***, debido a casos como los de el código anterior que **puede presentarse en otros programas no solo en este**

* Antes de revisar el codigo (de la libreria `ensamblando.h` principalmente), se recomienda tener **concimiento de la arquitectura de la *CPU* y la *ALU*** para entender ciertos fragmentos de el codigo como la parte de **ENSAMBLAJE**, esto estara en el [ARQUITECTURA.md](ARQUITECTURA.md) (*donde también se explicara porque hay ciertas operaciones y restricciones y como podrian integrarse más operaciones*).

* El diseño y creación de este programa se centra en la funcionalidad y escalabilidad y no tanto en la optimización (aunque se utilizan buenas practicas), esto es abierto a quien quiera mejorar el codigo optimizandolo de muchas maneras.

   **Ejemplos:**
    * Se podria mejorar la busqueda de valores en la tabla de simbolos por medio de *tablas hash*, en lugar de *busqueda lineal*.
    * Se podrian modular muchos bloques de código repetido como a el tomar el numero de linea.
 
* Este programa fue creado como proyecto final de la primera parte de el curso ***NAND2TETRIS*** por lo que para *ejecutar* el archivo `.hack` debe instalar el software de *NAND2TETRIS* o utilizar su *IDE ONLINE*
   [SOFTWARE DE NAND2TETRIS](https://www.nand2tetris.org/software)
  
   * Pasos para ejecutarlo en **Windows**
     
  1. Descomprima el archivo .zip
  
  2. Ingrese a la carpeta *nand2Tetris*

     ![image](https://github.com/user-attachments/assets/c79bfabc-fa18-473f-8a2d-430c16a5152c)
  
  3. Ingrese a *tools*
  
     ![image](https://github.com/user-attachments/assets/3d02e465-eb4d-4e3c-a30c-56852bfecdab)
  
  4. Abra *CPUEmulator.bat*
  
     ![image](https://github.com/user-attachments/assets/dd05c2ea-fe7c-45ab-b3a2-a39e5c8c57f9)

  5. Seleccione *Load ROM* o *Cargar Archivo*, y seleccione el archivo `.hack` y ejecute haciendo click en *>>* o *>*
     
     ![image](https://github.com/user-attachments/assets/49a07fc2-2d1d-4054-a7f1-43fb40156316)


**NOTA:** Para MacOs es lo mismo solo que ingresas a **_MACOSX** en lugar de **nand2Tetris**

* Si utiliza el **IDE de NAND2TETRIS ONLINE** ingrese a el **CPU Emulator** y cargue el `.hack` dando en el ícono de carpeta
  
   ![image](https://github.com/user-attachments/assets/9b18f438-43f0-4db7-8735-98b1a8ef9f93)
-----------------------------------------------------------------------------

### Características que Distinguen Este Ensamblador
-------------------------------------------
#### 🔧 Flexibilidad en Operaciones
A diferencia del ensamblador estándar de NAND2TETRIS, este soporta:
- **Conmutatividad**: `D+1`, `1+D`, `A+1`, `1+A` son todos válidos
- **Operaciones con cero**: `D+0`, `0+D`, `M-0` funcionan correctamente
- **Múltiples representaciones**: El ensamblador internamente ajusta todo al binario correcto

#### 📝 Mensajes de Error Detallados
Cuando hay errores, el ensamblador proporciona:
- Número de línea exacto donde ocurrió el error
- Descripción detallada del problema
- Sugerencias de cómo corregirlo
- Ejemplos de sintaxis correcta

**Ejemplo de mensaje de error:**
```
ERROR en la linea 15
DETALLES: no se reconoce esta sintaxis de etiqueta, corrijala poniendo solo letras 
o coloque una letra primero antes del numero
EJEMPLO: (1234) no se reconoce o (1234h) no se reconoce, (h1234) se reconoce
```

#### ⚠️ Sistema de Advertencias Inteligente
- **Truncamiento numérico**: Advierte pero continúa si un número tiene >5 dígitos
- **Límites de memoria**: Advierte cuando te acercas a los límites arquitectónicos
- **Opción de continuar**: Pregunta al usuario si desea continuar después de advertencias
  ## Casos de Prueba y Validación

------------------------------------------------------

Este ensamblador ha sido **exhaustivamente probado** con múltiples casos que incluyen:

### ✅ Casos Básicos Validados
- Instrucciones A simples: `@0`, `@100`, `@32767`
- Instrucciones C básicas: `D=A`, `M=D`, `A=M`
- Etiquetas: `(LOOP)`, `(END)`, `(START)`
- Variables: `@counter`, `@temp`, `@sum`

### ✅ Casos Avanzados Validados
- Operaciones complejas: `D=D+A`, `M=M-1`, `D=D&A`, `D=D|M`
- Saltos condicionales: `D;JGT`, `D;JEQ`, `M;JLE`
- Instrucciones completas: `AMD=D+1;JMP`
- Combinación de etiquetas y variables en el mismo archivo

### ✅ Casos Límite y Manejo de Errores
- ✔️ **Números muy grandes**: `@999999999` → Trunca a 5 dígitos con advertencia
- ✔️ **Límite de memoria**: `@32767` funciona, `@32768` genera advertencia
- ✔️ **Máximo de variables**: Detecta cuando se exceden 16,383 variables únicas
- ✔️ **Nombres largos**: Maneja variables/etiquetas hasta 1023 caracteres
- ✔️ **Comentarios**: Simples `//`, en bloque `/* */`, mezclados con código
- ✔️ **Formato flexible**: Espacios extra, tabulaciones, líneas vacías

### ✅ Extensiones sobre NAND2TETRIS Estándar
- **Operaciones conmutativas**: `D+1` y `1+D` son equivalentes y ambos válidos
- **Operaciones con cero**: `0+D`, `D+0`, `0-D` se manejan correctamente
- **Formato flexible**: Tolera espacios inconsistentes y formato variado

### 🎮 Prueba con Programa Real
El ensamblador ha sido validado con el juego **Pong.asm** completo del curso NAND2TETRIS, produciendo salida binaria idéntica al ensamblador oficial.

**Para probar tú mismo**: Descarga [Pong.asm](Pong.asm) y ensámblalo. Compara el `.hack` generado con el oficial usando el CPU Emulator de NAND2TETRIS.
## Preguntas Frecuentes (FAQ)

------------------------------------------------------

**P: ¿Por qué aparecen archivos .txt en mi carpeta después de ejecutar?**

R: El ensamblador crea archivos temporales durante el procesamiento (`archivo.txt`, `tabla.txt`, `copia.txt` si hay errores). Si el ensamblaje fue exitoso, la mayoría se eliminan automáticamente. `tabla.txt` se conserva para que puedas inspeccionar la tabla de símbolos.

---

**P: ¿Puedo usar este ensamblador para otros proyectos más allá de NAND2TETRIS?**

R: Sí, siempre que tu arquitectura objetivo sea compatible con HACK (16 bits, misma estructura de instrucciones A y C). Puedes extender los operadores modificando la estructura `patron` en `ensamblando.h`.

---

**P: ¿Por qué necesito la versión alternativa de `copiarValoresConVariables` en VSCode?**

R: Algunos compiladores modernos optimizan el código de manera diferente. La versión alternativa usa `sprintf` en lugar de manipulación directa de buffers, lo cual es más compatible entre diferentes compiladores.

---

**P: ¿Puedo procesar múltiples archivos .asm a la vez?**

R: No directamente, este ensamblador procesa un archivo a la vez. Para procesar múltiples archivos, ejecútalo varias veces o crea un script batch/shell que lo llame iterativamente.

---

**P: ¿Qué hago si obtengo "ERROR al crear archivo"?**

R: Verifica:
1. Que tienes permisos de escritura en la carpeta
2. Que no hay archivos .txt abiertos en otros programas
3. En Windows: Desactiva temporalmente el antivirus o permite la aplicación
4. Que el disco no está lleno

---

**P: ¿Este ensamblador produce salida idéntica al oficial de NAND2TETRIS?**

R: Sí, el código máquina generado es funcionalmente idéntico. Cualquier diferencia sería solo en el manejo de casos extremos o extensiones (como `1+D` que el oficial no soporta).
-------------------------------------------------
## Licencia

este proyecto se creo bajo la licencia MIT – puedes ver la [LICENCIA](LICENCIA-LICENSE/LICENCIA) para mas detalles.
