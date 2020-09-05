/*
Ejercicio 1 Planificación por Pandilla 
Equipo 12 
Rafael Díaz Medina A01024592
Edgar García
*/
#include<stdio.h>
#include<stdlib.h>
#include <unistd.h>
int quantum=3;

typedef struct{
      int namePandilla;
      int idPandilla;
      int numPandilleros;
      int idPandillero;
      int robTime;
}Pandilla;

//void cpuRR(Pandilla * gang, int cores, int maxPandillas);
void RoundRobin(Pandilla * gang, int , int );

int main(int argc, const char * argv[]){
      int maxPandillas;
      int cores;
      int timeRob;
      int maxRob;

      printf("\nCuantos CPU´S: ");
      scanf("%d", &cores);
      printf("\nCuantas pandillas hay: ");
      scanf("%d", &maxPandillas);
      char c;
      Pandilla * gang;
      gang = (Pandilla*)malloc(maxPandillas* sizeof(Pandilla));
      
      for(int i=0, c ='A'; i<maxPandillas; i++, c++){
            
            (gang+i)->namePandilla=c;
            (gang+i)->idPandilla=i;
            printf("\nCuantos pandilleros tiene la pandilla %c: ", (gang+i)->namePandilla);
            scanf("%d", &(gang+i)->numPandilleros);
            printf("\nTiempo de robo de la pandilla %c: ", c);
            scanf("%d", &(gang+i)->robTime);

      }

      for (int s = 0; s < maxPandillas; s++){
            printf("\nId Pandilla %d ", (gang+s)->idPandilla);
            printf("\n numero pandilleros %d ",(gang+s)->numPandilleros);
                  
            printf("\n id Pandillero %d", (gang+s)->idPandillero);
            printf("\n tiempo %d \n", (gang+s)->robTime);  
      }    

      RoundRobin(gang, maxPandillas, cores);  

      free(gang);
      gang=NULL;
      return 0;
}
void RoundRobin(Pandilla * gang, int maxPandillas , int cores){
      int result=0;
      int  auxTime;
      int auxDos=0;
	  int ronda=0;
      
      while(result!=1){
            for(int i=0; i<maxPandillas; i++){
                  if((gang+i)->robTime>0){
                        auxTime=(gang+i)->robTime;
                        auxTime-=quantum;      
                        (gang+i)->robTime=auxTime;
                        for (int s = 0; s < cores; s++){
                              //for(int l=0; l<(gang+i)->numPandilleros; l++){
                              printf("Pandilla %c pandillero id %d  tiempo restante %d\n",(gang+i)->namePandilla, (gang+i)->idPandillero=s, (gang+i)->robTime);
                              //}
                        }
						ronda++;
						printf("\nRonda de Quantum %d\n", ronda);
                  }
                  else if((gang+i)->robTime<=0){
                        if((gang+i+1)->robTime<=0){
                              auxDos++;
                              //printf("\nEntre a Auxdos\n");
                        }
                        if(auxDos==maxPandillas){
                              result=1;
                        }
                  }
                  else{
                        i=0;
                  }
                  
            }
      }
}

