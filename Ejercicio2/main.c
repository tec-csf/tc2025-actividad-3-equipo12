/*Programa realizado por Rafael Medina y Edgar Garcia y un compañero graduado
Link den ayuda del video con programa:
Escriba un programa en C que parta de un directorio dado y descienda por el árbol de archivos registrando 
los tamaños de todos los archivos que encuentre. Cuando termine, deberá imprimir un histograma de los 
tamaños de archivo, utilizando una anchura de urna especificada como parámetro ( por ejemplo, para un 
valor de urna de 1024, todos los archivos con tamaño entre 0 y 1023 se colocan en una urna, los de 1024 
a 2047 en otra y así sucesivamente).

Debe utilizar llamadas al sistema (system calls). Por favor, verifique las llamadas al sistema para 
manipulación de archivos y directorios que a aparecen en la última clase.

Ejemplo de visualización del histograma:

Urna	Número de archivos	Histograma
0-1023	20	********************
1024-2047	15	**************
2048-3071	35	*****************************
3072-4095	40	**************************************
Sugerencia: Para determinar la cantidad de * a imprimir, defina una relación 
respecto al número máximo de archivos obtenido. Por ejemplo, si el número máximo de archivos 
obtenido es 1000, entonces divida la cantidad entre 100. De esta manera, para la cantidad máxima 
imprimirá 10 * y todos los demás estarán acotados por debajo de este máximo.
*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
//arbol de archivos
/**
 *conteo de archivos
 *@param archivos
 *recorrido del programa
 *@param path
 *histograma
 *@param sizeArca
 * 
 **/ 
int ordenamientoClasi(int*, char*, int, int*);
void muestraInfo(int*, int);

int listadoOS = 25000; 
int mayorPresencia = 0; 

int main()
{
    DIR *dir; 
    int* longitudDoc;
    char* nombre; 
    int magnitudOS; 
    int *maximo;
    maximo = (int*)malloc(1 * sizeof(int));
    nombre = (char*)malloc(512 * sizeof(char));
    printf("Introduzca el path de donde quiere empezar el recorrido.\n");
    scanf(" %[^\n]", nombre);
    dir = opendir(nombre);
    //Revision de path correcto o eitente
    if (dir==NULL) {
        printf("Path invalido intentelo de nuevo\n");
        closedir(dir);
        return 1;
    }
    do{
        printf("Introduzca el tamaño de Bytes.\n");
        scanf(" %d", &magnitudOS);
    }while(magnitudOS<=0);

    longitudDoc = (int*)malloc(listadoOS * sizeof(int));
    int* aux;
    aux = longitudDoc;
    for(; aux<(longitudDoc + listadoOS); aux++){
        *aux = 0;
    }
    listadoOS = ordenamientoClasi(longitudDoc, nombre, magnitudOS, maximo); 
    if(listadoOS<=0) {
        listadoOS = ((*maximo)/magnitudOS) + 1;
    }
    
    longitudDoc = realloc(longitudDoc, listadoOS * sizeof(int));
    //Muestra histograma
    muestraInfo(longitudDoc, magnitudOS); 

    //Liberacion 
    free(longitudDoc); 
    free(nombre); 
    free(maximo);
    closedir(dir); 
    return 0;
}

int ordenamientoClasi(int* archivos, char* path, int sizeArca, int* maximo)
{
    DIR* directorio;
    struct dirent* inicio; 
    struct stat informacion; 
    directorio = opendir(path);
    int ultimaArca = 0;
    while((inicio = readdir(directorio))){
        int* aux;
        aux = archivos;
        char* nomreCompleto;
        nomreCompleto = (char*)malloc(512 * sizeof(char));

        sprintf(nomreCompleto, "%s/%s", path, inicio->d_name);
        stat(nomreCompleto, &informacion); 
        if(S_ISDIR(informacion.st_mode)){
            if (strcmp(inicio->d_name, ".") != 0 && strcmp(inicio->d_name, "..") != 0 ){
                ordenamientoClasi(archivos, nomreCompleto, sizeArca, maximo);
            }
        }
        else if(S_ISREG(informacion.st_mode)){
            int i = 1;
            int count = 0;
            for(; aux<(archivos + (listadoOS)); aux++) {
                if(informacion.st_size < ((sizeArca * i) - 1)){
                    if(informacion.st_size>*maximo){
                        *(maximo) = informacion.st_size;
                    }
                    *aux = *aux + 1;
                    *(archivos + (i-1)) = *aux;
                    if(*aux>mayorPresencia) {
                        mayorPresencia = *aux; 
                    }
                    if(ultimaArca < i) {
                        ultimaArca = i;
                    }
                    count = 1;
                    break;
                }
                i++;
            }
            //Problemas con el tamaño que no es valido
            if(count==0)
            {
                printf("El archivo presenta algunos inconvenietes\n");
            }
        }
        free(nomreCompleto);
    }
    closedir(directorio);
    return ultimaArca;
}
/*Impresion de datos
Urna	Número de archivos	Histograma
    0-1023	    20	********************
    1024-2047	15	**************
    2048-3071	35	*****************************
    3072-4095	40	**************************************
*/
void muestraInfo(int* arreglo, int magnitudOS)
{
    int* aux = arreglo;
    int i = 1;
    
    printf("%17s %20s %13s\n", "Urna Inferior"       "Urna Superior",     "Num. Archivos",     "Histograma");
    for(; aux<(arreglo + listadoOS); aux++){
        int impresionAsterisco = *aux;
        //Impresion del formato deseado 
        printf("%9d  %9d   %15d ", (i-1) * magnitudOS, (i * magnitudOS) -1, *aux);
        if((mayorPresencia)>100){
            impresionAsterisco = (*aux)/10;  
        }
        for (int count = 0; count < impresionAsterisco; count++){
            printf("*");
        }
        printf("\n");
        i++;
    }
}