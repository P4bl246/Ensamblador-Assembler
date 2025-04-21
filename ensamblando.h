#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h> 

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
void encontrarVariables(FILE* archivoLeer, FILE* archivoEscribir); // funcion para encontrar las variables y ponerlas en un archivo aparte(funcion interna)
void eliminarDuplicados(FILE *archivoLeer, FILE* archivoEscribir); // funcion para eliminar los duplicados o lineas duplicadas en un archivo(funcion interna)
int copiarValoresConVariables(FILE *archivoLeer, FILE *archivoEscribir);//funcion para asginar valores a las variables, o clave-valor, para luego usar la funcion 'mas_simbolos'(funcion interna)
int separarVariables(const char* archivo);//integra las 4 funciones anteriores y 'mas_simbolos', y les da los argumentos, estos es para crear los simbolos de las variables
//-----------------------------------------------------------------
int tomarVariables(const char* archivo);//tomar las varaibles y su numero de linea
char *etiq(char* poner_nlinea,char* cadena, FILE *etiq);//funcion para tomar cada cadena y numero de linea de etiquetas.txt
int verificarVarYEtiq();//funcion que integra las 2 funciones anterirores y compara cada cadena de varialbles.txt con cada cadena de etiquetas.txt
//-----------------------------------------------------------------
int limpiartxtPr(const char* archivo);//funcion para limpiar el archivo .txt principal e las etiquetas
//-----------------------------------------------------------------
void eliminarDuplicadosTabla(FILE *archivoLeer, FILE *archivoEscribir); //funcion para solo dejar las etiquetas si hay un caso en el que se haya puesto una variable con el mismo nombre de una etiqueta dejar la etiqueta(funcion interna)
int limpiar_tabla(); //funcion para limpiar la tabla de simbolos eliando simbolos repetidos si hay y integra la funcion anterior y de 'eliminarDuplicados'
//------------------------------*********************************
//AQUI TERMINAN LAS FUNCIONES DE LIMPIEZA Y PREPARACION-----------------------------------------------------------------

//FUNCIONES DE ENSAMBLAJE DE INSTRUCCIONES-----------------------------------------------------------------------

//AQUI TERMINAN LAS FUNCIONES DE ENSAMBLAJE DE INSTRUCCIONES--------------------------------------------------------


//AQUI SE HACE EL PROCESO DE ANALISIS SINTACTICO-------------------------------------
//**************************************************************
int analisis_sintactico(const char* archivo){
	int n, n2, n3, n4, n5, n6, n7, n8, n9, n10;
	n =copia_archivo(archivo);
	if(n != 0) return 1;
	
	n2 = limpiarLineas("copia.txt");
	if(n2 != 0) return 1;
	
	n4 = tratarEtiquetas("copia.txt");
	if(n4 != 0) return 1;
	
	n5 = tratarVariables("copia.txt");
	if(n5 != 0) return 1;
	
	n6 = numerarLineas("copia.txt");
	if(n6 != 0) return 1;
	system("cls");
	n7 = analizar_etiquetas("copia.txt");
	if(n7 != 0) return 1;
	
	n8 =analizar_instrucciones_A("copia.txt");
	if(n8 != 0) return 1;
	
	n9 = analizar_instrucciones_C("copia.txt");
	if(n9 != 0) return 1;
	
	n10 = eliminarArchivos();
	if(n10 != 0) return 1;
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
            
            if(actual == EOF) {
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
    
    int numeroLinea;
    int n, i;
    char numeros[6]; // Aumentado a 6 para garantizar espacio para el \0
    int cantidad = cantidadDeLineas(copia);
    char n_lineas[cantidad]; //obtenemos la cantidad de lineas que hay para poder obtener los caracteres necesaciros para el numero de linea
    int actual;
    rewind(copia);
    // Procesamos línea por línea
    while(1) { 
        // Limpiar los buffers
        memset(n_lineas, 0, sizeof(n_lineas));
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
        
        numeroLinea = atoi(n_lineas);
        // Leer el siguiente carácter (después del espacio)
        actual = fgetc(copia);
        
        // Procesar instrucción si es de tipo @
        if(actual == '@') {
            actual = fgetc(copia);
            
            if(actual == EOF || (char)actual == '\n' || (char)actual == ' ' || (char)actual == '\0') {
                printf("ERROR en la linea %d\n", numeroLinea);
                printf("DETALLES: Se esperan argumentos despues de el '@'\n");
                fclose(copia);
                return 1;
            }
            
            // Leer número después de @
            n = 0;
            if((char)actual >= '0' && (char)actual <= '9') {
                numeros[n] = (char)actual;
                n++;
                // Leer más dígitos
                while(1) {
                    actual = fgetc(copia);
                    
                    if((char)actual == '\n' || actual == EOF) {
                        break;
                    }
                    
                    if(!((char)actual >= '0' && (char)actual <= '9')) {
                        printf("ERROR en la linea %d\n", numeroLinea);
                        printf("DETALLES: no se reconoce esta sintaxis, corrijala poniendo un numero de 0-n o coloque el caracter primero\nEJEMPLO: @1234 o @h1234. @1234h(no se reconoce)\n");
                        fclose(copia);
                        return 1;
                    }
                    
                    numeros[n] = (char)actual;
                    n++;
                }
                
                numeros[n] = '\0';
                
            }
        // Avanzar hasta el final de la línea
        while((char)actual != '\n' && actual != EOF) {
            actual = fgetc(copia);
        }
  }
}
   printf("TERMINO EL ANALIZIS DE INSTRUCCIONES A\n");
    fclose(copia);
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
	actual = fgetc(soloC);
    if ((char)actual != '\n') {
        // Si comienza con D, M, A, 1 o 0
        if ((char)actual == 'D' || (char)actual == 'M' || (char)actual == 'A'||(char)actual == '1'||(char)actual == '0') {
        	buffer= (char)actual;
            actual = fgetc(soloC); // siguiente carácter
             //comprobamos que el siguietne caracter se +, -, | o &
            if ((char)actual == '+' || (char)actual == '-' || (char)actual == '|' || (char)actual == '&') {
                actual = fgetc(soloC); // siguiente carácter
                
                //comprobamos que el siguiente caracter sea A, M, D, 1 o 0
                if ((char)actual == 'A' || (char)actual == 'D' || (char)actual == 'M' || (char)actual == '1' || (char)actual == '0') {
                    actual = fgetc(soloC); // siguiente carácter
                    
                   //comprobamos que el siguiente caracter sea ; o fin de linea
                    if ((char)actual == '\n' || actual == EOF) {
                    	
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
	
	// Si comienza con D, M, A, 1 o 0
        if ((char)actual == 'D' || (char)actual == 'M' || (char)actual == 'A'||(char)actual == '1'||(char)actual == '0') {
        	
            actual = fgetc(archivo); // siguiente carácter
            
            //comprobamos que el siguiente caracter se +, -, | o &
            if ((char)actual == '+' || (char)actual == '-' || (char)actual == '|' || (char)actual == '&') {
                actual = fgetc(archivo); // siguiente carácter
                
                 //comprobamos que el siguiente caracter sea A, D, M, 1 o 0
                if ((char)actual == 'A' || (char)actual == 'D' || (char)actual == 'M' || (char)actual == '1' || (char)actual == '0') {
                    actual = fgetc(archivo); // siguiente carácter
                    
                    //vemos si es final de linea
                    if ((char)actual == '\n' || actual == EOF) {
                    	
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
            else if((char)actual == '\n'){
            	
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
int tratarVariables(const char *nombre_de_archivo) {
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
	    		fputc(char_actual, archivoEscribir); //ponemos el inicio de la etiqueta para uso posterior
	    		actual = fgetc(archivoLeer);
	    		while(actual != EOF && (char)actual != '\n'){
	    			char_actual = (char)actual;
	    			fputc(char_actual, archivoEscribir); //escribir el contenido de la etiqueta.
	    			actual = fgetc(archivoLeer);
				}				
				char_actual = '\n';
				
			}
			fputc(char_actual, archivoEscribir);
			actual = fgetc(archivoLeer);
	}
	return 0;
}
//**************************************************************

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
	
	FILE *var2 = fopen("variables.txt", "r");
	if(var2 == NULL){
		printf("No se encontro el archivo 'variables.txt'\n");
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
void encontrarVariables(FILE* archivoLeer, FILE* archivoEscribir){
	int actual = fgetc(archivoLeer);
   while(actual != EOF){
   	char char_actual = (char)actual;
   	  if(char_actual == '@'){
   	  	    fputc(char_actual, archivoEscribir);
   	  	     actual = fgetc(archivoLeer);
   	  	     char_actual = (char)actual;
   	  	    // Verifica si el carácter es una letra en mayúscula o minúscula
             if( !(char_actual >= '0' && char_actual <= '9')){
             	 while(actual != EOF && (char)actual != '\n' && (char)actual != '\0'){
             	 	fputc(char_actual, archivoEscribir);
             	 	actual = fgetc(archivoLeer);
             	 	char_actual = (char)actual;
				  }
				  if(actual == EOF){
				  	printf("Se llego a el final de el archivo\n"); //salir de la funcion
				  	fclose(archivoLeer);
				  	fclose(archivoEscribir);
				  	return;
				  }
				  fputc('\n', archivoEscribir);
			 }
		 }
		 actual = fgetc(archivoLeer);
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
   	char char_actual = (char)actual;
    sprintf(buffer, "%d", n);  // Convertir el entero 'n' a una cadena
   	  if(char_actual == '@'){
   	  	     actual = fgetc(archivoLeer);
   	  	     char_actual = (char)actual;
   	  	    // Verifica si el carácter es una letra en mayúscula o minúscula
             if( (char_actual >= 'A' && char_actual <= 'Z') || (char_actual >= 'a' && char_actual <= 'z') ){
             	fputs(buffer, archivoEscribir);//poner el valor de la variable
             	fputc(' ', archivoEscribir);//separa el nombre de la variable
             	 while(actual != EOF && (char)actual != '\n' && (char)actual != '\0'){
             	 	fputc(char_actual, archivoEscribir);
             	 	actual = fgetc(archivoLeer);
             	 	char_actual = (char)actual;
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
//**************************************************************

//**************************************************************
//-----------------------------------------------------------------
int verificarVarYEtiq(){
	FILE *txt = fopen("archivo.txt", "r");
	if(txt ==NULL){
		printf("No se encontro el archivo 'archivo.txt'\n");
		return 1;
	}
	int cantidad =cantidadDeLineas(txt);//tomamos la cantidad de lineas que tiene el archivo
	fclose(txt);
 
	if(tomarVariables("archivo.txt") != 0) return 1;
	system("cls");//limpiamos la terminal
	FILE *var = fopen("variables2.txt", "r");
	if(var == NULL){
		printf("No se encontro el archivo 'variables.txt'\n");
		return 1;
	}
	printf("Se abrio el archivo 'variables2.txt'\n");
	
	FILE *etiqe = fopen("etiquetas.txt", "r");
	if(etiqe == NULL){
		printf("No se encontro el archivo 'etiquetas.txt'\n");
		return 1;
	}
	printf("Se abrio el archivo 'etiquetas.txt'\n");
	
    char nlineaEtiq[cantidad]; //asignamos memoria para el numero de linea de las etiquetas
    char nlineaVar[cantidad];//asginamos memoria para el numero de linea de las variables
    char *cadenaVar2 = (char *)malloc(1024 * sizeof(char));//asginamos memoria dinamica para la cadena de las variables
    if(cadenaVar2 == NULL){
    	printf("ERROR a el asginar memoria para 'cadenaVar2'\n");
    	fclose(var);
    	return 1;
	}
    char *cadenaEtiq2 = (char *)malloc(1024 * sizeof(char));//asginamos memoria dinamica para la cadena de las etiquetas
	if(cadenaEtiq2 == NULL){
    	printf("ERROR a el asginar memoria para 'cadenaEtiq2'\n");
    	fclose(var);
    	return 1;
	}  
    char mostrar = 'Y';
    int actual = fgetc(var);//primer caracter
    while(actual != EOF){
    	
    	memset(nlineaVar, 0, sizeof(nlineaVar)); //resttablecer el arreglo a 0
    	memset(cadenaVar2, 0, sizeof(1024));//reestablecr el arreglo a 0
    	memset(nlineaEtiq, 0, sizeof(nlineaEtiq));//reestablecer el arreglo a 0
    	memset(cadenaEtiq2, 0, sizeof(1024));//reestablecer el arreglo a 0
    	int i = 0;
    	
    	if(actual == EOF) break;//salir de el bucle
    	//obtenemos el numero de linea de la variable
    	while((char)actual != ' '){
    		nlineaVar[i] = (char)actual;
    		i++;
    		actual = fgetc(var);
		}
		nlineaVar[i] = '\0';
		actual = fgetc(var); //caracter despues de el espacio
	   //obtenemos el nombre de la variables
	   int j= 0;
		while(actual != EOF && (char)actual != '\n'){
			cadenaVar2[j]= (char)actual;
			j++;
			actual = fgetc(var);
		}
		cadenaVar2[j]= '\0';
		rewind(etiqe);//rebobinamos el arhcivo etiqeutas.txt para volverlo a leer desde el principio
		char *c=etiq(nlineaEtiq, cadenaEtiq2, etiqe);//tomamos el numero de linea de la etiqueta y su cadena
		//entra en un bucle para comparar la cadena de la variable con cada cadena de etiqueta
		while(mostrar == 'Y' && c != NULL){
			//si la cadena es identica muestra la advertencia
			if(mostrar == 'Y' && strcmp(cadenaVar2,cadenaEtiq2) == 0){
				char escaneo;//caracter para recibir
				printf("ADVERTENCIA: en la linea de la etiqueta %s\nNOMBRE: %s\n Linea de la variable: %s\n", nlineaEtiq, cadenaEtiq2, nlineaVar);
				printf("DETALLEs: Puede haber problemas en la ejecucion si una etiqueta y una varaible tienen el mismo nombre, corrija esto\n");
				printf("MAS: La etiqueta se guardara pero la variable no, por lo que cualquier aparicion de esta sera tomada como etiqueta\n");
				printf("INGRESE SI DESEA CONTINUAR CON LA EJECUCION DE EL PROGRAMA(Y/N)\nSi selecciona Y se hara la verficacion con la siguiente variable y se terminara la de la actual\n");
				scanf(" %c", &escaneo);
				while(escaneo != 'Y' && escaneo != 'N'){
				printf("INGRESE SI DESEA CONTINUAR CON LA EJECUCION DE EL PROGRAMA(Y/N)\nSi selecciona Y se hara la verficacion con la siguiente variable y se terminara la de la actual\n");

				scanf(" %c", &escaneo);	
				}
				if(escaneo == 'Y'){
					printf("\nINGRESE SI DESEA SEGUIR VIENDO ESTOS MENSAJE(Y/N)\nSi seleccion N no volvera a ver estas advertencias y el programa continuara su ejecucion\n");
					scanf(" %c", &mostrar);
					while(mostrar != 'Y' && mostrar != 'N'){
					printf("\nINGRESE SI DESEA SEGUIR VIENDO ESTOS MENSAJE(Y/N)\nSi seleccion N no volvera a ver estas advertencias y el programa continuara su ejecucion\n");
					scanf(" %c", &mostrar);
					}
					if(mostrar == 'N'){
						printf("\nESPERE...\n");
					}
					break;
				}
				else{
					printf("Se detuvo la ejecucion de el programa\n");
					fclose(var);
					return 1;
				}
				
			}
			memset(cadenaEtiq2, 0, sizeof(1024));//limpiamos la cadena de etiqueta
		  c=etiq(nlineaEtiq,cadenaEtiq2, etiqe);//tomamos la cadena de la linea siguiente a la anterior y su numero de liena de la etiqueta
		}
		//cuando haya comparado la variable con todas las etiquetas va a la siguietn varaible para hacer lo mismo
		actual = fgetc(var);
	}
	//cuando ya se comparo todas las variables
	fclose(var);
	free(cadenaEtiq2);
	free(cadenaVar2);
	//eliminamos el archivo temporal variables2.txt
	if(remove("variables2.txt") != 0){
	  printf("No se elimino el archivo 'variables2.txt'\n");
	  return 1;
	}
	return 0;
    
}
//-----------------------------------------------------------------
char *etiq(char* poner_nlinea, char *cadena, FILE *etiq){
	int actual;
	while(1){
		actual = fgetc(etiq); //primer carater
		if(actual == EOF) return NULL;
		//obtener el numero de linea
		while((char)actual != ' '){
			*poner_nlinea = (char)actual;
			poner_nlinea++;
			actual = fgetc(etiq);
		}
		*poner_nlinea = '\0';//teriminar correctamente la cadena
		actual = fgetc(etiq); //caracter despues de el espacio
		int i = 0;
		//obtener la cadena
		while((char)actual != '\n' && actual != EOF){
			*cadena= (char)actual;
			cadena++;
			actual = fgetc(etiq);
		}
		*cadena= '\0';
		if((char)actual == '\n' || (char)actual == '\0' ||(char)actual == ' ') break; //si es fin de linea o de cadena o esapcio salir
	}
	return cadena;
	
}
//-----------------------------------------------------------------
int tomarVariables(const char* archivo) {
    // Abrimos el archivo de entrada
    FILE *archivoP = fopen(archivo, "r");
    if (archivoP == NULL) {
        printf("No se encontro el archivo '%s'\n", archivo);
        return 1;
    }

    // Abrimos el archivo de salida
    FILE *var2 = fopen("variables2.txt", "w");
    if (var2 == NULL) {
        printf("ERROR al crear el archivo 'variables2.txt'\n");
        fclose(archivoP); // Cerrar el archivo de entrada en caso de error
        return 1;
    }

    char linea[1024]; // Buffer para leer cada línea
    while (fgets(linea, sizeof(linea), archivoP) != NULL) {
        // Buscar el primer espacio en la línea
        char *ptrEspacio = strchr(linea, ' '); // Encontramos el primer espacio
        if (ptrEspacio != NULL) {
            // Verificamos que el siguiente carácter sea un '@'
            if (*(ptrEspacio + 1) == '@') {
                // Verificamos que el siguiente carácter después del '@' no sea un número
                if (*(ptrEspacio + 2) != '\0' && !isdigit((unsigned char)(*(ptrEspacio + 2)))) {
                    // Copiamos toda la línea al archivo var2
                    fprintf(var2, "%s", linea);
                }
            }
        }
    }
    // Cerramos los archivos
    fclose(archivoP);
    fclose(var2);
    //reabrimo variables2.txt para editarlo
    FILE *var3 = fopen("variables2.txt", "r");
    if(var3 == NULL){
    	printf("No se encontro el archivo 'variables2.txt'\n");
    	return 1;
	}
	printf("Se abrio el archivo 'variables2.txt'\n");
	//creamos un archivo temporal
	FILE *temp = fopen("tempvar6.txt", "w");
	if(temp ==NULL){
		printf("ERROR a el crear el archivo 'tempvar6.txt'\n");
		fclose(var3);
		return 1;
	}
	printf("Se creo el archivo 'tempvar6.txt'\n");
	int actual;
	//entra en un bucle
	while(1){
		actual = fgetc(var3);//primer caracter
		if(actual == EOF) break;//si es EOF salir de el bucle
		//tomar el numero de linea
		while((char)actual != ' '){
			fputc((char)actual, temp);
			actual = fgetc(var3);
		}
		fputc((char)actual, temp);//agregamos tambien el espacio
		actual = fgetc(var3);//pasamos a el siguietne caracter
		if((char)actual == '@') actual = fgetc(var3); //pasamos a el siguiente caracter despues de @ (ignoramos @)
		while((char)actual != '\n' && actual != EOF){
			fputc((char)actual, temp);
			actual = fgetc(var3);
		}
		if(actual == EOF) break;
		fputc('\n', temp);//agregar fin de linea
		
	}
	fclose(temp);
	fclose(var3);
	if(remove("variables2.txt")!= 0){
		printf("No se elimino el archivo 'variables2.txt'\n");
		return 1;
	}
	else{
		if(rename("tempvar6.txt", "variables2.txt") != 0){
			printf("No se pudo renombrar el archivo 'tempvar6.txt' a: 'variables2.txt'\n");
			return 1;
		}
		printf("Se renombro el arhcivo 'tempvar6.txt' a: 'variables2.txt'\n");
	}
    return 0;
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

void instruccionesA (const char* archivo){
	
}
