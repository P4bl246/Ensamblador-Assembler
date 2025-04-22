#include <stdio.h>
#include "ensamblando.h"
int main(){
	int r;
	//convertimos el archivo .asm a .txt para poder tratarlo
	r = ArchivoA_txt("archivo.asm");
	if(r != 0){
		printf("ERROR en la funcion 'ArchivoA_txt'\n");
		return 1;
	}
	//primero verficamos la sintaxist
 	r = analisis_sintactico("archivo.txt");
	if(r != 0){
		printf("ERROR en la funcion 'analisis_sintactio'\n");
		return 1;
	}
	
	//limpiamos el archivo .txt 
	r=limpiarLineas("archivo.txt");
	if(r != 0){
		printf("ERROR en la funcion 'limpiarLineas'\n");
		return 1;
	}
	
	//creamos la tabla de simbolos predeterminada y lo guardamos en 'tabla.txt'
	r = tablaDeSimbolos();
	if(r != 0){
		printf("ERROR en la funcion 'tablaDeSimbolos'\n");
		return 1;
	}
	
	//organizamos las etiquetas en el archivo.txt
	r = tratarEtiquetas("archivo.txt");
	if(r != 0){
		printf("ERROR en la funcion 'tratarEtiquetas'\n");
		return 1;
	}
	
	//organizamos las variables y instrucciones @ en el archivo.txt
	r = tratarVariables("archivo.txt");
	if(r != 0){
		printf("ERROR en la funcion 'tratarVariables'\n");
		return 1;
	}
	
	//numeramos las lineas
	r = numerarLineas("archivo.txt");
	if(r != 0){
		printf("ERROR en la funcion 'numerarLineas'\n");
		return 1;
	}
	
	//extraemos las etiquetas para tratarlas
	r = separarEtiquetas("archivo.txt");
	if(r != 0){
		printf("ERROR en la funcion 'separarEtiquetas'\n");
		return 1;
	}
	
	//agruegamos mas simbolos si hay en 'tabla.txt'
	r = mas_simbolos("etiquetas.txt");
	if(r != 0){
		printf("ERROR en la funcion 'mas_simbolos'\n");
		return 1;
	}
	
	//identificamos las variables y las separamos para tratarlas(incluye mas_simbolos)
	r = separarVariables("archivo.txt");
	if(r != 0){
		printf("ERROR en la funcion 'separarVariables'\n");
		return 1;
	}
	
	//limpiamos la tabla de posibles duplicados o problemas de variables y etiquetas con el mismo nombre dejando las etiquetas
	r = limpiar_tabla();
	if(r != 0){
		printf("ERROR en la funcion 'limpiar_tabla'\n");
		return 1;
	}
	
	system("cls");//limpiamos la terminal
	//limpiamos el archivo txt principal de las etiquetas
    r = limpiartxtPr("archivo.txt");
	if(r != 0){
		printf("ERROR en la funcino 'limpiartxtPr'\n");
		return 1;
	}	
	
//---------------------------------------------------------------------------

	
    	
	
	
	return 0;
}
