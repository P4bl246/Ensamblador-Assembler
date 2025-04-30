#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// =============================
// Autor: Pablo Riveros
// Proyecto: Compilador Hack
// Fecha: 2025-04-29
// Enlace GITHUB: https://github.com/P4bl246/Ensamblador.git
// =============================
//FUNCIONES DE ANALISIS SINTACTICO ANTES DE SEGUIR-----------------------------------------------
int copia_archivo(const char* archivo); //funcion para copiar el archivo original .txt en otro archivo(funcion interna)
//-----------------------------------------------------------------
int analizar_etiquetas(const char* archivo); //funcion para extraer las etiquetas y las anzaliza
//-----------------------------------------------------------------
int analizar_instrucciones_A(const char* archivo);//funcion para verificar que la sintaxis sea correcta en las instrucciones A(funcion interna)
//-----------------------------------------------------------------
int extraer_instrucciones_C(const char* archivo);//funcion que integra la funcion anteriror y le da los parametros(funcion interna)
//-----------------------------------------------------------------
int instruccionDestino(int actual, FILE* archivo, char* nlinea);//funcion para verificar la sintaxis de la parte de destino
int instruccionSalto(int actual, FILE* archivo, char* nlinea);//funcion para verficar la sintaxis de la parte de el salto
int instruccionCalculo(int actual, FILE *archivo, char* nlinea);//funcion para verficar la sintaxis de la parte de calculo
int tipoDeInstruccion(int actual, FILE* soloC, char* nlinea);//funcion que integra las 3 funciones anteriroes y verifica la parte de calculo y otros casos 
//-----------------------------------------------------------------
int organizar_instrucciones(const char* archivoC, int cantidad);//funcino que integra la funcion anteriror
int verficar_Formato_lineas(const char* archivo, int cantidad_Lineas_copia_completa);//funcion para verficar que el tamño de las instrucciones C sea el correcto
int analizar_instrucciones_C(const char* archivo);//funcion que integra las 2 funiones anteriroes
//-----------------------------------------------------------------
int eliminarArchivos();//funcion para eliminar los archivos creados durante el analisis sintactico
int analisis_sintactico(const char* archivo); // funcion que integra las funciones anteriroes principales como 'analizar_cadena', 'copiar_archivo', 'analizar_instruccion_A', y analizar_instruccion_C
//AQUI TERMINAN LAS FUNCIONES DE ANALISIS SINTACTICO-----------------------------------------------------------------

//FUNCIONES DE PREPRACION DE ARCHIVO---------------------------------------------------------------------
int ArchivoA_txt(const char* nombre_archivo); //Funcion para pasar el archivo .asm a .txt
//-----------------------------------------------------------------
char* eliminarEspaciosPreservarSalto(char *str); //Funcion para eliminar los espacios en el archivo .txt generado(funcion interna)
char *eliminar_comentario_simple(char *cadena);// Funcion para eleminiar los comentarios simpes de el arhcivo .txt(funcion interna)
void eliminar_comentario_bloque(FILE *archivoLeer, FILE* archivoEscribir); //Funcion para eliminar los comentarios en bloque de el archvi .txt(funcion interna)
char* eliminarLineas_vacias(char* cadena); // funcion para eliminar las lineas vacias de el archivo .txt(fucnio interna)
int limpiarLineas(const char *archivo);// funcion que integra las 4 funciones anteriores y entrega el arhcivo .txt limpio, reemplazando el viejo, con el nuevo(el limpio)
//-----------------------------------------------------------------
int tablaDeSimbolos(); //funcion para crear la tabla de simbolo predeterminada o basica
//-----------------------------------------------------------------
int encontrarEtiquetas(FILE* archivoLeer, FILE* archivoEscribir); //identificar las etiquetas y organizarlas(funcion interna)
int tratarEtiquetas(const char *nombre_de_archivo); // integra la funcino anterior y le da los parametros
//-----------------------------------------------------------------
int encontrarvar(FILE* archivoLeer, FILE* archivoEscribir);//idetneficar las variabeles y organizarlas(funcion interna)
int tratarVariables(const char *nombre_de_archivo);//integra la funcion anterior
//-----------------------------------------------------------------
//se ponen a parte porque la primera sirver para mostrar la advertencia y si decide continuar se ejecutan estas funciones
int encontrarvar2(FILE* archivoLeer, FILE* archivoEscribir);//idetneficar las variabeles y organizarlas solo tomando los primeros 5 digitos numericos(funcion interna)
int tratarVariables2(const char *nombre_de_archivo);//integra la funcion anterior
//-----------------------------------------------------------------
int numerarLineas(const char* archivoLeer);// funcion para numerar las lineas de el 1 a las que haya 1...n incluyendo las estiquetas
//-----------------------------------------------------------------
void copiarLineasConEtiqueta(FILE *archivoLeer, FILE *archivoEscribir); // funcion que solo escribe las lineas de etiquetas en el archivo etiquetas.txt(funcion interna)
void contenidoEtiquetas(FILE *archivoLeer, FILE* archivoEscrbir); //funcion que solo escribe el contenido dentro de los parentesis de la etiqueta
int separarEtiquetas(const char* archivo); //funcion que integra las 2 funciones anteriores y le da los paramentros
//-----------------------------------------------------------------
int cantidadDeLineas(FILE *archivoLeer); //funcion que devuelve la cantidad de lineas de un archivo (funcion interna)
int separaDigitosdeLetras(FILE* archivoLeer, char** poner_cadenas, char** poner_digitos, int n_lineas);//funcino para separar la cadena de digitos y la cadena de letras(funcion interna)
int mas_simbolos(const char* archivo_de_datos);// funcion para agregar nuevos simbolos a la tabla de simbolos, integra las 2 fucniones anteriores
//-----------------------------------------------------------------
void excluir(FILE *archivoLeer, FILE *archivoEscribir); //funcion para encontrar y excluir variables predefinidas como R0...R15, SCREEN, y KBD
void encontrarVariables(FILE* archivoLeer, FILE* archivoEscribir); // funcion para encontrar las variables y ponerlas en un archivo aparte(funcion interna)
void eliminarDuplicados(FILE *archivoLeer, FILE* archivoEscribir); // funcion para eliminar los duplicados o lineas duplicadas en un archivo(funcion interna)
int copiarValoresConVariables(FILE *archivoLeer, FILE *archivoEscribir);//funcion para asginar valores a las variables, o clave-valor, para luego usar la funcion 'mas_simbolos'(funcion interna)
int separarVariables(const char* archivo);//integra las 4 funciones anteriores y 'mas_simbolos', y les da los argumentos, estos es para crear los simbolos de las variables y 'vertificarVarYEtiq'
//-----------------------------------------------------------------
char *etiq(char* cadena, FILE *etiq);//funcion para tomar cada cadena y numero de linea de etiquetas.txt
int verificarVarYEtiq(FILE* archivoLeer,FILE* archivoComparar, FILE* archivoEscribir);//funcion que integra la funcion anteriror y compara cada cadena de archivoLeer con cada cadena de archivoComaprar y pone las no repetidas en el archivoEscribir
//-----------------------------------------------------------------
int limpiartxtPr(const char* archivo);//funcion para limpiar el archivo .txt principal de las etiquetas
//-----------------------------------------------------------------
void eliminarDuplicadosTabla(FILE *archivoLeer, FILE *archivoEscribir); //funcion para solo dejar las etiquetas si hay un caso en el que se haya puesto una variable con el mismo nombre de una etiqueta dejar la etiqueta(funcion interna)
int limpiar_tabla(); //funcion para limpiar la tabla de simbolos eliando simbolos repetidos si hay y integra la funcion anterior y de 'eliminarDuplicados'
//------------------------------*********************************
//AQUI TERMINAN LAS FUNCIONES DE LIMPIEZA Y PREPARACION-----------------------------------------------------------------

//FUNCIONES DE ENSAMBLAJE DE INSTRUCCIONES-----------------------------------------------------------------------
int tomarInstruccionesAyC (const char* archivo, int cantidad);//toma las instrucciones A y C de el archivo y su numero de linea para luego pasarlo a binario(funcion interna)
//-----------------------------------------------------------------
int buscarValor(FILE* tabla,char *cadena, int cantidad);//funcion para obtener el valor de la tabla (funcion interna)
char *EnteroABin(int valor_entero);//convierte el valor entero a binario y lo devuelve en una cadena(funcion interna)
int ensamblarA(const char *Ains, int cantidad);//funcion que integra las 2 funciones anteriores y les da los parametros para ensamblar linea por linea (pasarlo a binario)(funcion interna)
//-----------------------------------------------------------------
char *bitsDestino(char *destino);//vuelve el destino a su forma binaria(funcion interna)
char *destino(char *actual, char** copiaLineaActualizado);//trata la parte de destino en una instruccionC si hay, integra la funcion anterior(funcion interna)
//-----------------------------------------------------------------
char* salto(char* actual);//trata la parte de salto de una instruccion C (funcion interna)
//-----------------------------------------------------------------
//estructura que almacena los bits de esa linea que se le asignaron a la aprte de dest=comp;jmp
typedef struct {
	char *destino;
	char* comp;
	char* jump;
	char M;
}Cins;
//-----------------------------------------------------------------
char *tomarlos6(char *punt);//toma los 6 bits que queremos que son los primeros y ignora los otros 10 que devuelve 'EnteroABin'(funcion interna)
char* operandoA(char *actual, char**actualizado, char* conM);//trata el operandoA o la parte A de un calculo que simpre es D porque en la entrada X de la ALU siempre es D integra la funcion de enteroAbinario(funcion interna)
int constante(char *actual, char**actualizado, char anterior, char* conM);//trata la constante 1 y sus diferentes casos(funcion interna)
int operador(char *actual, char**actualizado, char anterior, char* conM);//trata la parte de los "calculos" si hay operador, es decir la parte A operador B (A+B, A-B y otras(esto lo trata), A(no lo trata) -A...(lo trata))(funcion interna) 
char* calculo(int actual, FILE* leer);//integra las funciones anteriroes y destino y salto y trata la parte de calculo integrando las funcones anteriores, y de ensamblarFinal(funcion interna)
//-----------------------------------------------------------------
char* ensamblarFinal(Cins completo);//toma la estructura y sus valores que son los que devolvieron las funciones principales anteriores y los une en una cadena(funcion interna)
//-----------------------------------------------------------------
void IdentificarInstruccion(FILE *insC, FILE *EscribirEnsamblado);//integra la funcion pricipal que integra todas las anterioeres que es calculo y le da los parametros
int ensamblarC(const char* Cins, int cantidad);//integra la funcion anteriores;
//-----------------------------------------------------------------
int leerNumero(const char* linea, int cantidad);//obtiene el numero de linea (funcion no utilizada en ninguna otra funcion (posible mejora))
int leerYOrdenarYEscribir(FILE* archivo1,  FILE* archivo2, FILE* archivoEscribir, int cantidad);//organiza las instrucciones ya ensambladas según su numero de linea, y integra la funcino anterior (funcion interna)
//-----------------------------------------------------------------
int archivoHack(const char* ensamblado);//ultima funcion de ensamblar para crear el archivo final que es el archivo .hack
//-----------------------------------------------------------------
int ensamblar(const char* archivo);// integra las funciones principales anteriores como ensamblarC y ensmblarA y las organiza
 
//AQUI TERMINAN LAS FUNCIONES DE ENSAMBLAJE DE INSTRUCCIONES--------------------------------------------------------


//AQUI SE HACE EL PROCESO DE ANALISIS SINTACTICO-------------------------------------
//**************************************************************
int analisis_sintactico(const char* archivo){
	int n;
	n =copia_archivo(archivo);
	if(n != 0) return 1;
	
	n = limpiarLineas("copia.txt");
	if(n != 0) return 1;
	
	n = tratarEtiquetas("copia.txt");
	if(n != 0) return 1;
	
	n = tratarVariables("copia.txt");
	if(n != 0) return 1;
	
	n = numerarLineas("copia.txt");
	if(n != 0) return 1;
	system("cls");
	n = analizar_etiquetas("copia.txt");
	if(n != 0) return 1;
	
	n =analizar_instrucciones_A("copia.txt");
	if(n != 0) return 1;
	
	n = tratarVariables2("copia.txt");
	if(n != 0) return 1;
	
	n = analizar_instrucciones_C("copia.txt");
	if(n != 0) return 1;
	
	n = eliminarArchivos();
	if(n != 0) return 1;
	
	system("cls");
	printf("ANALISIS SINTACTICO COMPLETADO\n\n");
	return 0;
}
//-----------------------------------------------------------------
int copia_archivo(const char* archivo){
	FILE *archivoP = fopen(archivo, "r");
	if(archivoP == NULL){
		printf("No se encontro el archivo '%s'\n", archivo);
		return 1;
	}
	printf("Se abrio exitosamente el archivo '%s'\n", archivo);
	
	FILE *copia = fopen("copia.txt", "w");
	if(copia == NULL){
		printf("ERROR a el crear el archivo 'copia.txt'\n");
		fclose(archivoP);
		return 1;
	}
	char linea[1024];
	while(fgets(linea, sizeof(linea), archivoP) != NULL){
		fputs(linea, copia);
	}
	printf("Se llego creo la copia de el archivo '%s' exitosamente\n", archivo);
	
	fclose(archivoP);
	fclose(copia);
	return 0;
}
//-----------------------------------------------------------------
int analizar_etiquetas(const char* archivo){
	printf("ANALIZANDO LAS ETIQUTEAS...\n");
	FILE *copia = fopen(archivo, "r");
	if(copia == NULL){
		printf("No se encontro el archivo '%s'\n", archivo);
		return 1;
	}
	printf("Se abrio el archivo '%s'\n", archivo);
	
    int numeroLinea;
    int i;
    int cantidad = cantidadDeLineas(copia);
    char n_lineas[cantidad]; //obtenemos la cantidad de lineas que hay para poder obtener los caracteres necesaciros para el numero de linea
    int actual;
    rewind(copia);
    // Procesamos línea por línea
    while(!feof(copia)) {
        // Limpiar los buffers
        memset(n_lineas, 0, sizeof(n_lineas));
        actual = fgetc(copia);
        i = 0; //acumulador
        //tomamos el numero de linea y luego lo convertimos a entero 
        while((char)actual != ' ' && actual != EOF) {
            n_lineas[i] = (char)actual;
            i++;
            actual = fgetc(copia);
        }
        n_lineas[i] = '\0';
        
        numeroLinea = atoi(n_lineas);
        // Leer el siguiente carácter (después del espacio)
        actual = fgetc(copia);
        
        // Procesar instrucción si es una etiqueta
        if(actual == '(') {
            actual = fgetc(copia);
            //si no hay nada mostrar un error
            if(actual == EOF || (char)actual == '\0' ||(char)actual == '\n' ||(char)actual == ' ') {
                printf("ERROR en la linea %d\n", numeroLinea);
                printf("DETALLES: Se esperan caracteres despues de el '('\n");
                fclose(copia);
                return 1;
            }
            
            // Leer si hay numro despues de '('
            if((char)actual >= '0' && (char)actual <= '9') {
                        printf("ERROR en la linea %d\n", numeroLinea);
                        printf("DETALLES: no se reconoce esta sintaxis de etiqueta, corrijala poniendo solo letras o coloque una letra primero antes de el numero\nEJEMPLO: (1234) no se reconoce o (1234h) no se reconoce, (h1234) se reconoce\n");
                        fclose(copia);
                        return 1;
                    }
                }
                while((char)actual != '\n' && actual != EOF){
                	actual = fgetc(copia);
				}
           }
      printf("TERMINO EL ANALISISI DE ETIQUETAS\n");     
    fclose(copia);
    return 0;
}
//-----------------------------------------------------------------
int analizar_instrucciones_A(const char* archivo) {
	printf("\nANALIZANDO INSTRUCCIONES A...\n");
    FILE *copia = fopen(archivo, "r");
    if(copia == NULL) {
        printf("No se encontro el archivo '%s'\n", archivo);
        return 1;
    }
    printf("Se abrio el archivo '%s'\n", archivo);
    
    int n, i;
    char numeros[6]; // Aumentado a 6 para garantizar espacio para el \0
    int cantidad = cantidadDeLineas(copia);
    char *n_lineas = (char*)malloc(cantidad); //obtenemos la cantidad de lineas que hay para poder obtener los caracteres necesaciros para el numero de linea
    int actual;//caracter actual
    char continuar;//si hay advertencias saber si se desea continuar con la ejecucion
    rewind(copia);//rebobinar el archivo debido a que ya lo leimos hasta el finlas a el tomar la cantidad de lienas
    int advertencia = 0;//si hay advertencias
    // Procesamos línea por línea
    while(1) { 
        // Limpiar los buffers
        memset(n_lineas, 0, sizeof(cantidad));
        memset(numeros, 0, sizeof(numeros));
        actual = fgetc(copia);
        if(actual == EOF) break;
        i = 0; //acumulador
        while((char)actual != ' ' && actual != EOF) {
            n_lineas[i] = (char)actual;
            i++;
            actual = fgetc(copia);
        }
        n_lineas[i] = '\0';
        // Leer el siguiente carácter (después del espacio)
        actual = fgetc(copia);
        
        // Procesar instrucción si es de tipo @
        if(actual == '@') {
            actual = fgetc(copia);
            
            if(actual == EOF || (char)actual == '\n' || (char)actual == ' ' || (char)actual == '\0') {
                printf("ERROR en la linea %s\n", n_lineas);
                printf("DETALLES: Se esperan argumentos despues de el '@'\n");
                fclose(copia);
                free(n_lineas);
                return 1;
            }
            
            // Leer número después de @
            n = 0;
            if((char)actual >= '0' && (char)actual <= '9') {
                numeros[n] = (char)actual;
                n++;
                // si hay mas digitos
                while(1) {
                    actual = fgetc(copia);//vamos a el siguietne caracter
                    //si es fin de linea
                    if((char)actual == '\n' || actual == EOF ) {
                        break;
                    }
                    //si se alcanzo el maximo de digitos numericos esperados
                    if(n == 5){
                    	//comprobar si no hay mas digitos o si hay mas mostrar advertencia
                    	if(actual != EOF && (char)actual != '\n'){
                    		printf("ADVENTERNCIA: en la linea %s\n", n_lineas);
                    		printf("DETALLES: No se esperan mas de 5 digitos numericos debido a que solo hay 15 bits entonces el numero maximo es 32767 que es de 5 bits\ny no se tendran en cuenta(se ignoraran)despues de los 5 digitos\n");
                    		advertencia = 1;
						}
						break;//salimos de el bucle y ignoramos los otros caracteres
					}
					//si no se alcanzo el numero comprobar que no haya letras despues de digitos numericos
                    if(!((char)actual >= '0' && (char)actual <= '9')) {
                        printf("ERROR en la linea %s\n", n_lineas);
                        printf("DETALLES: no se reconoce esta sintaxis, corrijala poniendo un numero de 0-n o coloque el caracter primero\nEJEMPLO: @1234 o @h1234. @1234h(no se reconoce)\n");
                        fclose(copia);
                        free(n_lineas);
                        return 1;
                    }
                    //si es un digito y no se a alcanzado el numero maximo de digitos leer los digitos
                    numeros[n] = (char)actual;
                    n++;
                }
                
                numeros[n] = '\0';
            }
            int contenido = atoi(numeros);//convertimos la cadena a entero
            //comprobar si el numero es mayor a 32767
            if(contenido > 32767){
            	printf("ADVERTENCIA: en la linea %s\n", n_lineas);
            	printf("DETALLES: El numero de la instruccion A no debe ser mayor a 32767 de lo contrario\n podria haber eventos inseperados duranto el ensamblaje de al instruccion debido a que son solo 15 bits\n");
            	advertencia = 1;
			}
        // Avanzar hasta el final de la línea
        while((char)actual != '\n' && actual != EOF) {
            actual = fgetc(copia);
        }
  }
}
   if(advertencia != 0){
   	printf("\n¿DESEA CONTINUAR CON LA EJECUCION DE EL PROGRAMA?(Y/N)\n");
   scanf(" %c", &continuar);
   while(continuar != 'Y' && continuar != 'N'){
    printf("¿DESEA CONTINUAR CON LA EJECUCION DE EL PROGRAMA?(Y/N)\n");
    scanf(" %c", &continuar);
	}
	//si es N parar la ejecucion
	if(continuar == 'N'){
		printf("SE INTERRUMPIO LA EJECUCION DE EL PROGRAMA\n");
		fclose(copia);
		free(n_lineas);
		return 1;
	}
	//si no es decir si es Y continuar
	printf("TERMINO EL ANALIZIS DE INSTRUCCIONES A\n");
    fclose(copia);
    free(n_lineas);
    return 0;
   }
   //si no hubieron advertencias
   printf("TERMINO EL ANALIZIS DE INSTRUCCIONES A\n");
    fclose(copia);
    free(n_lineas);
    return 0;
}
//-----------------------------------------------------------------
int analizar_instrucciones_C(const char* archivo){
	printf("\nANALIZANDO INSTRUCCIONES C...\n");
	
	FILE *copia = fopen(archivo, "r");
    if(copia == NULL){
    	printf("No se encontro el archivo 'analizarLineas.txt'\n");
    	return 1;
	}
	printf("Se abrio el archivo 'analizarLineas.txt'\n");
	int cantidad = cantidadDeLineas(copia);
	fclose(copia);
	
	int n =extraer_instrucciones_C(archivo);
	if(n != 0) return 1;
	
	int n1=verficar_Formato_lineas("analizarLineas.txt", cantidad);
	if(n1 != 0) return 1;
	
	
	int n2 = organizar_instrucciones("analizarLineas.txt", cantidad);
	if(n2 != 0) return 1;
	
	printf("TERMINO EL ANALISIS DE INSTRUCCIONES C\n");
	return 0;
}
//-----------------------------------------------------------------
int extraer_instrucciones_C(const char* archivo) {
    printf("\nEXTRAYENDO INSTRUCCIONES C...\n");

    FILE *copia = fopen(archivo, "r");
    if (copia == NULL) {
        printf("No se encontro el archivo '%s'\n", archivo);
        return 1;
    }
    printf("Se abrio el archivo '%s' exitosamente\n", archivo);

    FILE *copia2 = fopen("analizarLineas.txt", "w");
    if (copia2 == NULL) {
        printf("ERROR al crear el archivo 'analizarLineas.txt'\n");
        fclose(copia);
        return 1;
    }
    printf("Se creo el archivo 'analizarLineas.txt'\n");

    char linea[1024];
    // Leer línea por línea
    while (fgets(linea, sizeof(linea), copia) != NULL) {

        // Buscar el primer espacio en la línea
        char *espacio = strchr(linea, ' ');
        
            // Verificar el siguiente carácter después del espacio
            if (*(espacio + 1) == '(' || *(espacio + 1) == '@') {
                // Si el carácter después del espacio es '(' o '@', no copiamos la línea
                continue;
            }
        // Si no se cumple la condición, copiamos la línea a copia2
        fputs(linea, copia2);
    }
    printf("INSTRUCCIONES C EXTRAIDAS\n");

    fclose(copia);
    fclose(copia2);
    return 0;
}
//-----------------------------------------------------------------
int verficar_Formato_lineas(const char* archivo, int cantidad_Lineas_copia_completa){
	printf("\nVERIFICANDO FORMATO...\n");
	FILE* soloC = fopen(archivo, "r");
	if(soloC == NULL){
		printf("No se encontro el archivo '%s'\n", archivo);
		return 1;
	}
	printf("Se abrio el archivo '%s'\n", archivo);
	
	char nLinea[cantidad_Lineas_copia_completa];
	
	int actual = fgetc(soloC);
	while(actual != EOF){
		int i =0;
		memset(nLinea, 0, sizeof(nLinea)); //restablecemos el arreglo a '\0'
		while((char)actual != ' '){
			nLinea[i] = (char)actual;
			i++;
			actual = fgetc(soloC);
		}
		nLinea[i]= '\0';
		actual = fgetc(soloC); //vamos a el siguiente caracter despues de el espacio
		int cont = 0;
		//si despues de el espacio hay un final de linea es un error de formato
		if(actual == EOF || (char)actual == '\n'){
			printf("ERROR en la linea %s\n", nLinea);
			printf("DETALLES: No hay nada despues de el espacio, ERROR DE FORMATO(numeroLinea,espacio,instruccion)\nIntente volver a ejecutar el codigo\n");
			fclose(soloC);
			return 1;
		}
		while((char)actual != '\n' && actual != EOF){
			cont++;
			actual = fgetc(soloC);
		}
		//si el numero de caracteres en la intruccion es mayor a 10 es un error
		if(cont > 12){
			printf("ERROR en la linea %s\n", nLinea);
			printf("DETALLES: La instruccion C no puede ser mayor de 12 caracteres\n");
			fclose(soloC);
			return 1;
		}
		actual = fgetc(soloC);//ir a el siguietne caracter es decir la siguiente linea
	}
	printf("TERMINO LA VERFICACION DE FORMATO\n");
	fclose(soloC);
	return 0;
}
//**************************************************************

//**************************************************************
//-----------------------------------------------------------------
int organizar_instrucciones(const char* archivoC, int cantidad) {
    printf("\nVERIFICANDO SINTAXIS...\n");

    FILE* instrucciones = fopen(archivoC, "r");
    if (instrucciones == NULL) {
        printf("No se encontro el archivo '%s'\n", archivoC);
        return 1;
    }

    printf("Se abrio el archivo '%s'\n", archivoC);

    char nlinea[cantidad];
    int actual;
    int i = 0;

    while ((actual = fgetc(instrucciones)) != EOF) {
        memset(nlinea, 0, sizeof(nlinea));
        i = 0;

        // Leer número de línea hasta encontrar un espacio
        while (actual != ' ' && actual != EOF) {
            if (i < cantidad - 1) {
                nlinea[i++] = (char)actual;
            }
            actual = fgetc(instrucciones);
        }

        // Procesar la instrucción
        int result = tipoDeInstruccion(actual, instrucciones, nlinea);
        if (result != 0) {
            fclose(instrucciones);
            return 1;
        }
        // Avanzar hasta el comienzo de la próxima línea
        while (actual != EOF && (char)actual != '\n' &&(char)actual != '\0' &&(char)actual != ' ') {
            actual = fgetc(instrucciones);
        }
    }

    printf("SINTAXIS VERIFICADA\n");
    fclose(instrucciones);
    return 0;
}

//**************************************************************
//-----------------------------------------------------------------
int tipoDeInstruccion(int actual, FILE* soloC, char* nlinea) {
	char buffer;
	char buffer2[3];
	memset(buffer2, 0, 3);
	actual = fgetc(soloC);
    if ((char)actual != '\n') {
        // Si comienza con D, M, A, 1 o 0
        if ((char)actual == 'D' || (char)actual == 'M' || (char)actual == 'A'||(char)actual == '1'||(char)actual == '0') {
        	buffer= (char)actual;
        	buffer2[0] = (char)actual;//guradamos el caracter actual 
            actual = fgetc(soloC); // siguiente carácter
             //comprobamos que el siguietne caracter se +, -, | o &
            if ((char)actual == '+' || (char)actual == '-' || (char)actual == '|' || (char)actual == '&') {
                actual = fgetc(soloC); // siguiente carácter
                buffer2[1] = (char)actual;
                buffer2[2] = '\0';//cerramos correctamente
                //comprobamos que el siguiente caracter sea A, M, D, 1 o 0
                if ((char)actual == 'A' || (char)actual == 'D' || (char)actual == 'M' || (char)actual == '1' || (char)actual == '0') {
                    actual = fgetc(soloC); // siguiente carácter
                   
				   	//excepciones como que A y M no se pueden calcular
				   	if(buffer2[0] == 'A' && buffer2[1] == 'M' || buffer2[0] == 'M' && buffer2[1] == 'A'){
				   		printf("ERROR en la linea %s\n", nlinea);
				   		printf("DETALLES: No se pueden calcular A con M debido a la arquitectura de la CPU\n");
				   		fclose(soloC);
				   		memset(buffer2, 0, 3);
				   		return 1;
					   }
					 //si son iguales los operandos
				   	 else if(buffer2[0] == buffer2[1]){
				   	 	printf("ERROR en la linea %s\n", nlinea);
				   	 	printf("DETALLES: No se puede operar con la misma letra\n");
				   	 	fclose(soloC);
				   	 	memset(buffer2, 0, 3);
				   	 	return 1;
						}
				    
                   //comprobamos que el siguiente caracter sea ; o fin de linea
                    else if ((char)actual == '\n' || actual == EOF) {
                    	
                        return 0; // Solo cálculo
                    } else {
                    	//si no es final de linea entonces comprobamos que sea ;
                        if ((char)actual != ';') {
                            printf("ERROR en la linea %s\n", nlinea);
                            printf("DETALLES: Se espera el caracter ';' o fin de linea.\n");
                            fclose(soloC);
                            return 1;
                        }
						//si es ; llamamos a instruccionSalto para comprobar la sintaxis de el salto 
						else {
							
                            int h = instruccionSalto(actual, soloC, nlinea);
                            
                            if (h != 0) return 1;
                            else return 0; // Instrucción completa válida
                        }
                    }
                }
				//si el siguiente caracter despues del opeardor no es M, D, A, 1 o 0 es un error 
				else {
                    printf("ERROR en la linea %s\n", nlinea);
                    printf("DETALLES: Se espera 'M', 'D', 'A', '0' o '1' despues del operador.\n");
                    fclose(soloC);
                    return 1;
                }
            }
            //si no es +, -, | o &, comprobamos si es fin de linea
            else if((char)actual == '\n'||actual == EOF){
            	
            	return 0;
			}
            //si no  comprobamos que sea un ;
            else if((char)actual == ';'){
            	
            	int h2 = instruccionSalto(actual, soloC, nlinea);
            	
                if (h2 != 0) return 1;
                else return 0; // Instrucción completa válida
            	
			}
            //si no ; comprobamos que el caracter anteriro no sea 1 o 0, si es asi hay un error;
            else if(buffer != '0' && buffer != '1'){
            	
            	int n= instruccionDestino(actual, soloC, nlinea);//si es una instruccion de destino se verfica su sintaxis
            	
            	if(n != 0) return 1;
            	else return 0;
			}
			//si es 1 o 0 el caracter hay un error
            else{
            	printf("ERROR en la linea %s\n", nlinea);
            	printf("DETALLES: El destino no puede ser 1 o 0\n");
            	fclose(soloC);
            	return 1;
			}
        }

        // Si empieza con un operador como '-' o '!'
        else if ((char)actual == '-' || (char)actual == '!') {
            actual = fgetc(soloC);
            
            //verificamos que el siguiente caracter se A, D, M o 1
            if ((char)actual == 'M' || (char)actual == 'D' || (char)actual == 'A' || (char)actual == '1') {
                actual = fgetc(soloC);
                
                //vemos si el siguiente caracter es ; si es asi llamamos a instruccionSalto
                if((char)actual == ';'){
                	int h3=instruccionSalto(actual, soloC, nlinea);
                	
                	if(h3 != 0) return 1;
                	return 0;
				}
				//si no es ; y no es final de linea hay un error
				else if((char)actual != '\n'&& actual != EOF){
					printf("ERROR en la linea %s\n", nlinea);
					printf("DETALLES: Se espera un caracter ';' o nada despues de el caracter anterior A, M, D o 1\n");
					fclose(soloC);
					return 1;
				}
				else return 0;
            }
            //si el caracter despues de - o ! no es A, M, D o 1
			 else {
                printf("ERROR en la linea %s\n", nlinea);
                printf("DETALLES: Se espera A, M, D o 1 despues de '-' o '!'\n");
                fclose(soloC);
                return 1;
            }
        }
        //si no es alguno de estos caracteres hay un error
        else{
          printf("ERROR en la linea %s\n", nlinea);
          printf("DETALLES: Se espera un caracter A, M, D, 1 o 0\n");
          fclose(soloC);
          return 1;
		}
    }
    
    return 0;
}
//-----------------------------------------------------------------
int instruccionDestino(int actual, FILE* archivo, char* nlinea){
	
	if((char)actual == 'A'|| (char)actual == 'M'||(char)actual == 'D'){
		actual = fgetc(archivo);//pasamos a el siguiente caracter 
		
		//comprobamos que sea = o A,M o D
		// si es = comprobamos que despues haya una instruccion de calculo
		if((char)actual == '='){
			actual = fgetc(archivo);
			
			int n = instruccionCalculo(actual, archivo, nlinea);
			
			if(n != 0) return 1;
			else return 0;
		}
		//si es A, M o D
		else if((char)actual == 'A'||(char)actual == 'M'|| (char)actual == 'D'){
			actual = fgetc(archivo);//pasamos a el siguiente caracter
			
			//comprobamos que sea = porque solo pueden haber 3 caracteres de destino
			if((char)actual != '=' || actual == EOF){
				printf("ERROR en la linea %s\n", nlinea);
				printf("DETALLES: Se espera un signo '=' despues de el A, M, o D (de el tercer caracter)\n");
				fclose(archivo);//cerramos el archivo
				return 1;//es un error
			}
			// si es = comprobamos que haya una instruccion de calculo despues
			else{
				actual = fgetc(archivo);
				
				int n2 = instruccionCalculo(actual, archivo, nlinea);
				
				if(n2 != 0) return 1;
				else return 0;
			}
		}
		//si no es A, M o D 
		else{
			printf("ERROR en la liena %s\n", nlinea);
			printf("DETALLES: Se espera un caracter =, A, M o D despuse de el A,M o D(de el segundo caracter)\n");
			fclose(archivo);
			return 1;
		}
	}
	//si es = el segundo caracter
	else if((char)actual == '='){
		actual = fgetc(archivo);
		
		int h = instruccionCalculo(actual, archivo, nlinea);
		
		if(h != 0) return 1;
		else return 0;
	}
	// si no es = o A, M o D es un error
	else{
		printf("ERROR en la liena %s\n", nlinea);
		printf("DETALLES: Se espera un caracter =, A, M o D\n");
		fclose(archivo);
		return 1;
	}
}
//-----------------------------------------------------------------
int instruccionSalto(int actual, FILE* archivo, char* nlinea){
	
	if((char)actual == ';'){
		actual = fgetc(archivo);//ir a el siguiente caracter
		
		//comprobamos que el siguietne caractere sea J
		if(actual == EOF || (char)actual != 'J'){
			printf("ERROR en la linea %s\n", nlinea);
			printf("DETALLES: Se espera el caracter 'J'despues de el ';'\n");
			fclose(archivo);
			return 1;
		}
		actual = fgetc(archivo);//segumios a el siguiente caracter si el caracter anteriro fue J
		//si es J comrpobamos qeu el siguete caracter sea M, Q, E, L, N o G
		if((char)actual == 'M' ||(char)actual == 'N'||(char)actual =='Q'||(char)actual == 'E'||(char)actual=='L' ||(char)actual == 'G'){
			actual = fgetc(archivo);
			
			//comprobamos que el siguieten caracter se T, Q, E o P
			if((char)actual == 'T'||(char)actual == 'Q'||(char)actual == 'E'||(char)actual == 'P'){
				actual = fgetc(archivo);//vamos a el siguiente caracter para comprobar que no hayan mas caracters
				
				if(actual != EOF && actual != '\n'){
					printf("ERROR en la linea %s\n", nlinea);
					printf("DETALLES: No se esperan mas caracteres despues de el ultimo caracter de salto\n");
					fclose(archivo);
					return 1;
				}
				
				return 0;
			}
			// si no es T, Q E o P el tercer caracter
			else{
				printf("ERROR en la linea %s\n", nlinea);
				printf("DETALLES: Se espera un caracter T, Q E o P, despues de el segundo caracter de el salto\n");
				fclose(archivo);
				return 1;//error
			}
		}
		//si no es M, N, Q, E, L o G el segundo caracter
		else{
			printf("ERROR en la linea %s\n", nlinea);
			printf("DETALLES: Se espera un caracter M, N, Q, E, L o G despues de el J\n");
			fclose(archivo);
			return 1;
		}
	}
	
	//si no es ; el primer caracter
	printf("ERROR en la linea %s\n", nlinea);
	printf("DETALLES: Se espera el signo ;\n");
	fclose(archivo);
	return 1;
}
//-----------------------------------------------------------------
int instruccionCalculo(int actual, FILE *archivo, char* nlinea){
	char buffer2[3];//buffer para ver que los operandos no sean iguales o excepciones
	buffer2[2] = '\0';
	memset(buffer2, 0, 3);
	// Si comienza con D, M, A, 1 o 0
        if ((char)actual == 'D' || (char)actual == 'M' || (char)actual == 'A'||(char)actual == '1'||(char)actual == '0') {
        	buffer2[0] = (char)actual;
            actual = fgetc(archivo); // siguiente carácter
            
            //comprobamos que el siguiente caracter se +, -, | o &
            if ((char)actual == '+' || (char)actual == '-' || (char)actual == '|' || (char)actual == '&') {
                actual = fgetc(archivo); // siguiente carácter
                buffer2[1] = (char)actual;
                 //comprobamos que el siguiente caracter sea A, D, M, 1 o 0
                if ((char)actual == 'A' || (char)actual == 'D' || (char)actual == 'M' || (char)actual == '1' || (char)actual == '0') {
                    actual = fgetc(archivo); // siguiente carácter
                    
				   	//excepciones como que A y M no se pueden calcular
				   	if(buffer2[0] == 'A' && buffer2[1] == 'M' || buffer2[0] == 'M' && buffer2[1] == 'A'){
				   		printf("ERROR en la linea %s\n", nlinea);
				   		printf("DETALLES: No se pueden calcular A con M debido a la arquitectura de la CPU\n");
				   		fclose(archivo);
				   		return 1;
					   }
					 //si son iguales los operandos
				   	 else if(buffer2[0] == buffer2[1]){
				   	 	printf("ERROR en la linea %s\n", nlinea);
				   	 	printf("DETALLES: No se puede operar con la misma letra\n");
				   	 	fclose(archivo);
				   	 	return 1;
						}
				   
                    //vemos si es final de linea
                    else if ((char)actual == '\n' || actual == EOF) {
                    	
                        return 0; // Solo cálculo
                    }
					//si no es final de linea vemos si el siguiente caracter es ; 
					else {
                        if ((char)actual != ';') {
                            printf("ERROR en la linea %s\n", nlinea);
                            printf("DETALLES: Se espera el caracter ';' o fin de linea.\n");
                            fclose(archivo);
                            return 1;
                        }
                        //si es ;
						 else {
						 	
                            int h = instruccionSalto(actual, archivo, nlinea);
                            
                            if (h != 0) return 1;
                            else return 0; // Instrucción completa válida
                        }
                    }
                }
                // si no es A, D, M, 1 o 0 el tercer caracter hay un error
				 else {
                    printf("ERROR en la linea %s\n", nlinea);
                    printf("DETALLES: Se espera 'M', 'D', 'A', '0' o '1' despues del operador.\n");
                    fclose(archivo);
                    return 1;
                }
            }
            //si no hay operador pero hay un final de linea
            else if(actual == EOF || (char)actual == '\n' || (char)actual == ' ' || (char)actual == '\0'){
            	
				return 0;
			}
            //si no hay salto de linea pero hay un ;
            else if((char)actual == ';'){
            	
            	int h2 = instruccionSalto(actual, archivo, nlinea);
            	
                if (h2 != 0) return 1;
                else return 0; // Instrucción completa válida
            	
			}
			//si no hay salto de linea, o ; ni operador
            else {
                printf("ERROR en la linea %s\n", nlinea);
                printf("DETALLES: Se espera un caracter como +, -, & o |, ; o nada\n");
                fclose(archivo);
                return 1;
            }
        }
        
        // Si empieza con un operador como '-' o '!'
        else if ((char)actual == '-' || (char)actual == '!') {
            actual = fgetc(archivo);
            
            if ((char)actual == 'M' || (char)actual == 'D' || (char)actual == 'A' || (char)actual == '1') {
                actual = fgetc(archivo);
                
                if((char)actual == '\n' ||(char)actual == ' ' ||(char)actual == '\0' ||actual == EOF){
                	return 0;
				}
                else if((char)actual == ';'){
                	
                	int h3=instruccionSalto(actual, archivo, nlinea);
                	
                	if(h3 != 0) return 1;
                	else return 0;
				}
				else if((char)actual != '\n'&& actual != EOF){
					printf("ERROR en la linea %s\n", nlinea);
					printf("DETALLES: Se espera un caracter ';' o nada despues de el caracter anterior A, M, D o 1\n");
					fclose(archivo);
					return 1;
				}
            } else {
                printf("ERROR en la linea %s\n", nlinea);
                printf("DETALLES: Se espera A, M, D o 1 despues de '-' o '!'\n");
                fclose(archivo);
                return 1;
            }
        }
        
        printf("ERROR en la linea %s\n", nlinea);
        printf("DETALLES: Se espera un calculo despues de el destino\n");
        fclose(archivo);
        return 1;
}
//**************************************************************

//-----------------------------------------------------------------
int eliminarArchivos(){
	FILE *analizar = fopen("analizarLineas.txt", "r");
	if(analizar == NULL){
		printf("No se encontro el archivo 'analizarEtiquetas.txt'\n");
		return 1;
	}
	FILE *copia = fopen("copia.txt", "r");
	if(copia == NULL){
		printf("No se encontro el archivo 'copia.txt'\n");
		return 1;
	}
	fclose(analizar);
	fclose(copia);
	if(remove("analizarLineas.txt") != 0){
		printf("ERROR a el tratar de eliminar el archivo 'analizarEtiquetas.txt'\n");
		return 1;
	}
	if(remove("copia.txt") != 0){
		printf("ERROR a el tratar de eliminar el archivo 'copia.txt'\n");
		return 1;
	}
	printf("\nSE ELIMINARON LOS ARCHIVOS PARA ANALISIS SINTACTICO CORRECTAMETE\n");
	return 0;
}


//**************************************************************
//-----------------------------------------------------------------
int tratarVariables2(const char *nombre_de_archivo) {
	FILE *archivoP = fopen(nombre_de_archivo, "r");
	if(archivoP == NULL){
		printf("No se encontro el archivo '%s'\n", nombre_de_archivo);
		return 1;
	}
	printf("Se abrio el archivo '%s'\n", nombre_de_archivo);
	
	FILE* tempoEtiquetas = fopen("var2.txt", "w");
	if(tempoEtiquetas == NULL){
		printf("ERROR a el crear el archivo 'var2.txt'\n");
		fclose(archivoP);
		return 1;
	}
	printf("Se creo el archivo 'var2.txt'\n");
	
	int result = encontrarvar2(archivoP, tempoEtiquetas);
	if(result != 0){
		fclose(archivoP);
		fclose(tempoEtiquetas);
		return 1;
	}
	fclose(archivoP);
	fclose(tempoEtiquetas);
	if(remove(nombre_de_archivo) != 0){
		printf("ERROR a el elminar el archivo '%s'\n", nombre_de_archivo);
		return 1;
	}
	else{
		if(rename("var2.txt", nombre_de_archivo) != 0){
			printf("No se puedo reenombrar el archivo 'etiquetas2.txt'\n");
			return 1;
		}
		printf("Se renombro el archivo 'var2.txt' a: '%s'\n", nombre_de_archivo);
	}	
	
	char linea[1024];
	FILE *limpiar = fopen(nombre_de_archivo, "r");
    if(limpiar == NULL){
    	printf("No se encontro el archivo '%s'\n", nombre_de_archivo);
    	return 1;
	}
	printf("Se abiro el archivo '%s'\n", nombre_de_archivo);
	FILE *tempoE = fopen("tempoE.txt", "w");
	if(tempoE == NULL){
		printf("ERROR  a el crear el archivo 'tempoE.txt'\n");
		fclose(limpiar);
		return 1;
	} 
	printf("Se creo exitosamente el archivo 'tempoE.txt'\n");
	
	while(fgets(linea, sizeof(linea), limpiar) != NULL){
		char *linea3 = eliminarLineas_vacias(linea);
		if(linea3[0] != '\0'){
			fputs(linea3, tempoE);
		}
	}
	fclose(limpiar);
	fclose(tempoE);
	if(remove(nombre_de_archivo) != 0){
		printf("ERROR a el elminar el archivo '%s'\n", nombre_de_archivo);
		return 1;
	}
	else{
		if(rename("tempoE.txt", nombre_de_archivo) != 0){
			printf("No se puedo reenombrar el archivo 'tempoE.txt'\n");
			return 1;
		}
		printf("Se renombro el archivo 'tempoE.txt' a: '%s'\n", nombre_de_archivo);
	}
	return 0;
	
}
//-----------------------------------------------------------------
int encontrarvar2(FILE* archivoLeer, FILE* archivoEscribir){
	int actual = 0; //caracter actual(fgetc devuelve entero entonces para leer el caracter tenemos que pasarlo a caracter con '(char)actual')
	while((actual = fgetc(archivoLeer)) !=  EOF){
		  while((char)actual != ' '){
		  	fputc((char)actual, archivoEscribir);
		  	actual = fgetc(archivoLeer);
		  }
          fputc((char)actual, archivoEscribir);//agregamos el espacio
		  actual = fgetc(archivoLeer);//caracter despues de el espacio
	    	if((char)actual == '@'){
	    		fputc((char)actual, archivoEscribir); //ponemos el inicio de la variable para uso posterior
	    		actual = fgetc(archivoLeer);
	    		while(actual != EOF && (char)actual != '\n'){
	    			//si es una cadena de digitos 
	    			if((char)actual >= '0' && (char)actual <= '9'){
	    				int n = 0;
	    				//solo copiamos los primeros 5
	    				while(actual != EOF && (char)actual!= '\n' && n <5){
	    					fputc((char)actual, archivoEscribir);
	                        n++;
	    					actual = fgetc(archivoLeer);
						}
					   fputc('\n', archivoEscribir);
						if(actual == EOF) break;
						//si se alcanzo el maximo de caracteres y hay mas los ignoramos
						if(n == 5){
							while(actual != EOF && (char)actual != '\n'){
								actual = fgetc(archivoLeer);
							}
							if((char)actual == '\n') fputc('\n', archivoEscribir);
						}
						break;
					}
					//escribir el contenido de la variable completo si no empieza con digito numerico
					else{
					while(actual != EOF && (char)actual != '\n'){
					fputc((char)actual, archivoEscribir);
					actual = fgetc(archivoLeer);
				   }
				   if(actual == '\n') fputc('\n', archivoEscribir);
				   //si es eof salimos de el bucle
				   else break;
				}				
			}
	}
	else{
	   while(actual != EOF && (char)actual != '\n'){
			fputc((char)actual, archivoEscribir);
			actual = fgetc(archivoLeer);
			}
			if(actual == '\n') fputc('\n', archivoEscribir);
			else break;
	   }
 }
	return 0;
}
//**************************************************************

//-----------------------------------------------------------------
int tratarVariables(const char *nombre_de_archivo){
	FILE *archivoP = fopen(nombre_de_archivo, "r");
	if(archivoP == NULL){
		printf("No se encontro el archivo '%s'\n", nombre_de_archivo);
		return 1;
	}
	printf("Se abrio el archivo '%s'\n", nombre_de_archivo);
	
	FILE* tempoEtiquetas = fopen("etiquetas2.txt", "w");
	if(tempoEtiquetas == NULL){
		printf("ERROR a el crear el archivo 'etiquetas2.txt'\n");
		fclose(archivoP);
		return 1;
	}
	printf("Se creo el archivo 'etiquetas2.txt'\n");
	
	int result = encontrarvar(archivoP, tempoEtiquetas);
	if(result != 0){
		fclose(archivoP);
		fclose(tempoEtiquetas);
		return 1;
	}
	fclose(archivoP);
	fclose(tempoEtiquetas);
	if(remove(nombre_de_archivo) != 0){
		printf("ERROR a el elminar el archivo '%s'\n", nombre_de_archivo);
		return 1;
	}
	else{
		if(rename("etiquetas2.txt", nombre_de_archivo) != 0){
			printf("No se puedo reenombrar el archivo 'etiquetas2.txt'\n");
			return 1;
		}
		printf("Se renombro el archivo 'etiquetas2.txt' a: '%s'\n", nombre_de_archivo);
	}	
	
	char linea[1024];
	FILE *limpiar = fopen(nombre_de_archivo, "r");
    if(limpiar == NULL){
    	printf("No se encontro el archivo '%s'\n", nombre_de_archivo);
    	return 1;
	}
	printf("Se abiro el archivo '%s'\n", nombre_de_archivo);
	FILE *tempoE = fopen("tempoE.txt", "w");
	if(tempoE == NULL){
		printf("ERROR  a el crear el archivo 'tempoE.txt'\n");
		fclose(limpiar);
		return 1;
	} 
	printf("Se creo exitosamente el archivo 'tempoE.txt'\n");
	
	while(fgets(linea, sizeof(linea), limpiar) != NULL){
		char *linea3 = eliminarLineas_vacias(linea);
		if(linea3[0] != '\0'){
			fputs(linea3, tempoE);
		}
	}
	fclose(limpiar);
	fclose(tempoE);
	if(remove(nombre_de_archivo) != 0){
		printf("ERROR a el elminar el archivo '%s'\n", nombre_de_archivo);
		return 1;
	}
	else{
		if(rename("tempoE.txt", nombre_de_archivo) != 0){
			printf("No se puedo reenombrar el archivo 'etiquetas2.txt'\n");
			return 1;
		}
		printf("Se renombro el archivo 'tempoE.txt' a: '%s'\n", nombre_de_archivo);
	}
	return 0;
	
}
//-----------------------------------------------------------------
int encontrarvar(FILE* archivoLeer, FILE* archivoEscribir){
			int actual = fgetc(archivoLeer); //caracter actual(fgetc devuelve entero entonces para leer el caracter tenemos que pasarlo a caracter con '(char)actual')
	while(actual !=  EOF){
		  char char_actual =(char)actual;
	    	if(char_actual == '@'){
	    		fputc('\n', archivoEscribir);
	    		fputc(char_actual, archivoEscribir); //ponemos el inicio de la varible para uso posterior
	    		actual = fgetc(archivoLeer);
	    		while(actual != EOF && (char)actual != '\n'){
	    			char_actual = (char)actual;
	    			fputc(char_actual, archivoEscribir); //escribir el contenido de la variable.
	    			actual = fgetc(archivoLeer);
				}				
				char_actual = '\n';
				
			}
			fputc(char_actual, archivoEscribir);
			actual = fgetc(archivoLeer);
	}
	return 0;
}
//AQUI TERMINA EL PROCESO DE ANALISIS SINTACTICO---------------------------------------


//AQUI INICIA EL PROCESO DE PREPARCION Y LIMPIEZA-------------------------------------------------------------
//-----------------------------------------------------------------
int ArchivoA_txt(const char* nombre_archivo) {
    FILE *assembly = fopen(nombre_archivo, "r");
    
    // Verificar si el archivo se pudo abrir correctamente
    if (assembly == NULL) {
        printf("El archivo '%s' no se encontró.\n", nombre_archivo);
        return 1;
    }
    
    // Si el archivo se abre correctamente
    printf("El archivo '%s' fue encontrado y abierto exitosamente.\n", nombre_archivo);
    
    // Crear o abrir el archivo .txt en modo escritura
    FILE *txt_file = fopen("archivo.txt", "w");
    if (txt_file == NULL) {
        printf("No se pudo crear el archivo .txt.\n");
        fclose(assembly);  // Aseguramos que cerramos el archivo .asm
        return 1;
    }
    
    printf("El archivo 'archivo.txt' fue creado y abierto exitosamente.\n");

    // Leer el archivo .asm y escribir en el archivo .txt
    char c;
    while ((c = fgetc(assembly)) != EOF) {
        fputc(c, txt_file);  // Escribir cada carácter en el archivo .txt
    }
    
    // Cerrar ambos archivos
    fclose(assembly);
    fclose(txt_file);
    
    printf("El contenido de '%s' ha sido copiado a 'archivo.txt'.\n", nombre_archivo);
    return 0;
}
//**************************************************************
//-----------------------------------------------------------------
int limpiarLineas(const char *archivo) {
	//abrir archivos y crear temporal
    FILE *archivoPrincipal = fopen(archivo, "r"); // Abrimos el archivo en modo lectura
    if (archivoPrincipal == NULL) {
        printf("No se encontro el archivo '%s'\n", archivo);
        return 1; // Salir si no se pudo abrir
    }
    printf("El archivo '%s' se abrio correctamente\n", archivo);

    FILE *temp2 = fopen("temp2.txt", "w"); // Crear un archivo temporal
    if (temp2 == NULL) {
        printf("ERROR al crear el archivo 'temp2.txt'\n");
        fclose(archivoPrincipal);
        return 1; // Salir si no se pudo abrir el archivo temporal
    }
    printf("'temp2.txt' listo para ser editado\n");
     // COMIENZA LO IMPORTANTE
     char linea[1024]; // buffer para leer líneas
     //eliminar espacios es en el archivo y guardar el arhcivo editado
    while (fgets(linea, sizeof(linea), archivoPrincipal) != NULL) {
        char *lineaProcesada = eliminarEspaciosPreservarSalto(linea);
        if (lineaProcesada[0] != '\0') {
            fputs(lineaProcesada, temp2);
        }
    }
    
   printf("Se llego a el final de el archivo\n");
    fclose(archivoPrincipal);  // Cerramos el archivo original
    fclose(temp2);  // Cerramos el archivo temporal
    //eliminamos el archivo .txt actual y lo reemplazamos por el procesado
    if (remove(archivo) != 0) {
        printf("Error al eliminar el archivo original.\n");
        return 1;
    } else {
        if (rename("temp2.txt", archivo) != 0) {
            printf("Error al reemplazar el archivo original.\n");
            return 1;
        } else {
            printf("Archivo '%s' sin espacios se creo correctamente.\n", archivo);
        }
    }  	
	
    FILE *archivoSinEspacios= fopen(archivo, "r");
    if(archivoSinEspacios == NULL){
    	printf("No se pudo abrir el archivo '%s'\n", archivo);
    	return 1;
	}
	printf("Se abrio correctamente el archivo '%s'\n", archivo);
	FILE *temp3 = fopen("temp3.txt", "w");
	if(temp3 == NULL){
		printf("ERROR  a el crear el archivo 'temp3.txt'\n");
		fclose(archivoSinEspacios);
		return 1;
	}
	printf("Se creo el arcivo 'temp3.txt' correctamente\n");
     
 // Eliminar los comentarios en bloque de el archivo
    eliminar_comentario_bloque(archivoSinEspacios, temp3); 
	fclose(archivoSinEspacios);
	fclose(temp3);
	
	if(remove(archivo) == 0) printf("Se elimino el archivo '%s'\n", archivo);
	else{
		 printf("No se puedo eliminar el archivo '%s'\n", archivo);
      return 1;
	} 
    if(rename("temp3.txt", archivo) == 0){
    	printf("Se reenombro el archivo 'temp3.txt' a : '%s'\n", archivo);
	}
	else{
		printf("No se pudo renombrar el archivo 'temp3.txt'\n");
		return 1;
	}	
	
	FILE *archivoSinbloques = fopen(archivo, "r");
	if(archivoSinbloques == NULL){
		printf("No se encontro el archivo '%s'\n", archivo);
		return 1;
	}
	printf("Se abrio el archivo '%s' exitosamente\n", archivo);
     FILE *temp4 = fopen("temp4.txt", "w");
     if(temp4 == NULL){
     	printf("ERROR a el crear el archivo 'temp4.txt'\n");
     	fclose(archivoSinbloques);
     	return 1;
	 }
	 printf("Se creo el archivo 'temp4.txt'\n");
	 //Eliminar los comentarios simples de el archivo 
	  while(fgets(linea, sizeof(linea), archivoSinbloques) != NULL){
        char *linea3 = eliminar_comentario_simple(linea);
        if(linea3[0] != '\0'){
            fputs(linea3, temp4);
        }
    }
    fclose(archivoSinbloques);
    fclose(temp4);
    
    if(remove(archivo) == 0) printf("Se elimino el archivo '%s'\n", archivo);
	else{
		 printf("No se puedo eliminar el archivo '%s'\n", archivo);
      return 1;
	} 
    if(rename("temp4.txt", archivo) == 0){
    	printf("Se reenombro el archivo 'temp4.txt' a : '%s'\n", archivo);
	}
	else{
		printf("No se pudo renombrar el archivo 'temp4.txt'\n");
		return 1;
	}
    
    
	FILE *casiLimpio = fopen(archivo, "r");
	if(casiLimpio == NULL){
		printf("No se encontro el archvio '%s'\n", archivo);
		return 1;
	}
	printf("El archivo '%s' se abrio correctamente\n", archivo);
	FILE *ultimotemp = fopen("tempF.txt", "w");
	if(ultimotemp == NULL){
		printf("ERROR a el crear el archivo 'tempF.txt'\n");
		fclose(casiLimpio);
		return 1;
	}
	printf("Se creo el archivo 'tempF.txt'\n");
	
	while(fgets(linea, sizeof(linea), casiLimpio) != NULL){
		char *linea3 = eliminarLineas_vacias(linea);
		if(linea3[0] != '\0'){
			fputs(linea3, ultimotemp);
		}
	}
	fclose(casiLimpio);
	fclose(ultimotemp);
	
	if(remove(archivo) == 0) printf("Se elimino el archivo '%s'\n", archivo);
	else{
		 printf("No se puedo eliminar el archivo '%s'\n", archivo);
      return 1;
	} 
	//eliminamos los archivos temporales creados
    if(rename("tempF.txt", archivo) == 0){
    	printf("Se reenombro el archivo 'tempF.txt' a : '%s'\n", archivo);
	}
	else{
		printf("No se pudo renombrar el archivo 'tempF.txt'\n");
		return 1;
	}
	printf("EL ARCHIVO '%s' ESTA LIMPIO\n", archivo);
	return 0;
}
//-----------------------------------------------------------------
// Elimina espacios/tabs excepto \n
char* eliminarEspaciosPreservarSalto(char *str) {
    char *dest = str;
    char *inicio = str;
    while (*str != '\0') {
        if (*str != ' ' && *str != '\t') {
            *dest = *str;
            dest++;
		}
        str++;
    }
    *dest = '\0';
    return inicio;
}
//-----------------------------------------------------------------
char *eliminar_comentario_simple(char *cadena) {
    char *inicio = cadena;
    char *linea = cadena;
    char *nuevaLinea = linea;  // Apunta al inicio de la cadena

    while (*linea != '\0') {
        // Detectar comentario de una línea (//)
        if (*linea == '/') {
            linea++;
            if (*linea == '/') {
                // Comentario de una sola línea (//)
                while (*linea != '\n' && *linea != '\0') {
                    linea++;  // Saltar todo el comentario
                }
            }
        }
        
        // Si no es un comentario, copiar el carácter actual a nuevaLinea
        if (*linea != '\0') {
            *nuevaLinea = *linea;
            nuevaLinea++;
        }
        linea++;  // Avanzar al siguiente carácter
    }
    
    *nuevaLinea = '\0';  // Terminamos la cadena
    return inicio;  // Retornamos la cadena modificada
}
//-----------------------------------------------------------------
void eliminar_comentario_bloque(FILE *archivoLeer, FILE *archivoEscribir) {
    int actual = fgetc(archivoLeer);
    int dentroComentario = 0;
    while (actual != EOF) {
        char car_actual = (char)actual;
    
        if (car_actual == '/' && !dentroComentario) {
            actual = fgetc(archivoLeer);
            if (actual == EOF) {
                // Si el archivo termina abruptamente después de un '/', no hay nada que hacer.
                fprintf(stderr, "Se llegó al final del archivo inesperadamente.\n");
                fclose(archivoLeer);
                fclose(archivoEscribir);
                return;
            }

            if ((char)actual == '*') {
            	actual = fgetc(archivoLeer);
                car_actual = (char)actual;
				dentroComentario = 1;
                printf("Es un comentario en bloque\n");
            } else {
                // Si no es un comentario en bloque, escribe el '/' y el siguiente carácter.
                fputc(car_actual, archivoEscribir);
            }
        } else if (dentroComentario) {
            while ((actual = fgetc(archivoLeer)) != EOF && car_actual != '*' || (char)actual != '/') {
                  car_actual = (char)actual;
            } 
			 if (actual == EOF) {
                fprintf(stderr, "Se llegó al final del archivo dentro de un comentario.\n");
                fclose(archivoLeer);
                fclose(archivoEscribir);
                return;
            }
            dentroComentario = 0;
            actual = fgetc(archivoLeer);
            car_actual = (char)actual;
        } else {
            // Si no estamos dentro de un comentario, escribimos el carácter.
            fputc(car_actual, archivoEscribir);
            actual = fgetc(archivoLeer);
        }
    }

    fclose(archivoLeer);
    fclose(archivoEscribir);
    return;
}
//-----------------------------------------------------------------
char* eliminarLineas_vacias(char* cadena) {
    char *inicio = cadena;
    char *src = cadena;
    char *dst = cadena;
    int i = 0;
    while (*src != '\0') {
        // Buscar fin de línea
        char *line_end = src;
        while (*line_end != '\n' && *line_end != '\0') {
            line_end++;
        }

        // Calcular longitud de la línea
        int len = line_end - src;

        // Verificar si la línea no está vacía (más que solo salto de línea)
        int es_vacia = 1;
        for ( i = 0; i < len; i++) {
            if (src[i] != ' ' && src[i] != '\t') {
                es_vacia = 0;
                break;
            }
        }

        if (!es_vacia) {
            // Copiar la línea completa (incluyendo salto de línea si existe)
            for (i = 0; i < len; i++) {
                *dst++ = src[i];
            }
            if (*line_end == '\n') {
                *dst++ = '\n';
            }
        }

        // Avanzar src a la siguiente línea
        if (*line_end == '\0') {
            break;
        }
        src = line_end + 1;
    }

    *dst = '\0'; // Terminar cadena
    return inicio;
}
//**************************************************************

//-----------------------------------------------------------------
// prototipo de las filas(plantilla)
typedef struct tablaP {
    char *claves;
    int valor;
    struct tablaP *next;
} tablaP;

int tablaDeSimbolos() {
    FILE *tabla = fopen("tabla.txt", "w");
    if (tabla == NULL) {
        printf("No se pudo crear el archivo 'tabla.txt'\n");
        return 1;
    }
    printf("El archvio 'tabla.txt' se creo\n");
    fclose(tabla);
   
    int valor[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16384, 24576, 0, 1, 2, 3, 4};
    char clave[] ="R0 R1 R2 R3 R4 R5 R6 R7 R8 R9 R10 R11 R12 R13 R14 R15 SCREEN KBD SP LCL ARG THIS THAT";
    int n = 23; // Número de elementos
    int h = n;
    tablaP *filas = (tablaP *)malloc(n * sizeof(tablaP));
    if (filas == NULL) {
        printf("Error al asignar memoria para el arreglo de filas\n");
        return 1;
    }
    char *token = strtok(clave, " ");
    // Inicializar el puntero next a NULL
    int i;
    int j;
    int k;
    for (i = 0; i < n; i++) {
        filas[i].next = NULL;
        filas[i].claves = strdup(token);  // Copiar la clave
        if (filas[i].claves == NULL) {
            printf("Error al asignar memoria para la clave\n");
            free(filas);
            return 1;
        }

        filas[i].valor = valor[i];
        filas[i].next = ((i + 1) < h) ? &filas[i + 1] : NULL;  // Establecer el siguiente puntero
        

        token = strtok(NULL, " ");  // Obtener el siguiente token
    }

    // Abrir el archivo nuevamente para agregar datos
    FILE *tabla_file = fopen("tabla.txt", "a");
    if (tabla_file == NULL) {
        printf("No se pudo encontrar el archivo 'tabla.txt'\n");
        free(filas);
        return 1;
    }
    printf("Se abrio el archivo 'tabla.txt' correctamente\n");

    for (j = 0; j < n; j++) {
        fprintf(tabla_file, "%s %d\n", filas[j].claves, filas[j].valor);
    }

    fclose(tabla_file); // Escribir los datos al archivo

    // Liberar memoria
    for ( k = 0; k < n; k++) {
        free(filas[k].claves);  // Liberar las cadenas dinámicas
    }

    free(filas);  // Liberar el arreglo de filas
    printf("SE CREO LA TABLA EXITOSAMENTE EN EL ARCHIVO 'tabla.txt'\n");
    return 0;
}

//**************************************************************
//-----------------------------------------------------------------
int tratarEtiquetas(const char *nombre_de_archivo) {
	FILE *archivoP = fopen(nombre_de_archivo, "r");
	if(archivoP == NULL){
		printf("No se encontro el archivo '%s'\n", nombre_de_archivo);
		return 1;
	}
	printf("Se abrio el archivo '%s'\n", nombre_de_archivo);
	
	FILE* tempoEtiquetas = fopen("etiquetas2.txt", "w");
	if(tempoEtiquetas == NULL){
		printf("ERROR a el crear el archivo 'etiquetas2.txt'\n");
		fclose(archivoP);
		return 1;
	}
	printf("Se creo el archivo 'etiquetas2.txt'\n");
	
	int result = encontrarEtiquetas(archivoP, tempoEtiquetas);
	if(result != 0){
		fclose(archivoP);
		fclose(tempoEtiquetas);
		return 1;
	}
	fclose(archivoP);
	fclose(tempoEtiquetas);
	if(remove(nombre_de_archivo) != 0){
		printf("ERROR a el elminar el archivo '%s'\n", nombre_de_archivo);
		return 1;
	}
	else{
		if(rename("etiquetas2.txt", nombre_de_archivo) != 0){
			printf("No se puedo reenombrar el archivo 'etiquetas2.txt'\n");
			return 1;
		}
		printf("Se renombro el archivo 'etiquetas2.txt' a: '%s'\n", nombre_de_archivo);
	}	
	
	char linea[1024];
	FILE *limpiar = fopen(nombre_de_archivo, "r");
    if(limpiar == NULL){
    	printf("No se encontro el archivo '%s'\n", nombre_de_archivo);
    	return 1;
	}
	printf("Se abiro el archivo '%s'\n", nombre_de_archivo);
	FILE *tempoE = fopen("tempoE.txt", "w");
	if(tempoE == NULL){
		printf("ERROR  a el crear el archivo 'tempoE.txt'\n");
		fclose(limpiar);
		return 1;
	} 
	printf("Se creo exitosamente el archivo 'tempoE.txt'\n");
	
	while(fgets(linea, sizeof(linea), limpiar) != NULL){
		char *linea3 = eliminarLineas_vacias(linea);
		if(linea3[0] != '\0'){
			fputs(linea3, tempoE);
		}
	}
	fclose(limpiar);
	fclose(tempoE);
	if(remove(nombre_de_archivo) != 0){
		printf("ERROR a el elminar el archivo '%s'\n", nombre_de_archivo);
		return 1;
	}
	else{
		if(rename("tempoE.txt", nombre_de_archivo) != 0){
			printf("No se puedo reenombrar el archivo 'etiquetas2.txt'\n");
			return 1;
		}
		printf("Se renombro el archivo 'tempoE.txt' a: '%s'\n", nombre_de_archivo);
	}
	return 0;
	
}
//-----------------------------------------------------------------
int encontrarEtiquetas(FILE* archivoLeer, FILE* archivoEscribir){
	int actual = fgetc(archivoLeer); //caracter actual(fgetc devuelve entero entonces para leer el caracter tenemos que pasarlo a caracter con '(char)actual')
	while(actual !=  EOF){
		  char char_actual =(char)actual;
	    	if(char_actual == '('){
	    		fputc('\n', archivoEscribir);
	    		fputc(char_actual, archivoEscribir); //ponemos el inicio de la etiqueta para uso posterior
	    		actual = fgetc(archivoLeer);
	    		while(actual != EOF && (char)actual != ')'){
	    			char_actual = (char)actual;
	    			fputc(char_actual, archivoEscribir); //escribir el contenido de la etiqueta.
	    			actual = fgetc(archivoLeer);
				}				
				if(actual == EOF){
					printf("ERROR, se llego a el final de el archivo '%s', y no se cerro la etiqueta\n", archivoLeer);
					fclose(archivoLeer);
					fclose(archivoEscribir);
					return 1;
				}
				char_actual = '\n';
				
			}
			fputc(char_actual, archivoEscribir);
			actual = fgetc(archivoLeer);
	}
	return 0;
}
//**************************************************************

//-----------------------------------------------------------------
int numerarLineas(const char* archivoLeer) {
    FILE* entrada = fopen(archivoLeer, "r");
    if (entrada == NULL) {
        printf("No se encontro el archivo '%s'\n", archivoLeer);
        return 1;
    }
    printf("Se abrio el archivo '%s'\n", archivoLeer);

    FILE* temp = fopen("tempo.txt", "w");
    if (temp == NULL) {
        printf("ERROR al crear el archivo 'tempo.txt'\n");
        fclose(entrada);
        return 1;
    }
    printf("Se creo 'tempo.txt' exitosamente\n");

    char linea[1024]; // Buffer para leer cada línea
    int numero_linea = 1; // Contador de líneas
    
    // Leer cada línea del archivo
    while (fgets(linea, sizeof(linea), entrada) != NULL) {
        // Verificar si la línea contiene una etiqueta o '('
        if (strchr(linea, '(') != NULL) {
            fprintf(temp, "%d %s", numero_linea, linea);
            continue;
        }
        
        // Escribir el número de línea y la línea en el archivo de salida
        fprintf(temp, "%d %s", numero_linea, linea);
        numero_linea++; // Incrementar el número de la línea
    }
    fclose(entrada);
    fclose(temp);
    // Eliminar el archivo original
    if (remove(archivoLeer) != 0) {
        printf("ERROR al eliminar el archivo '%s'\n", archivoLeer);
        return 1;
    } else {
        // Renombrar el archivo temporal a su nombre original
        if (rename("tempo.txt", archivoLeer) != 0) {
            printf("ERROR al renombrar el archivo 'tempo.txt' a '%s'\n", archivoLeer);
            return 1;
        } else {
            printf("Se renombro el archivo 'tempo.txt' a '%s' exitosamente\n", archivoLeer);
        }
    }

    printf("LINEAS DEL ARCHIVO NUMERADAS\n");
    return 0;
}
//**************************************************************
//-----------------------------------------------------------------
int separarEtiquetas(const char* archivo){
	FILE *archivoP = fopen(archivo, "r");
	if(archivoP == NULL){
		printf("No se encontro el archivo '%s'\n", archivo);
		return 1;
	}
	printf("Se abrio el archivo '%s' exitosamente\n", archivo);
	FILE *temp = fopen("etiquetas.txt", "w");
	if(temp == NULL){
		printf("ERROR a el crear el archivo 'etiquetas.txt'\n");
		fclose(archivoP);
		return 1;
	}
	printf("Se creo el archivo 'etiquetas.txt' exitosamente\n");
	
	copiarLineasConEtiqueta(archivoP, temp);
	fclose(archivoP);
	fclose(temp);
	
	FILE *reabrir = fopen("etiquetas.txt", "r");
	if(reabrir == NULL){
		printf("No se encontro el archivo 'etiquetas.txt'\n");
		return 1; 
	}
	FILE *temp2 = fopen("tempetiquetas.txt", "w");
	if(temp2 == NULL){
		printf("ERROR a el crear el archivo 'tempetiquetas.txt'\n");
		fclose(reabrir);
		return 1;
	}
	
	contenidoEtiquetas(reabrir, temp2);
	fclose(reabrir);
	fclose(temp2);
	
	if(remove("etiquetas.txt") != 0){
		printf("No se pudo eliminar el arhcivo 'etiquetas.txt'\n");
		return 1;
	}	
	else{
		if(rename("tempetiquetas.txt", "etiquetas.txt") != 0){
			printf("No se pudo renombrar el archivo 'tempertiquetas.txt'\n");
			return 1;
		}
	}
	printf("SE CREO EL ARCHIVO 'etiquetas.txt'\n");
	return 0;
}
//-----------------------------------------------------------------
void copiarLineasConEtiqueta(FILE *archivoLeer, FILE *archivoEscribir) {
    char linea[1024];  // Buffer para almacenar cada línea leída

    // Lee línea por línea
    while (fgets(linea, sizeof(linea), archivoLeer) != NULL) {
        // Revisa si hay un '(' en la línea
        if (strchr(linea, '(') != NULL) {
            // Si encontramos un '(', copiamos la línea al archivo de salida
            fputs(linea, archivoEscribir);
        }
    }
}
//-----------------------------------------------------------------
void contenidoEtiquetas(FILE *archivoLeer, FILE* archivoEscribir){
    int actual = fgetc(archivoLeer);
    while(actual != EOF){
        char char_actual = (char)actual;
        if(char_actual == '('){
           actual = fgetc(archivoLeer);
           if(actual == EOF) break; // Evitar procesar EOF
           char_actual = (char)actual;
        }
        fputc(char_actual, archivoEscribir);
        actual = fgetc(archivoLeer);
    }
}
//**************************************************************

//**************************************************************
//-----------------------------------------------------------------
int mas_simbolos(const char* archivo_de_datos){
    FILE *archivoEtiq = fopen(archivo_de_datos, "r"); // abrir el archivo de etiquetas
    if(archivoEtiq == NULL){
        printf("No se encontro el archivo '%s'\n", archivo_de_datos);
        return 1;
    }
    printf("Se abrio el archivo '%s'\n", archivo_de_datos);
    
    int cantidad = cantidadDeLineas(archivoEtiq); //obtenemos la cantidad de lineas de el archivo
    printf("numero de lineas : %d. De el archivo '%s'\n", cantidad, archivo_de_datos);
    
    tablaP mas_simbolos[cantidad]; //asignar memoria para nuevos simbolos
    
    char **valoresChar = (char**)malloc(cantidad*sizeof(char*));// asignamos memoria para almacena la cantidad de cadenas de digitos que hay (n lineas)
    if(valoresChar == NULL){
    	printf("ERROR a el asignar memoria a 'valoresChar'\n");
    	fclose(archivoEtiq);
    	return 1;
	} 
    
    
    char **cadena = (char**) malloc(cantidad * sizeof(char*)); //asginamos memoria para almacenar la cantidad de cadenas que hay (n lineas)
    if(cadena == NULL){
    	printf("ERROR a el asignar memoria a 'cadena'\n");
    	fclose(archivoEtiq);
    	return 1;
	} 
	int result =separaDigitosdeLetras(archivoEtiq, cadena, valoresChar, cantidad);
	if(result != 0){
       	return 1;
	}
	int i;
	for(i = 0; i < cantidad; i++){
		mas_simbolos[i].valor = atoi(valoresChar[i]); //transformamos la cadena de digitos a un numero entero (cadena: "1234", entero: 1234);
		mas_simbolos[i].claves = cadena[i];
		mas_simbolos[i].next = ((i + 1) < cantidad) ? &mas_simbolos[i + 1] : NULL;  // Establecer el siguiente puntero
	}
	 // Abrir el archivo nuevamente para agregar datos
    FILE *tabla_file = fopen("tabla.txt", "a");
    if (tabla_file == NULL) {
        printf("No se pudo encontrar el archivo 'tabla.txt'\n");
        return 1;
    }
    printf("Se abrio el archivo 'tabla.txt' correctamente\n");

   int j;
   int k;
    for (j = 0; j < cantidad; j++) {
        fprintf(tabla_file, "%s %d\n", mas_simbolos[j].claves, mas_simbolos[j].valor);
    }
    fclose(tabla_file); // Escribir los datos al archivo

    // Liberar memoria
    for ( k = 0; k < cantidad; k++) {
        free(cadena[k]);  // Liberar las cadenas dinámicas
        free(valoresChar[k]);
    }
    printf("SE AGREEGARON SIMBOLOS A LA TABLA EXITOSAMENTE EN EL ARCHIVO 'tabla.txt'\n");
    return 0;
}
//-----------------------------------------------------------------
int cantidadDeLineas(FILE *archivoLeer){
	char linea[1024];
	int n = 0;
	//recorremos el archivo y mientras no se llegue a el final de este y hallan mas filas n incrementa 1.
	while(fgets(linea, sizeof(linea), archivoLeer) != NULL){
		n++;
	}
	return n;
}
//-----------------------------------------------------------------
int separaDigitosdeLetras(FILE* archivoLeer, char** poner_cadenas, char** poner_digitos, int n_lineas){
    int i;
    rewind(archivoLeer); //si ya se habia leido el archivo lo rebobinamos o volvemos a el incio
    // Asignamos memoria para cada línea (200 caracteres para cadenas, 200 para dígitos)
    for(i = 0; i < n_lineas; i++) {
        poner_cadenas[i] = (char*)malloc(200 * sizeof(char));  // Asigna memoria para las cadenas
        if(poner_cadenas[i] == NULL) {
            printf("ERROR al asignar memoria para 'cadena[%d]'\n", i);
            // Liberamos memoria previamente asignada
            int j;
            for(j = 0; j < i; j++) {
                free(poner_cadenas[j]);
                free(poner_digitos[j]);
            }
            fclose(archivoLeer);
            return 1;
        }

        poner_digitos[i] = (char*)malloc(200 * sizeof(char));  // Asigna memoria para los dígitos
        if(poner_digitos[i] == NULL) {
            printf("ERROR al asignar memoria para 'digitos[%d]'\n", i);
            // Liberamos memoria previamente asignada
            int j;
            for(j = 0; j < i; j++) {
                free(poner_cadenas[j]);
                free(poner_digitos[j]);
            }
            fclose(archivoLeer);
            return 1;
        }
    }

    char linea[1024];
    i = 0;
    
    // Leer cada línea
    while(i < n_lineas && fgets(linea, sizeof(linea), archivoLeer) != NULL) {
        int valor; //varaibel temporal para alamcenar el entero 
        char etiqueta[200]; //variable temporal para alamcenar la cadena o el nobmre de la etiqueta
        
        /* Extraer valor y etiqueta de la línea
        se esacnaea o obtiene de la linea el entero, y una cadena no superior a 200 caracteres, y se ignorarn los saltos de linea
        se verfica si ambos datos se obtuvieron correctamete
        se ponene en los arreglso correspondieten
        */
        if(sscanf(linea, "%d %199[^\n]", &valor, etiqueta) == 2) {
            sprintf(poner_digitos[i], "%d", valor);
            strcpy(poner_cadenas[i], etiqueta);
            i++;
        }
    }
    fclose(archivoLeer);
    return 0;
}
//**************************************************************

//**************************************************************
//-----------------------------------------------------------------
int separarVariables(const char* archivo){
	FILE *archivoP = fopen(archivo, "r");
	if(archivoP == NULL){
		printf("No se encontro el archivo '%s'\n", archivo);
		return 1;
	}
	printf("Se abrio correctamente el archivo '%s'\n", archivo);
	
	FILE *temp_var = fopen("tempVar.txt", "w");
	if(temp_var == NULL){
		printf("ERROR a el crear el archivo 'tempVar.txt'\n");
		fclose(archivoP);
		return 1;
	}
	printf("Se creo el archivo 'tempVar.txt'\n");
	
	encontrarVariables(archivoP, temp_var);
	
	FILE *temp2 = fopen("tempVar.txt", "r");
	if(temp2 == NULL){
		printf("No se encontro el achivo 'tempVar.txt'\n");
		return 1;
	}
	printf("Se encontro el archivo 'tempVar.txt'\n");
	FILE *var = fopen("variables.txt", "w");
	if(var == NULL){
		printf("ERROR a el crear el archivo 'variables.txt'\n");
		fclose(temp2);
		return 1;
	}
	printf("Se creo el archivo 'variables.txt'\n");
	
	eliminarDuplicados(temp2, var);
	
	FILE *vart= fopen("variables.txt", "r");
	if(vart == NULL){
		printf("No se encontro el archivo 'tempVar.txt'\n");
		return 1;
	}
	FILE *vart2 = fopen("tempVar3.txt", "w");
	if(vart2 == NULL){
		printf("No se creo el archivo 'tempVar3.txt'\n");
		fclose(vart);
		return 1;
	}
	
	excluir(vart, vart2);
	
	FILE *etiq = fopen("etiquetas.txt", "r");
	if(etiq == NULL){
		printf("No se encontro el archivo 'etiquetas.txt'\n");
		return 1;
	}
	FILE *var2 = fopen("tempVar3.txt", "r");
	if(var2 == NULL){
		printf("No se encontro el archivo 'tempVar3.txt'\n");
		return 1;
	}
	
	FILE *tempF1 = fopen("tempVar4.txt", "w");
	if(tempF1 == NULL){
		printf("ERROR a el crear el archivo 'tempVar.txt'\n");
		fclose(var2);
		return 1;
	}
	 int r =verificarVarYEtiq(var2, etiq, tempF1);
	 if(r!= 0) return 1;
	 printf("SE EXLUYERON LAS ETIQUETAS DE LAS VARIABLES\n");
	 FILE *varF = fopen("tempVar4.txt", "r");
	if(var2 == NULL){
		printf("No se encontro el archivo 'tempVar4.txt'\n");
		return 1;
	}
	
	FILE *tempF = fopen("tempVar.txt", "w");
	if(tempF == NULL){
		printf("ERROR a el crear el archivo 'tempVar.txt'\n");
		fclose(var2);
		return 1;
	}
	
	int result2 = copiarValoresConVariables(var2, tempF);
	if(result2 != 0){
		return 1;
	}
	
	//si todo sale bien eleiminamos los temporales y "actualizamos" el archivo variables.txt y agregamos los nuevos simbolos
	if(remove("tempVar3.txt")!= 0){
		printf("No se pudo eliminar el archivo 'tempVar3.txt'\n");
		return 1;
	}
	if(remove("tempVar4.txt")!= 0){
		printf("No se pudo eliminar el archivo 'tempVar4.txt'\n");
		return 1;
	}
	if(remove("variables.txt") != 0){
		printf("No se pudo eliminar el archivo 'variables.txt'\n");
		return 1;
	}
	else{
		if(rename("tempVar.txt", "variables.txt") != 0){
			printf("No se renombro el archivo 'tempVar.txt' a: 'variables.txt'\n");
			return 1;
		}
		printf("Se renombor el archivo 'tempVar.txt' a: 'variables.txt'\n");
	}
	  mas_simbolos("variables.txt");
	
	return 0;
}
//-----------------------------------------------------------------
void encontrarVariables(FILE* archivoLeer, FILE* archivoEscribir) {
    char linea[1024];
    int actual;
    char buffer;
    //mientra no se llegue a el final de el archivo
    while(1){
    	actual = fgetc(archivoLeer);
    	if(actual == EOF) break;
    	while((char)actual != ' '){
    		actual = fgetc(archivoLeer);
		}
		actual = fgetc(archivoLeer); //saltar el numero de linea y el esapacio
    	//si el caracter es @
    	if((char)actual == '@'){
            buffer = (char)actual;
    		actual = fgetc(archivoLeer);//pasamos a le siguiente caracter despues de @
    		//comprobamos qeu no sea un numero
    		if(!((char)actual >= '0' && (char)actual <= '9')){
    			//si no es numero agregamos toda la linea
    			fputc(buffer, archivoEscribir);
    			//entramos en un bucle para copiar toda la linea
    			while(actual != EOF&&(char)actual != '\n'){
    			fputc((char)actual, archivoEscribir);
				actual = fgetc(archivoLeer);	
				}
				if(actual == EOF) break; //si es final de archivo salir de el bucle
				fputc('\n', archivoEscribir);
			}
			//si es un numero ignoramos toda la linea
			else{
				while(actual != EOF &&(char)actual != '\n' && (char)actual != '\0' && (char)actual != ' '){
				actual = fgetc(archivoLeer);	
				}
				if(actual == EOF) break; //si es final de archivo salir de el bucle
			}
			
		}
		//si no es @ ignoramos la linea;
		else {
		while(actual != EOF&&(char)actual != '\n' && (char)actual != '\0' && (char)actual != ' '){
				actual = fgetc(archivoLeer);	
				}
				if(actual == EOF) break; //si es final de archivo salir de el bucle
			}
	}

    fclose(archivoLeer);
    fclose(archivoEscribir);
}
//-----------------------------------------------------------------
void eliminarDuplicados(FILE *archivoLeer, FILE* archivoEscribir) {
    char line[1024];
    char **lineasLeidas = NULL; // Array dinámico para almacenar líneas leídas
    int numLineasLeidas = 0;    // Número de líneas leídas
    int esDuplicado;
    int i;
    // Leer línea por línea del archivo
    while (fgets(line, sizeof(line), archivoLeer)) {
        esDuplicado = 0;
      
        // Compara la línea con las líneas previamente leídas
        for (i = 0; i < numLineasLeidas; i++) {
            if (strcmp(lineasLeidas[i], line) == 0) {
                esDuplicado = 1; // Se encontró una línea duplicada
                break;
            }
        }

        // Si la línea no es duplicada, escribirla en el archivo de salida
        if (!esDuplicado) {
            fputs(line, archivoEscribir);

            // Almacenar la línea leída para futuras comparaciones
            lineasLeidas =(char**)realloc(lineasLeidas, (numLineasLeidas + 1) * sizeof(char*));
            lineasLeidas[numLineasLeidas] = (char*)malloc(strlen(line) + 1);
            strcpy(lineasLeidas[numLineasLeidas], line);
            numLineasLeidas++;
        }
    }

    // Liberar memoria de las líneas leídas
    for (i = 0; i < numLineasLeidas; i++) {
        free(lineasLeidas[i]);
    }
    
free(lineasLeidas);
fclose(archivoLeer);
fclose(archivoEscribir);
}
//-----------------------------------------------------------------
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
   fclose(archivoLeer);
   fclose(archivoEscribir);	
   return 0;
}
//-----------------------------------------------------------------
void excluir(FILE *archivoLeer, FILE *archivoEscribir) {
    char linea[1024];
    char subcadena[] = "R0 R1 R2 R3 R4 R5 R6 R7 R8 R9 R10 R11 R12 R13 R14 R15 SCREEN KBD SP LCL THIS THAT ARG";
    char cadena[10];
    
    // Preprocesar las subcadenas válidas
    char *variables[24];
    int total_vars = 0;
    char *token = strtok(subcadena, " ");
    
    while (token != NULL && total_vars < 24) {
        variables[total_vars++] = token;
        token = strtok(NULL, " ");
    }
    int i;
    // Procesar cada línea
    while (fgets(linea, sizeof(linea), archivoLeer) != NULL) {
        if (linea[0] == '@') {
            // Extraer cadena después del @
            if (sscanf(linea + 1, "%9s", cadena) != 1) {
                fputs(linea, archivoEscribir);
                continue;
            }
            
            // Verificar coincidencias
            int coincidencia = 0;
            
            for (i = 0; i < total_vars; i++) {
                if (strcmp(cadena, variables[i]) == 0) {
                    coincidencia = 1;
                    break;
                }
            }
            
            // Escribir solo si no hay coincidencia
            if (!coincidencia) {
                fputs(linea, archivoEscribir);
            }
        } else {
            fputs(linea, archivoEscribir);
        }
    }

    fclose(archivoLeer);
    fclose(archivoEscribir);
    printf("SE EXCLUYERON LAS VARIABLES PREDEFINIDAS\n");
    return;
}
//-----------------------------------------------------------------
const char* m_agua = "Autor: Pablo Riveros - Proyecto Hack";
//-----------------------------------------------------------------
int verificarVarYEtiq(FILE *archivoLeer, FILE* archivoComparar, FILE *archivoEscribir){ 
    char *cadenaVar2 = (char *)malloc(1024 * sizeof(char));//asginamos memoria dinamica para la cadena de las variables
    if(cadenaVar2 == NULL){
    	printf("ERROR a el asginar memoria para 'cadenaVar2'\n");
    	fclose(archivoLeer);
    	fclose(archivoEscribir);
    	return 1;
	}
    char *cadenaEtiq2 = (char *)malloc(1024 * sizeof(char));//asginamos memoria dinamica para la cadena de las etiquetas
	if(cadenaEtiq2 == NULL){
    	printf("ERROR a el asginar memoria para 'cadenaEtiq2'\n");
    	fclose(archivoLeer);
    	fclose(archivoEscribir);
    	return 1;
	}  
    int actual = fgetc(archivoLeer);//primer caracter
    while(actual != EOF){
    	memset(cadenaVar2, 0, sizeof(1024));//reestablecr el arreglo a 0
    	memset(cadenaEtiq2, 0, sizeof(1024));//reestablecer el arreglo a 0
    	int i = 0, r = 0;
    	
    	if(actual == EOF) break;//salir de el bucle
		actual = fgetc(archivoLeer); //caracter despues de el @
	   //obtenemos el nombre de la variables
	   int j= 0;
		while(actual != EOF && (char)actual != '\n'){
			cadenaVar2[j]= (char)actual;
			j++;
			actual = fgetc(archivoLeer);
		}
		cadenaVar2[j]= '\0';
		rewind(archivoComparar);//rebobinamos el arhcivo etiqeutas.txt para volverlo a leer desde el principio
		char *c=etiq( cadenaEtiq2, archivoComparar);//tomamos el numero de linea de la etiqueta y su cadena
		//entra en un bucle para comparar la cadena de la variable con cada cadena de etiqueta
		while(c != NULL){
			//si la cadena es identica no se pone en archivoEscrbir
			if(strcmp(cadenaVar2,cadenaEtiq2) == 0){
				r = 1;
				break;
			}
			memset(cadenaEtiq2, 0, sizeof(1024));//limpiamos la cadena de etiqueta
		  c=etiq(cadenaEtiq2, archivoComparar);//tomamos la cadena de la linea siguiente a la anterior y su numero de liena de la etiqueta
		}
		if(r == 0){
			fputc('@', archivoEscribir);
			fputs(cadenaVar2, archivoEscribir);
			fputc('\n', archivoEscribir);
		} 
		//cuando haya comparado la variable con todas las etiquetas va a la siguietn varaible para hacer lo mismo
		actual = fgetc(archivoLeer);
	}
	//cuando ya se comparo todas las variables se cierran los archivos y se libera la memoria
	fclose(archivoLeer);
    fclose(archivoEscribir);
	free(cadenaEtiq2);
	free(cadenaVar2);
	return 0;
}
//-----------------------------------------------------------------
char *etiq(char *cadena, FILE *etiq){
	int actual;
	while(1){
		actual = fgetc(etiq); //primer carater
		if(actual == EOF) return NULL;
		//obtener el numero de linea
		while((char)actual != ' '){
			actual = fgetc(etiq);
		}
		actual = fgetc(etiq); //caracter despues de el espacio
		int i = 0;
		//obtener la cadena
		while((char)actual != '\n' && actual != EOF && (char)actual != '\0' && (char)actual != ' '){
			*cadena= (char)actual;
			cadena++;
			actual = fgetc(etiq);
		}
		*cadena= '\0';
		if((char)actual == '\n' || (char)actual == '\0' ||(char)actual == ' ') break; //si es fin de linea o de cadena o esapcio salir
	}
	return cadena;
	
}
//**************************************************************

//-----------------------------------------------------------------
int limpiartxtPr(const char* archivo) {
    // Abrimos el archivo de entrada en modo lectura
    FILE *archivoP = fopen(archivo, "r");
    if (archivoP == NULL) {
        printf("No se encontró el archivo '%s'\n", archivo);
        return 1;
    }

    // Creamos un archivo temporal en modo escritura
    FILE *temp = fopen("temp.txt", "w");
    if (temp == NULL) {
        printf("ERROR al crear el archivo temporal\n");
        fclose(archivoP); // Cerramos el archivo de entrada en caso de error
        return 1;
    }

    char linea[1024]; // Buffer para almacenar cada línea leída del archivo
    while (fgets(linea, sizeof(linea), archivoP) != NULL) {
        // Buscar el primer espacio en la línea
        char *ptrEspacio = strchr(linea, ' ');
        if (ptrEspacio != NULL) {
            // Si encontramos un espacio, verificamos el siguiente carácter
            if (*(ptrEspacio + 1) == '(') {
                // Si el siguiente carácter es un paréntesis '(', no escribimos la línea en el archivo temporal
                continue;
            }
        }

        // Si no encontramos un paréntesis después del espacio, escribimos la línea en el archivo temporal
        fprintf(temp, "%s", linea);
    }

    // Cerramos ambos archivos
    fclose(archivoP);
    fclose(temp);

    // Eliminamos el archivo original
    if (remove(archivo) != 0) {
        printf("No se eliminó el archivo '%s'\n", archivo);
        return 1;
    }

    // Renombramos el archivo temporal al nombre original del archivo
    if (rename("temp.txt", archivo) != 0) {
        printf("No se pudo renombrar el archivo temporal\n");
        return 1;
    }

    printf("Se ha limpiado el archivo '%s' correctamente\n", archivo);
    return 0;
}
//**************************************************************
//-----------------------------------------------------------------
int limpiar_tabla(){
	FILE *tabla = fopen("tabla.txt", "r");
	if(tabla == NULL){
		printf("No se encontro el archivo 'tabla.txt'\n");
		return 1;
	}
	printf("Se abrio el archivo 'tabla.txt'\n");
	FILE *temp= fopen("temporalta.txt", "w");
	if(temp == NULL){
		printf("ERROR  a el crear el archivo 'temporalta.txt'\n");
		fclose(tabla);
		return 1;
	}
	
	
	eliminarDuplicados(tabla, temp);
	
	FILE *tabla2 = fopen("tabla.txt", "r");
	if(tabla2 == NULL){
		printf("No se encontro el archivo 'tabla.txt'\n");
		return 1;
	}
	printf("Se abrio el archivo 'tabla.txt'\n");
	FILE *temp2= fopen("temporalta.txt", "w");
	if(temp2 == NULL){
		printf("ERROR  a el crear el archivo 'temporalta.txt'\n");
		fclose(tabla2);
		return 1;
	}
	
	eliminarDuplicadosTabla(tabla2, temp2);
	
	if(remove("tabla.txt") != 0){
		printf("No se pudo eliminar el archivo 'tabla.txt'\n");
        return 1;
	}
	else{
		if(rename("temporalta.txt", "tabla.txt") != 0){
			printf("No se puedo renombrar el archivo 'temporalta.txt'\n");
			return 1;
		}
		printf("Se renombro el archivo 'temporalta.txt' a: 'tabla.txt'\n");
	}
	system("cls");
	printf("PROCESO DE PREPARACION TERMINADO EXITOSAMENTE\n");
	return 0;
}
//-----------------------------------------------------------------
void eliminarDuplicadosTabla(FILE *archivoLeer, FILE *archivoEscribir){
    char line[1024];  // Para almacenar cada línea leída
    char lineCopy[1024]; // Copia de la línea para análisis
    char **palabrasVistas = NULL; // Arreglo dinámico para almacenar las palabras vistas
    int numPalabrasVistas = 0;    // Contador de palabras vistas
    int esDuplicado;
    int i;

    while (fgets(line, sizeof(line), archivoLeer)) {
        strcpy(lineCopy, line);  // Hacemos una copia de la línea original

        // Extraer la primera palabra de la copia
        char *primeraPalabra = strtok(lineCopy, " ");

        if (primeraPalabra == NULL) {
            continue;
        }

        esDuplicado = 0;

        // Comprobar si la palabra ya ha sido vista
        for (i = 0; i < numPalabrasVistas; i++) {
            if (strcmp(palabrasVistas[i], primeraPalabra) == 0) {
                esDuplicado = 1;
                break;
            }
        }

        if (!esDuplicado) {
            fputs(line, archivoEscribir); // Usamos la línea original completa
            // Guardamos la palabra
            palabrasVistas = (char**)realloc(palabrasVistas, (numPalabrasVistas + 1) * sizeof(char*));
            palabrasVistas[numPalabrasVistas] = (char*)malloc(strlen(primeraPalabra) + 1);
            strcpy(palabrasVistas[numPalabrasVistas], primeraPalabra);
            numPalabrasVistas++;
        }
    }

    // Liberar memoria
    for (i = 0; i < numPalabrasVistas; i++) {
        free(palabrasVistas[i]);
    }
    free(palabrasVistas);

    fclose(archivoLeer);
    fclose(archivoEscribir);
}
//**************************************************************

//AQUI TERMINA TODA LA LIMPIEZA Y PROCESOS DE "PREPARACION"-----------------------------------------------------------------

//COMIENZA EL PROCESO DE ENSAMBLAJE DE INSTRUCCIONES-----------------------------------------------------------------------
int ensamblar(const char* archivo){
	remove("variables.txt");
	remove("etiquetas.txt");
	FILE *archivoP = fopen(archivo, "r");
	if(archivoP == NULL){
		printf("No se encontro el archivo '%s'\n",archivo);
		return 1;
	}
	int cantidad = cantidadDeLineas(archivoP);//tomamos la cantidad de lineas de el archivo orginal
	fclose(archivoP);
	int n; 
	n=tomarInstruccionesAyC(archivo, cantidad);
	if(n != 0) return 1;
	system("cls");//limpiar consola
	n = ensamblarA("Ainstrucciones.txt", cantidad);
	if(n!= 0) return 1;
	
	n = ensamblarC("Cinstrucciones.txt", cantidad);
	if(n!= 0) return 1;
	FILE* insA = fopen("Aensamblado.txt", "r");
	if(insA == NULL){
		printf("No se encontro el archivo 'Aensamblado.txt'\n");
		return 1;
	}
	printf("Se abrio el archivo 'Aensamblado.txt'\n");
	FILE* insC = fopen("Censamblado.txt", "r");
	if(insC == NULL){
		printf("No se encontro el archivo 'Censamblado.txt'\n");
		fclose(insA);
		return 1;
	}
	printf("Se abrio el archivo 'Censamblado.txt'\n");
	FILE* ensam = fopen("ensamblado.txt", "w");
	if(ensam == NULL){
		printf("ERROR a el crear el archivo 'ensamblado.txt'\n");
		fclose(insC);
		fclose(insA);
		return 1;
	}
	printf("Se creo el archivo 'ensamblado.txt'\n");
	n = leerYOrdenarYEscribir(insC, insA, ensam, cantidad);
	if(n != 0) return 1;
	if(remove("Aensamblado.txt") != 0){
		printf("ERROR a el eliminar el archivo 'Aensamblado.txt'\n");
	   return 1;
	}
	if(remove("Censamblado.txt") != 0){
		printf("ERROR a el eliminar el archivo 'Censamblado.txt'\n");
		return 1;
	}
	n = archivoHack("ensamblado.txt");
	if(n!= 0) return 1;
	system("cls");
	printf("\nSE ENSAMBLO EL CODIGO CORRECTAMENTE\n");
	return 0;

}
//-----------------------------------------------------------------
int tomarInstruccionesAyC (const char* archivo, int cantidad){
	printf("OBTENIENDO INSTRUCCIONES A y C...\n");
	FILE *archivoP = fopen(archivo, "r");
	if(archivoP == NULL){
		printf("No se encontro el archivo '%s'\n", archivo);
		return 1;
	}
	printf("Se abrio el archivo '%s'\n", archivo);
	
	FILE *insA = fopen("Ainstrucciones.txt", "w");
	if(insA == NULL){
		printf("ERROR a el crear el archivo 'Ainstrucciones.txt'\n");
		fclose(archivoP);
		return 1;
	} 
	printf("Se creo el archivo 'Ainstrucciones.txt'\n"); 
	
	FILE* insC = fopen("Cinstrucciones.txt", "w");
	if(insC == NULL){
		printf("ERROR a el crear el archivo 'Cinstrucciones.txt'\n");
		fclose(archivoP);
		fclose(insA);
		return 1;
	}
	printf("Se creo el archivo 'Cinstrucciones.txt'\n");
	//mientras no se llegue a el final de la linea
	char linea[cantidad+1024]; //almacena la linea completa
	while(fgets(linea, sizeof(linea), archivoP) != NULL){
		char *c = strchr(linea, '@');//buscamos el @ en la linea que indica que es una instruccion A
		if(c!= NULL){
			fputs(linea, insA);//poner la linea completa en el nuevo archivo de instrucciones A
		}
		else{
		fputs(linea, insC);//poner la linea completa en el archivo de instrrucciones C
	   }
	}
   //despues de recorrer todo el archivo
   fclose(archivoP);
   fclose(insA);
   fclose(insC);
   printf("SE OBTUVIERON LAS INSTRUCCIONES A y C\n");
   return 0;
}
//-----------------------------------------------------------------
int ensamblarA (const char* Ains, int cantidad){
	printf("\nENSAMBLANDO INSTRUCCIONES A...\n");
	FILE *Af = fopen(Ains, "r");
	if(Af == NULL){
		printf("No se encontro el archivo '%s'\n", Ains);
		return 1;
	}
	printf("Se abrio el archivo '%s'\n", Ains);
	FILE *ensam = fopen("Aensamblado.txt", "w");
	if(ensam == NULL){
		printf("ERROR a el crear el archivo 'Aensamblado.txt'\n");
		fclose(Af);
		return 1;
	}
	printf("Se creo el archivo 'Aensamblado.txt'\n");
	FILE *tabla = fopen("tabla.txt", "r");
	if(tabla == NULL){
		printf("No se encontro el archivo 'tabla.txt'\n");
		return 1;
	}
	printf("Se abrio el archivo 'tabla.txt'\n");
	int actual = 0;
	char *cadena=(char*)malloc(1024);//almacena la cadena leida
	int valor = 0;//almacena el valor actual como entero
	//mientras no se llegue a el final de el archivo
	while((actual=fgetc(Af)) != EOF){
		memset(cadena, 0,sizeof(cadena));
		char *bin2 = NULL;//almacena la cadena binaria 
		if(actual == EOF){
			fclose(Af);
			fclose(ensam);
			free(cadena);
			break;//salimos de el bucle
		}
		while((char)actual != ' '){
			fputc((char)actual, ensam);//ponemos el numero de linea en el nuevo archvio
			actual = fgetc(Af);//vamos a el siguiente caracter
		}
		fputc((char)actual, ensam);//incluir el espacio
		actual = fgetc(Af);//vamos a el siguiente caracter despues de el espacio
		actual = fgetc(Af);//saltamos el @
		int i = 0;
		//mientras no se llegue a el final de linea
		while(actual != EOF && (char)actual != '\n'){
			cadena[i] = (char)actual;
			i++;
			actual = fgetc(Af);
		}
		cadena[i] = '\0';
		//si es un numero en lugar de una cadena lo convertimos directamente
		if(cadena[0] >= '0' && cadena[0] <= '9'){
			valor = atoi(cadena);
			bin2 = EnteroABin(valor);
			fputc('0', ensam);
			fputs(bin2, ensam);
			fputc('\n', ensam);    
			free(bin2);
		}
		 else{
	    valor = buscarValor(tabla, cadena, cantidad);
		bin2 = EnteroABin(valor);
		fputc('0', ensam);//convencion para instrucciones el bit 16 siempre es el opcode(bit que indica que instrucción es si A o C) y para instrucciones A siempre es 0 los otros 15 son de valor
		fputs(bin2, ensam);//poner el binario
		fputc('\n', ensam);        // Aquí se añade el salto de línea
		free(bin2);//liberar la memoria utilizada en la funcion EnteroABin
	   }
	}
	fclose(Af);
	fclose(ensam);
	if(remove("Ainstrucciones.txt") != 0){
		printf("No se elimino el archivo 'Ainstrucciones.txt'\n");
	    return 1;
	}
	printf("Se elimino el archivo 'Ainstrucciones.txt'\n");
	printf("INSTRUCCIONES A ENSAMBLADAS\n");
	return 0;
}
//-----------------------------------------------------------------
int buscarValor(FILE *tabla, char *cadena, int cantidad){
	rewind(tabla);
	char *cdtabla= (char*)malloc(1024);//almacena la cadena obtenidad de la tabla
	char valor[cantidad+1024];//almacenamos el valor
	int actual = 0;
	while(!feof(tabla)){
		memset(cdtabla, 0, sizeof(1024));
		memset(valor,0, sizeof(valor));
		
		actual = fgetc(tabla);
		int i = 0;
		//obtener la cadena que simpre va antes de el espacio
		while((char)actual != ' '){
			cdtabla[i]=(char)actual;
			i++;
			actual = fgetc(tabla);
		}
		cdtabla[i] = '\0';	
		actual = fgetc(tabla);//caracter despues de el espacio
		//obtener el valor 
		int j = 0;
		while(actual != EOF && (char)actual != '\n' && (char)actual !='\0' && (char)actual !=' '){
			valor[j] = (char)actual;
			j++;
			actual = fgetc(tabla);//vamos a el siguiente caracter
		}
		valor[j] = '\0';
		if(strcmp(cadena, cdtabla) == 0){
			int valorint= atoi(valor);
			free(cdtabla);
		 return valorint;//devolvemos el valor como entero
	     }
	     continue;
	}
	free(cdtabla);
	return 0;//esto nunca va a salir
}
//-----------------------------------------------------------------
char *EnteroABin(int valor_entero) {
    char *bin = (char*)malloc(16); // 15 bits + 1 para '\0'
    memset(bin, 0, 16);
    if (bin == NULL) return NULL; // por seguridad para poder devolver la cadena sin problemas
    int i;
    for (i = 14; i >= 0; i--) {
        bin[14 - i] = ((valor_entero >> i) & 1) ? '1' : '0';//guardamos cada bit, y el bit mas significativo esta a la izquierda (bin[0])
    }

    bin[15] = '\0';
    return bin;
}
//-----------------------------------------------------------------
int ensamblarC(const char* Cins, int cantidad){
	printf("\nENSAMBLANDO INSTRUCCIONES C...\n");
	FILE *Cf = fopen(Cins, "r");
	if(Cf == NULL){
		printf("No se encontro el archivo '%s'\n", Cins);
		return 1;
	}
	printf("Se abrio el archivo '%s'\n", Cins);
	FILE *ensam = fopen("Censamblado.txt", "w");
	if(ensam == NULL){
		printf("ERROR a el crear el archivo 'Censamblado.txt'\n");
		fclose(Cf);
		return 1;
	}
    printf("Se creo el archivo 'Censamblado.txt'\n");
    
    IdentificarInstruccion(Cf, ensam);
    if(remove(Cins) != 0){
    	printf("ERROR a el eliminar el archivo '%s'\n", Cins);
    	return 1;
	}
	printf("Se elimino el archivo '%s'\n", Cins);
    printf("INSTRUCCIONES C ENSAMBLADAS\n");
    return 0;
	
}
//-----------------------------------------------------------------
void IdentificarInstruccion(FILE *insC, FILE *EscribirEnsamblado){
   int actual;
   char* s =NULL;
   //mientras no se llegue a el final de linea
   while((actual = fgetc(insC)) != EOF){
   	 //ponemos el numero de linea en el archivo de instrucciones C ensambladas
   	while((char)actual != ' '){
   		fputc((char)actual, EscribirEnsamblado);
   		actual = fgetc(insC);
	   }
	   fputc((char)actual, EscribirEnsamblado);//agregamos el espacio
	   actual = fgetc(insC);//vamos a el siguiente caracter despues de el espacio
	   
   	     s=calculo(actual, insC);//todas las intrucciones C tienen que tener un calculo y esta funcion integra las otras de destino y salto entonces por eso solo llamamos a calculo y obtenemos la cadena de este
		fputs(s, EscribirEnsamblado);
		fputc('\n', EscribirEnsamblado);
		free(s);  // también liberas el string ensamblado
		s= NULL;
   }
   fclose(insC);
   fclose(EscribirEnsamblado);
   return;
}
//es una estructura de valores constantes asignados a cada parte de un calculo para luego utilizarlos en una "formula" que da el comp esperado
typedef struct {
	//valores para operadores 
	int menos;//19
	int mas;// 2
	int negar;//1
	int AND;//0
	int OR;// 21
	//valores para constantes
	int uno;//63
	int cero;//42
	//valores para variables (entradas de la ALU)
	int x;//12
	int y;//48
}patron;
//variable tipo estructura y definimos los valores
patron valores={
    .menos=19,
    .mas=2,
    .negar=1,
    .AND=0,
    .OR=21,
    .uno=63,
    .cero=42,
    .x=12,
    .y=48,
};
//-----------------------------------------------------------------
char anterior2 = '\0'; //unica variable global especial para entregar el anteriro a comp
char *destino(char *actual, char** copiaLineaActualizado){
    char *cadena = (char*)malloc(4); // para los 3 caracteres + '\0'
    char* bits = NULL;
    memset(cadena, 0, 4); // limpia cadena
    
    int i = 0;
    cadena[i] = *actual;
    i++;
    //verificamos que el caracter incial sea de destino (A, M o D), si no es asi, devuelve 000
    if (*actual != 'M' && *actual != 'D' && *actual != 'A') {
       memset(cadena, 0, 4);
    strcpy(cadena, "000"); // sin salto
        return cadena;
    }
    //si es un caracter de destino seguimos hasta encontrar un = o un operador, si hay un operador salir
    actual++;//pasamos a el siguiente caracter y si no es un operador entonces es un destino
    if(*actual == 'M' || *actual == 'A' || *actual == 'D' || *actual == '='){
    	while(*actual != '='){
    		cadena[i] = *actual;
    		i++;
    		actual++;
		}
		//cuando se llegue a el =
		cadena[i] = '\0';
        actual++;//pasamos a el siguiente caracter despues de el =
        *copiaLineaActualizado = actual;
        bits = bitsDestino(cadena);
        int i = 0;
        char *n = bits;
        char *copiaBits = (char*)malloc(4);
        while (*bits != '\0') {
            copiaBits[i] = *bits;
            bits++;
            i++;
        }
        copiaBits[i] = '\0';
        free(cadena);
        free(n);
        bits = NULL;
        n = NULL;
        return copiaBits;
	}
	//si hay un operador despues
	anterior2 =cadena[0]; 
    memset(cadena, 0, 4);
    strcpy(cadena, "000"); // sin salto
        return cadena;
}
//-----------------------------------------------------------------
char* bitsDestino(char *destino) {
    if (destino == NULL){
        char *bin = (char *)malloc(4);
        if (bin == NULL) return NULL;
        strcpy(bin, "000");
        return bin;
    }

    int bits = 0;
    if (strchr(destino, 'A')) bits |= 4;
    if (strchr(destino, 'D')) bits |= 2;
    if (strchr(destino, 'M')) bits |= 1;

    char *bin = (char *)malloc(4);
    if (bin == NULL) return NULL;

    bin[0] = (bits & 4) ? '1' : '0';
    bin[1] = (bits & 2) ? '1' : '0';
    bin[2] = (bits & 1) ? '1' : '0';
    bin[3] = '\0';
    return bin;
}
//-----------------------------------------------------------------
char* calculo(int actual, FILE* leer) {
	char *copiaLinea = (char*)malloc(10);//9+1 para '\0'
	char *n = copiaLinea;
	if(copiaLinea == NULL){
		printf("ERROR a el asignar memoria para copiaLinea\n");
		return NULL;
	}
	memset(copiaLinea, 0, 10);
	int i = 0;
	while(actual !=EOF && (char)actual != '\n' && (char)actual != '\0' && (char)actual != ' '){
		copiaLinea[i] = (char)actual;
		i++;
		actual = fgetc(leer);
	}
	copiaLinea[i] = '\0';
	
    Cins completo = {0}; // inicializa todo a NULL o 0
        completo.destino = destino(copiaLinea, &copiaLinea); // ya devuelve malloc
        if (*copiaLinea == 'M') completo.M = '1';
        else completo.M = '0';
        
        completo.comp = operandoA(copiaLinea, &copiaLinea, &completo.M); // ya devuelve malloc
        completo.jump = salto(copiaLinea); // ya devuelve malloc
        free(n);
    char *h = ensamblarFinal(completo);
    return h;
}
//-----------------------------------------------------------------
char* operandoA(char *actual, char**actualizado, char* conM){
	*conM = '0';//incializamos completo.M a 0
	char anterior = anterior2;
	//si es M o A corresponde a la entrada Y de la ALU
	if(*actual == 'M'||*actual== 'A'|| *actual == 'D' || *actual == '1' || *actual == '0' ){
		anterior = *actual;
		if(*actual == 'M') *conM = '1';//vemos si tiene M
		actual++;
		*actualizado = actual;
		//si es final de linea o ; indica que termino la parte de el calculo
		if(*actual == '\n' || *actual == ';' || *actual == ' ' || *actual == '\0'){
			*actualizado = actual;
			if(anterior == 'M' || anterior == 'A'){
				char *h = EnteroABin(valores.y);
				return tomarlos6(h);
			}
			else if(anterior == 'D'){
				char *x = EnteroABin(valores.x);
				return tomarlos6(x);
			}
			else if(anterior == '0'){
				char *h = EnteroABin(valores.cero);
				return tomarlos6(h);
			}
			else {
				char *uno = EnteroABin(valores.uno);
				return tomarlos6(uno);
			}
		}
		//si es -,+, & o | llamamos a operador 
		else if(*actual == '-' || *actual == '+'|| *actual== '&' || *actual== '|'){
			 int n =operador(actual, actualizado, anterior, conM);//porque dentro de esta funcion se hacen todos los "calculos" necesarios para el siguiente y anterior operando y operador
			 char *h = EnteroABin(n);
			 return tomarlos6(h);
		}
	}
	else if(*actual == '-' || *actual == '!'){
		anterior = *actual;
	    actual++;
	    *actualizado = actual;
	    int n = operador(actual, actualizado, anterior, conM);
	    char *s = EnteroABin(n);
	    return tomarlos6(s);
	}
	return NULL;//esto nunca va a suceder o no deberia
}
//-----------------------------------------------------------------
char *tomarlos6(char *punt){
	char *n = punt;
	char *bin = (char*)malloc(7);// 6 + 1 para el '\0'
	int i;
	//saltamos los ultimos 10 bits debido a que no nos interesan solo nececitamos los primeros 6 bits
	for(i = 0; i < 9; i++){
		punt++;
	}
	//tomamos los 6 bits restantes
	for(i = 0; *punt != '\0'; i++){
		bin[i] = *punt;
		punt++;
	}
	bin[i] = '\0';
	free(n);//liberamos la memoria que almacenaba los 16 bits
	punt = NULL;//apunte a nada
	n = NULL;//apunte a nada
	return bin;
}
//-----------------------------------------------------------------
int operador(char *actual, char**actualizado, char anterior, char* conM){
      //si es un operador como + 
      if(*actual == '+'){
    	int n = valores.mas+ 6;//valor de y que es 2(2 porque a el final y+ o x+ es 2 (000010) + 6(que es un arreglo)

      	//vemos si el anterior es Y o X
      	if(anterior == 'A' || anterior == 'M'){
      		if(*actual == 'M') *conM = '1';
      		 actual++; //pasamos a el siguiente caracter desues de el signo +
      		 *actualizado = actual;
      		 if(*actual == '1'){
      		 	 return valores.uno - n;//luego le restamos el valor de el operandoB con n y tenemos el entero que luego pasaremos a binario (63-8=55)
			   }
			   else if(*actual == 'D'){
			   	return valores.mas;//porque no alteramos ni X ni Y solo sumamos(000010) qu es lo mismo que decir (y+ + 8 - x = 2)
			   }
			   else if(*actual == '0'){
			   	return 34; //porque pasamos X a 0 y Y lo dejamos igual (que es lo mismo que decir (y+ + 8 - 0 = 34)
			   }
		  }
		  //si es X (D)
		   else if(anterior == 'D'){
      		 actual++; //pasamos a el siguiente caracter desues de el signo +
      		 *actualizado = actual;
      		 if(*actual == '1'){
      		 	 return valores.uno - (valores.mas+30);//caso "especial" en el que ponemos 30 porque es un arreglo porque 2 + 30 = 32 y 63 - 32 = 31
			   }
			   else if(*actual == 'A' || *actual == 'M'){
			   	if(*actual == 'M') *conM = '1';
			   	return valores.mas;//porque no se altera X ni Y
			   }
			   else if(*actual == '0'){
			   	return 10; //porque pasamos Y a 0 y X lo dejamos igual( que es lo mismo que decir (x+ + 8 = 10)(001010)
			   }
		  }
		  //si es 0, es decir 0+D o 0+X
		  else if(anterior == '0'){
		  	actual++;
		  	*actualizado = actual;
		  	if(*actual == '1'){
		  		return valores.uno;
			  }
			  else if(*actual == 'A'|| *actual == 'M'){
			  	if(*actual == 'M') *conM = '1';
			  	return valores.y;
			  }
			  //si es D (0+D)
			  else{
			  	return valores.x;
			  }
		  }
	  }
	  // si es -
	  else if(*actual== '-'){
	  	int n = valores.menos + 6;//porque - + 6 = 25 (y- y x- = 19)(010011) 

      	//vemos si el anterior es Y o X
      	if(anterior == 'A' || anterior == 'M'){
      		if(*actual == 'M') *conM = '1';
      		 actual++; //pasamos a el siguiente caracter desues de el signo - 
      		 *actualizado = actual;
      		 if(*actual == '1'){
      		 	 return n+n;//luego le restamos el valor de el operandoB con n y tenemos el entero que luego pasaremos a binario (n+n = 50) (110010= y-1)
			   }
			   else if(*actual == 'D'){
			   	return n-valores.x;//porque alteramos a negativo X lo susamos con Y (000111) que es lo mismo que decir (y- - x = 7)
			   }
			   else if(*actual == '0'){
			   	return 34; //porque pasamos X a 0 y Y lo dejamos igual (que es lo mismo que decir (0+y = 34))(100010)
			   }
		  }
		  //si es X (D)
		   else if(anterior == 'D'){
      		 actual++; //pasamos a el siguiente caracter desues de el signo - 
      		 *actualizado = actual;
      		 if(*actual == '1'){
      		 	 return valores.menos-6;//caso "especial" en el que ponemos -6 porque es un arreglo porque 19 - 6 = 14 (001110=x-1)
			   }
			   else if(*actual == 'A' || *actual == 'M'){
			   	if(*actual == 'M') *conM = '1';
			   	return valores.menos;//porque no se altera X ni Y
			   }
			   else if(*actual == '0'){
			   	return 10; //porque pasamos Y a 0 y X lo dejamos igual( que es lo mismo que decir (x-0 = x+0 = 10)
			   }
		  }
		  //si es 0, es decir 0-x o 0-y = -x o -y
		  else if(anterior == '0'){
		  	actual++;
		  	*actualizado = actual;
		  	if(*actual == 'A' || *actual == 'M'){
		  		if(*actual == 'M') *conM = '1';
	  		return valores.y + 3;//porque en binario e 110011(es lo mismo que 51 que es 48+3 = 51)
		  }
		  else if(*actual == 'D'){
		  	return valores.x + 3; //porque en binario es 001111 = 15 (es lo mismo que decir que 12 + 3 = 15)
		  }
		  //si es 1
		  else{
		  	return valores.uno + 5;//porque es -1 (58)
		  }
		  }
	  }
	  //si es un operador como & o |
	  else if(*actual == '&'){
	  	if(anterior == 'D'){
	  	   actual++;//Pasamos a el siguiente caracter
	  	   *actualizado = actual;
	  	   if(*actual == 'A' || *actual == 'M'){
	  	   	if(*actual == 'M') *conM = '1';
	  		    return 0;//porque no se altera ningun bit de control
		     }
		     else if(*actual == '1'){
		     	return valores.x;//porque a el final solo pasamos a 1 Y y X lo dejamos igual 
			 }
			 else if(*actual == '0'){
			 	return 8; //estos son casos especiales porque solo pasamos a 0 el Y y X lo dejamos igual
			 }
		
		  }
		  //si es Y
		else if(anterior == 'A' || anterior == 'M'){
			if(*actual == 'M') *conM = '1';
			actual++;//Pasamos a el siguiente caracter
			*actualizado = actual;
	  	   if(*actual == 'D'){
	  		    return 0;//porque no se altera ningun bit de control
		     }
		     else if(*actual == '1'){
		     	return valores.y;//porque a el final solo pasamos a 1 X y Y lo dejamos igual 
			 }
			 else if(*actual == '0'){
			 	return 32; //estos son casos especiales porque solo pasamos a 0 el X y Y lo dejamos igual
			 }
		}
		
		else if(anterior == '0'){
			actual++;
			*actualizado = actual;
		  if(*actual == '1'){
		  	return 44;//porque pasamos a alguno a 0 y alguno a 1(101100 = 44)
		  }
		  else if(*actual == 'A' || *actual == 'M'){
		  	if(*actual == 'M') *conM = '1';
		  	return 8;//porque ponemos a X a 0 (001000 = 8)
		  }
		  else{
		  	return 32;//porque ponemos a Y a 0 (100000 = 32)
		  }
		}
	  }
	  //si es | que es operador OR
	  else if(*actual == '|'){
	  	if(anterior == 'D'){
	  		actual++;//Pasamos a el siguiente caracter
	  		*actualizado = actual;
	  	   if(*actual == 'A' || *actual == 'M'){
	  	   	if(*actual == 'M') *conM = '1';
	  		    return valores.OR;//porque solo se niegan X y Y y el resultado final de &( X | Y = 010101 = 21)
		     }
		     else if(*actual == '1'){
		     	return valores.uno;//porque a el final solo pasamos a 1 (111111)(X|1 = 1)
			 }
			 else if(*actual == '0'){
			 	return 8; //porque a el finla solo pasamos a 1 a Y(001000)(X | 0 = X)
			 }
		  }
		  else if(anterior == 'A' || anterior == 'M'){
		  	if(*actual == 'M') *conM = '1';
		  	actual++;//Pasamos a el siguiente caracter
		  	*actualizado = actual;
	  	   if(*actual == 'D'){
	  		    return valores.OR;//porque solo se niegan X y Y y el resultado final de &
		     }
		     else if(*actual == '1'){
		     	return valores.uno;//porque a el final la salida de OR con 1 simpre es 1 (Y| 1 = 1)(111111)
			 }
			 else if(*actual == '0'){
			 	return 32; //porque a el finla solo pasamos a 0 X y comparamos con Y (Y|0 = Y)
			 }
		  }
		  else if(anterior == '0'){
		  	actual++;
		  	*actualizado = actual;
		  	  if(*actual == '1'){
		  	  	return valores.uno;
				}
				else if(*actual == 'M' || *actual == 'A'){
					if(*actual == 'M') *conM = '1';
					return 32;
				}
				else if(*actual == 'D'){
					return 8;
				}
		  }
	  }
	  //si es -X o -Y
	  else if(anterior == '-'){
	  	if(*actual == 'A' || *actual == 'M'){
	  		if(*actual == 'M') *conM = '1';
	  		return valores.y + 3;//porque en binario e 110011(es lo mismo que 51 que es 48+3 = 51)
		  }
		  else if(*actual == 'D'){
		  	return valores.x + 3; //porque en binario es 001111 = 15 (es lo mismo que decir que 12 + 3 = 15)
		  }
	  }
	  //si es !X o !Y
	  else if(anterior == '!'){
	  	if(*actual == 'A' || *actual == 'M'){
	  		if(*actual == 'M') *conM = '1';
                return valores.y + valores.negar;//que es binario es 00101 = 49 (es lo mismo que decir que 48 + 1 = 49)
		  }
		  else if(*actual == 'D'){
		  	return valores.x + valores.negar;//que es binario es 001101 = 13 (es lo mismo que decir que 12+1=13)
		  }
	  }
	  //si no es ninguno de estos casos llamamos a constante 
	  int result = constante(actual, actualizado, anterior, conM);
	  return result;
}
//-----------------------------------------------------------------
int constante(char *actual, char**actualizado, char anterior, char* conM){
	
	if(anterior == '-'){
		if(*actual == '1'){
			return valores.uno - 5; // porque n binario es 111010 = 58(que es lo mismo que decir 63-5= 58)
		}
	}
	else if(anterior == '!'){
		if(*actual == '1'){
			return valores.cero;//porque !1 = 0
		}
	}
	else if(anterior == '1'){
		if(*actual == '-'){
			actual++;//pasamos a el siguiente caracter
			*actualizado = actual;
			if(*actual == 'M' || *actual == 'A'){
				if(*actual == 'M') *conM = '1';
				return 1+(~valores.y+1);//porque negamos el decimal de Y,y le sumamos 1 que da como resultado -y y le sumamos 1 que es 1-y(porque 1 es positvo, es lo mismo qeu decir -y+1)(complemento a 2 de y +1)
			}
			else if(*actual == 'D'){
				return 1+(~valores.x+1); //porque negamos el decimal de X,y le sumamos 1 que da como resultado -x y le sumamos 1 que es 1-x(porque 1 es positvo, es lo mismo qeu decir -x+1)(complemento a 2 de x + 1)
			}
			else if(*actual == '0'){
				 return valores.cero + 3; //porque en binarioes 101110=46(qeu es lo mismo que decir 42+3=46)
			}
		}
		else if(*actual == '+'){
			actual++;//pasamos a el siguiente caracter
			*actualizado = actual;
			if(*actual == 'M' || *actual == 'A'){
				if(*actual == 'M') *conM = '1';
				return valores.uno-8;//porque en binario es 110111 = 55(que es lo mismo que decir 63-8=55)
			}
			else if(*actual == 'D'){
				return (valores.uno-9)-23; //porque en binairo es 011111=31(que es lo mismo qeu decir 63-23-9 = 31)
			}
			else if(*actual == '0'){
				 return valores.cero + 3; //porque en binarioes 101110=46(qeu es lo mismo que decir 42+3=46)
			}
		}
		else if(*actual == '|'){
			//simpre se retorna 1 porque cualuqiero OR con 1 es 1 
			actual++;//pasamos a el siguiente caracter
			*actualizado = actual;
			if(*actual == 'M' || *actual == 'A'){
				if(*actual == 'M') *conM = '1';
				return valores.uno;
			}
			else if(*actual == 'D'){
				return valores.uno; 
			}
			else if(*actual == '0'){
				 return valores.uno; 
			}
			
		}
		else if(*actual == '&'){
			actual++;//pasamos a el siguiente caracter
			*actualizado = actual;
			if(*actual == 'M' || *actual == 'A'){
				if(*actual == 'M') *conM = '1';
				return valores.y;//porque en binario es 110000 = 48(que es lo mismo que decir 1&Y=48)
			}
			else if(*actual == 'D'){
				return valores.x; //porque en binairo es 001100=12(que es lo mismo qeu decir 1&D = 12)
			}
			else if(*actual == '0'){
				 return valores.cero; //porque en binarioes 10101=42(que es lo mismo que decir 1&0 = 0)
			}
		}
	}
	//si no es -1 o calculo con 1 devuelve 1
	return valores.uno;
}
//-----------------------------------------------------------------
char* salto(char* actual) {
    char *jump = (char*)malloc(4); // 3 bits + '\0'
    if (jump == NULL) return NULL;
    memset(jump, 0, 4);
    if(*actual != '\n' && *actual != '\0' && *actual != ' ') actual++;
    else {
    	strcpy(jump, "000"); // sin salto
        return jump;
	}
    if (*actual != 'J') {
        strcpy(jump, "000"); // sin salto
        return jump;
    }

    char buffer[4] = {0};
    int i = 0;

    // Leer hasta 3 letras
    while (i < 3 && *actual != '\n' && *actual!= ' ' && *actual!= '\0') {
        buffer[i++] = *actual;
        actual++;
    }
    buffer[i] = '\0';

    int valor = 0;
   // printf("%s", buffer);
    if (strcmp(buffer, "JGT") == 0) valor = 1;
    else if (strcmp(buffer, "JEQ") == 0) valor = 2;
    else if (strcmp(buffer, "JGE") == 0) valor = 3;
    else if (strcmp(buffer, "JLT") == 0) valor = 4;
    else if (strcmp(buffer, "JNE") == 0) valor = 5;
    else if (strcmp(buffer, "JLE") == 0) valor = 6;
    else if (strcmp(buffer, "JMP") == 0) valor = 7;
    else valor = 0; // sin salto válido

    // Convertir valor a binario de 3 bits
    jump[0] = (valor & 4) ? '1' : '0';
    jump[1] = (valor & 2) ? '1' : '0';
    jump[2] = (valor & 1) ? '1' : '0';
    jump[3] = '\0';
    return jump;
}
//-----------------------------------------------------------------
char* ensamblarFinal(Cins completo) {
    // Reservamos memoria para "111" + comp (6) + dest (3) + jump (3) + '\0'
    char* instruccion = (char*)malloc(17); // 3 + 6 + 3 + 3 + '\0'
    memset(instruccion, 0, 17);
    if (!instruccion) return NULL;
    if (!completo.M || !completo.comp || !completo.destino || !completo.jump) {
    free(instruccion);
    return NULL;
    }
    // El patrón es: 111accccccdddjjj
    sprintf(instruccion, "111%c%s%s%s", completo.M, completo.comp, completo.destino, completo.jump);
    //liberamos la memoria asginada en las funcionciones dentor de calculo
    free(completo.comp);
    free(completo.destino);
    free(completo.jump);
	completo.comp = NULL;
    completo.destino = NULL;
    completo.jump = NULL;
    completo.M='0';
    return instruccion;
}
//-----------------------------------------------------------------
int leerNumero(const char* linea, int cantidad) {
    char numero[cantidad];
    int i = 0;
    while (linea[i] != ' ' && linea[i] != '\0' && i < cantidad) {
        numero[i] = linea[i];
        i++;
    }
    numero[i] = '\0';
    return atoi(numero);
}
//-----------------------------------------------------------------
int leerYOrdenarYEscribir(FILE* archivo1, FILE* archivo2, FILE* archivoEscribir, int cantidad) {
    char *linea1 = (char*)malloc(1024 + cantidad);
    char *linea2 = (char*)malloc(1024 + cantidad);

    if (!linea1 || !linea2) {
        printf("Error al asignar memoria.\n");
        if (linea1) free(linea1);
        if (linea2) free(linea2);
        return 1;
    }

    char *c1 = fgets(linea1, 1024 + cantidad, archivo1);
    char *c2 = fgets(linea2, 1024 + cantidad, archivo2);

    while (c1 && c2) {
        int h1 = leerNumero(linea1, cantidad);
        int h2 = leerNumero(linea2, cantidad);

        if (h1 < h2) {
            fputs(linea1, archivoEscribir);
            c1 = fgets(linea1, 1024 + cantidad, archivo1);
        } else if (h2 < h1) {
            fputs(linea2, archivoEscribir);
            c2 = fgets(linea2, 1024 + cantidad, archivo2);
        }
		else return 1; //esto nunca deberia salir 
    }

    // Si archivo1 termina primero
    while (c2) {
        fputs(linea2, archivoEscribir);
        c2 = fgets(linea2, 1024 + cantidad, archivo2);
    }

    // Si archivo2 termina primero
    while (c1) {
        fputs(linea1, archivoEscribir);
        c1 = fgets(linea1, 1024 + cantidad, archivo1);
    }

    free(linea1);
    free(linea2);
    fclose(archivo1);
    fclose(archivo2);
    fclose(archivoEscribir);

    return 0;
}

int archivoHack(const char* ensamblado) {
    FILE *ensam = fopen(ensamblado, "r");
    if (ensam == NULL) {
        printf("No se encontró el archivo '%s'\n", ensamblado);
        return 1;
    }
    printf("Se abrió el archivo '%s'\n", ensamblado);

    FILE *hack = fopen("archivoHack.hack", "w");
    if (hack == NULL) {
        printf("ERROR al crear el archivo 'archivoHack.hack'\n");
        fclose(ensam);
        return 1;
    }
    printf("Se creó el archivo 'archivoHack.hack'\n");
    char linea[1024];
    fputc('\n', hack);
    while (fgets(linea, sizeof(linea), ensam)) {
        // Buscar el primer espacio
        char *despuesDelEspacio = strchr(linea, ' ');
        if (despuesDelEspacio != NULL) {
            despuesDelEspacio++; // Saltar el espacio
            // Eliminar salto de línea al final si existe
            size_t len = strlen(despuesDelEspacio);
            if (len > 0 && despuesDelEspacio[len - 1] == '\n') {
                despuesDelEspacio[len - 1] = '\0';
            }
            fprintf(hack, "%s\n", despuesDelEspacio);
        }
    }
    fclose(ensam);
    fclose(hack);
    
    if(remove(ensamblado) != 0){
    	printf("ERROR a el eliminar el archivo '%s'\n", ensamblado);
    	return 1;
	}
	printf("Se elimino el archivo '%s'\n", ensamblado);
	if(remove("archivo.txt") != 0){
		printf("ERROR a el eliminar el archivo 'archivo.txt'\n");
    	return 1;
	}
    return 0;
}
