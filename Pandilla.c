/*
Realice un programa en C donde simule el comportamiento del algoritmo de planificación por pandilla.
 El programa debe permitir al usuario entrar por teclado el número total de procesos a planificar, 
 el tiempo de CPU que se requiere para cada uno, la relación que existe entre los procesos (grupos) 
 y el número de CPUs. Los grupos de procesos deben ir planificándose según el criterio que Ud. 
 defina (puede ser Round Robin, FIFO, etc.), garantizando siempre un máximo aprovechamiento de todas las CPUs.
1- Hacer un Round Robin
2- Simular multiples Cores de procesamiento, las unidades de procesamiento son de tamaño N
3- Obtener el numero de gang que entraran y a cada una asignarle un ID, justo como en el ejemplo pandilla A= A0-A5
4- Solo existe un Round Robin, y ese Round Robin debe de correr todas las gang por que cada pandilla debe de tener 
cierto tiempo de asignación en la CPU.
6- Todos los CPU'S inician al mismo tiempo
7- Los procesos los voy a añadir conforme vayan llegando directo al round robin, si la pandiila es más grande que el timepo de quantum
la meto en el sedundo tiempo de quantum, así hasta poder meter al segundo proceso, lo que se debe de tratar de hacer es tener la mayor
cantidad de pandilleros de una pandilla dentro de un mismo tiempo de quantum.
8- Contar el tiempo de el ultimo pandillero=0 si es mayor se que esa pandilla aun debe de correr
Verificar el tamaño de la pandilla y si la pandilla 
verificar cada uno de los pandilleros para ver si ya pasaron
deben de pasar en orden de 0 a n 
Listo
Round Robin
Pandilla
*/
#include<stdio.h>
#include<stdlib.h>
#include <unistd.h>
int quantum=3;


//Función Round Robin


typedef struct{
      int namePandilla;
      int idPandilla;
      int numPandilleros;
      int idPandillero;
      int robTime;
}Pandilla;

void cpuRR(Pandilla * gang, int cores, int maxPandillas);
void RoundRobin(Pandilla* gang, int maxPandillas);

int main(int argc, const char * argv[]){
      int maxPandillas;
      int cores;
      int timeRob;
      int maxRob;

      printf("\nCuantos CPU´S: ");
      scanf("%d", &cores);
      printf("\nCuantas pandillas hay: ");
      scanf("%d", &maxPandillas);
      /*lo de abajo debe de ir dentro de un for para preguntarlo por cada pandilla
      y le debo de agregar el id de la pandilla que asignare
      Para imprimir de la A a la Z
      */
      char c;
      Pandilla * gang;
      gang = (Pandilla*)malloc(maxPandillas* sizeof(Pandilla));
      
      for(int i=0, c ='A'; i<maxPandillas; i++, c++){
            //(gang+i)->namePandilla = (char*)malloc(2);
            //(gang+i)->namePandilla= (char*)malloc(c);
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
                  /*for ( int l = 0; l <(gang+s)->numPandilleros; l++){
                        (gang+s)->namePandilla=(gang+s)->namePandilla;
                        (gang+s)->idPandilla=(gang+s)->idPandilla;
                        (gang+l)->idPandillero=l;
                        (gang+s)->numPandilleros=(gang+s)->numPandilleros;
                        (gang+s)->robTime=(gang+s)->robTime;
                  }*/
            printf("\n id Pandillero %d", (gang+s)->idPandillero);
            printf("\n tiempo %d \n", (gang+s)->robTime);  
      }

      int result=0;
      int  auxTime;
      int auxDos=0;
      
      while(result!=1){
            for(int i=0; i<maxPandillas; i++){
                  if((gang+i)->robTime>0){
                        auxTime=(gang+i)->robTime;
                        auxTime-=quantum;      
                        (gang+i)->robTime=auxTime;
                        for (int s = 0; s < cores; s++)
                        {
                              //for(int l=0; l<(gang+i)->numPandilleros; l++){
                              printf("Pandilla %c pandillero id %d  tiempo restante %d\n",(gang+i)->namePandilla, (gang+i)->idPandillero=s, (gang+i)->robTime);
                              //}
                        }
                  }
                  else if((gang+i)->robTime<=0){
                        auxDos++;
                        if(auxDos==maxPandillas){
                        result=1;
                  }
                  }
                  /*for(int s=0; s<cores; s++){
                        if((gang+i)->robTime<=0){
                        auxDos++;
                        }
                        else{
                        auxTime=(gang+i)->robTime;
                        auxTime-=quantum;      
                        (gang+i)->robTime=auxTime;
                  
                        printf("Este es el tiempo de robo que le queda a la pandilla id %d  tiempo %d\n", (gang+i)->idPandilla, (gang+i)->robTime);
                        }
                  }*/
                  else
                  {
                        i=0;
                  }
                  
            }
      }      

      free(gang);
      gang=NULL;
      return 0;
}


/*void cpuRR(Pandilla * gang, int cores, int maxPandillas){
      int fin=0;
      while (fin!=1)
      {

            

            
      }
      


}*/

/*void RoundRobin(Pandilla* gang, int maxPandillas){
      int tQuantum=4;
      int total = 0; 
      int x; 
      int counter = 0;
      int wTime = 0;
      int taTime = 0;
      int arTime[10];
      int bsTime[10];
      int temp[10];
      int i=0;
      x = maxPandillas;
      
      for(i = 0; i < maxPandillas; i++){
 
            temp[i] = bsTime[i];
      }
 
      /*printf("\nTiempo Quantum\t");
      scanf("%d", &qTime);
      for(total = 0, i = 0; x != 0;){
            if(temp[i] <= qTime && temp[i] > 0)
            {
                  total = total + temp[i];
                  temp[i] = 0;
                  counter = 1;
            }
            else if(temp[i] > 0)
            {
                  temp[i] = temp[i] - qTime;
                  total = total + qTime;
            }
            if(temp[i] == 0 && counter == 1)
            {
                  x--;
                  printf("\nProcess %d    %d       %d      %d", i + 1, bsTime[i], total - arTime[i], total - arTime[i] - bsTime[i]);
                  wTime = wTime + total - arTime[i] - bsTime[i];
                  taTime = taTime + total - arTime[i];
                  counter = 0;
            }
            if(i == maxPandillas - 1)
            {
                  i = 0;
            }
            else if(arTime[i + 1] <= total)
            {
                  i++;
            }
            else
            {
                  i = 0;
            }
      }
}*/