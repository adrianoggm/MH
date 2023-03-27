
#include "pr1.h"
#include <iostream>


int main(){

  printf("Programa e Interfaz de prácticas MH de Adriano García-Giralda Milena:: \n");

  printf("Ahora le pasamos el siguiente MENÚ para decidir la práctica a ejecutar: \n");
  printf("Elija el número de práctica deseado  \n");
  printf("-.1 Técnicas de Búsqueda Local y Algoritmos Greedy para el Problema de la Asignación Cuadrática. \n");
  printf("-.2 Por implementar. \n");
  printf("-.3 Por implementar. \n");

  int i=0;
  std::cin>>i;

  while(i<1 && i>3){
  printf("Recuerde un número del 1-3 para elegir la práctica  \n");
    std::cin>>i;
  }

  while(i>1){
  printf("Disculpe las molestias la práctica aún no está implementada le recomiendo pulsar 1 para ejecutar la que si lo está \n");
    std::cin>>i;
  }

  if(i==1){
    printf("Ha elegido la práctica 1 Técnicas de Búsqueda Local y Algoritmos Greedy para el Problema de la Asignación Cuadrática. \n");
    //ejecutamos pr1
    Pr1 p1;

    p1.CalculaGreedy();
    p1.CalculaBusquedaLocal();
  }

}
