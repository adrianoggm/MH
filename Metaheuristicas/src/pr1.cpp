
#include "pr1.h"
#include "iostream"
#include "fstream"
#include <bits/stdc++.h>
#include "random.hpp"






bool sort_pred_func(const std::pair<float,int> &l,const std::pair<float,int> &r){
  return l.first<r.first;
}


using Random = effolkronium::random_static;
//Constructor del obj Pr1
Pr1::Pr1()
{
  //Crea de acuerdo al fichero de entrada los datos de las matrices de flujo y coste
  leefichero();
  seed=196917;//va a ser una semilla que vamos a elegir a consciencia para llevar el ejercicio

}

void Pr1::leefichero(){
  printf("Ahora le pasamos el siguiente MENÚ para decidir que archivo le gustaría ejecutar : \n");
  printf("Elija el número del archivo deseado  \n");
  printf("-0. chr22a  \n");
  printf("-1. chr22b  \n");
  printf("-2. chr25a  \n");
  printf("-3. esc128  \n");
  printf("-4. had20  \n");
  printf("-5. lipa60b \n");
  printf("-6. lipa80b \n");
  printf("-7. nug28 \n");
  printf("-8. sko81 \n");
  printf("-9. sko90 \n");
  printf("-10. sko100a \n");
  printf("-11. sko100f \n");
  printf("-12. tai100a \n");
  printf("-13. tai100b \n");
  printf("-14. tai150b \n");
  printf("-15. tai256c \n");
  printf("-16. tho40 \n");
  printf("-17. tho150 \n");
  printf("-18. wil50 \n");
  printf("-19. wil100 \n");
  int i=0;
  std::cin>>i;
  while(i<0 && i>19){
  printf("Recuerde un número del 0-19 para elegir el problema a estudiar  \n");
    std::cin>>i;
  }

  //problemas={"chr22a","chr22b","chr25a","esc128","had20","lipa60b","lipa80b","/nug28","ww/sko81","ww/sko90","ww/sko100a","ww/sko100f","ww/tai100a","ww/tai100b","ww/tai150b","ww/tai256c","ww/tho40","ww/tho150","ww/wil50","ww/wil100"};
  std::string problema=problemas[i];

  std::ifstream infile;
  infile.open(problema);

  if(!infile){
    printf("NO EXISTE DICHO ARCHIVO,revisalo loquete \n");
    std::cout<<problema;
  }
  infile>>tam;
  printf("Tamaño %d \n",tam);
  matrizflujo= new float*[tam];
  matrizcoste= new float*[tam];
  //Aqui voy generando y inicializando las matrices
  for(int j=0;j<tam;j++){
    matrizflujo[j]=new float[tam];
    matrizcoste[j]=new float[tam];
  }

  for(int j=0;j<tam;j++){
    for(int k=0;k<tam;k++){
      float a;
      infile>>a;
      matrizflujo[j][k]=a;
    }
  }
  for(int j=0;j<tam;j++){
    for(int k=0;k<tam;k++){
      float a;
      infile>>a;

      matrizcoste[j][k]=a;
    }

  }
  infile.close();

}
void Pr1::CalculaGreedy(){
  /*Luego para calcular el problema cogeremos una permutación de las soluciones
  //es decir :
  //si n = 6

    0 1 2 3 4 5  i _ _ _
   |4|2|1|5|0|3| j
  donde las i son las localidades y las j las actividades
  */

  //Para calcular el vector de flujos
  //Se hace la sumatoria de ya sea en filas o columnas y se van guardando en el vector

float suma =0;
  for(int i=0;i<tam;i++){
    suma =0;
    for(int j=0;j<tam;j++){
      suma+=matrizflujo[i][j];
    }
    vectorflujos.push_back(std::make_pair(suma,i));
  }
  //idem con el de costes
  for(int i=0;i<tam;i++){
     suma =0;
    for(int j=0;j<tam;j++){
      suma+=matrizcoste[i][j];
    }
    vectorcostes.push_back(std::make_pair(suma,i));
  }
  /*

   ahora tenemos varias soluciones ordenamos ambos vectores
  //flujo de mayor a menor
  //costes de menor a mayor
  //en guarda pos tendremos sus posiciones originales de cada 1 pero con mismo orden
  de tal manera que luego podremos obtener la solucion de forma sencilla y en formato
  0 1 2 3 4 5  i _ _ _
   |4|2|1|5|0|3| j
   a la que tamb le calcularemos sus coste asociado.
   */


   vectsolucionflujo=vectorflujos;
   vectsolucioncostes=vectorcostes;

   std::sort(vectsolucionflujo.rbegin(), vectsolucionflujo.rend(),sort_pred_func);

   std::sort(vectsolucioncostes.begin(), vectsolucioncostes.end(),sort_pred_func);

   float value=0;
   std::vector< int>v(tam);

   for(int i=0;i<tam;i++){
     int j=vectsolucionflujo[i].second;
     v[j]=vectsolucioncostes[i].second;
     //+=vectsolucioncostes[i].first;//vectsolucionflujo[i].first*vectsolucioncostes[i].first
   }

   /*
      Función que calcula el coste de la forma  fi,j d l,k
      donde i y l son localidad y ubicación respectivamente
      y lo mismo para l k . l k serán aquellos elementos != a i y
      l de forma que se obtienen los costes exceptuandose a ellos mismos

   */
  for(int i=0;i<tam;i++){
      int l=v[i];
    for(int j=0;j<tam;j++){
      if(j!=i){
        int k=v[j];
        value+=matrizflujo[i][j]*matrizcoste[l][k];
      }
    }

  }
   //coste =
   printf("Luego el resultado de Greedy es la siguiente permutación: \n");
   for(int i=0;i<tam;i++){
     printf("%d,",v[i]+1);//+1 para comprobar con el formato de la web https://mh2223.danimolina.net/testsol.html
   }
   printf(" \n");
   printf("Con el siguiente coste :%f \n",value);

}

void Pr1::CalculaBusquedaLocal(){

  /*
    Para la búsqueda local partiremos de una solución anterior
    a la cual le aplicaremos permurtaciones es decir buscaremos un mejor vecino
    que este mismo el cual mejore la función de minimización del Fitness.

    Para ello buscaremos en el vecindario si no mejoramos
  */

  // el cual es de partida una buena sol.
  //si no pasaría nada por empezar por cualquier permutación válida.
  printf("Estamos en BL \n");
  printf("Para la semilla ponga un valor >= 0 el valor con el que se ha estudiado es el 196917 por si quiere replicarlo \n");
  std::cin>>seed;
  while(seed<0){
  printf("Para la semilla ponga un valor >= 0 el valor con el que se ha estudiado es el 196917 por si quiere replicarlo \n");
    std::cin>>seed;
  }

   Random::seed(seed);//fijamos semilla en este caso 196917
   std::vector< int>v(tam);
   for(int i=0;i<tam;i++){
     v[i]=i;
   }
   Random::shuffle(v);
   for(int i=0;i<tam;i++){
     printf("%d,",v[i]+1);//+1 para comprobar con el formato de la web https://mh2223.danimolina.net/testsol.html
   }
   //para chr22a y chr22b 15,4,11,19,21,13,6,12,5,20,22,17,3,9,7,8,14,1,16,2,18,10

   //CALCULAMOS SU COSTE Y EMPEZAMOS A BUSCAR

   /*
      Función que calcula el coste de la forma  fi,j d l,k
      donde i y l son localidad y ubicación respectivamente
      y lo mismo para l k . l k serán aquellos elementos != a i y
      l de forma que se obtienen los costes exceptuandose a ellos mismos

   */
  float value=0;
  for(int i=0;i<tam;i++){
      int l=v[i];
    for(int j=0;j<tam;j++){
      if(j!=i){
        int k=v[j];
        value+=matrizflujo[i][j]*matrizcoste[l][k];
      }
    }

  }
  printf(" \n");
  printf("Con el siguiente coste inicial:%f \n",value);

  //partiendo de esta permutación procedemos a buscar...
  //PARA LA BUSQUEDA USAMOS UN VECTOR DONT Loock
  //Partimos de un vector booleano de 0 y 1
  //al principio todo a false.
  //elegimos un aleatoriamente  2 elementos de la permutación para

//Genera mejor permutacion
  for(int i=0;i<tam;i++){
    mascara.push_back(0);
  }

  int steps=0;
  improve_flags=true;
  while(improve_flags==true && steps<50000){
      improve_flags=false;
      v=MejorVecino(v);

      steps++;

  }
    printf("PERMUTACIÓN BL \n");
  for(int i=0;i<tam;i++){
    printf("%d,",v[i]+1);//+1 para comprobar con el formato de la web https://mh2223.danimolina.net/testsol.html
  }

  value=Coste(v);
  printf(" \n");
  printf("Con el siguiente coste final:%f \n",value);
}

/*Factoriza las permutaciones y devuelve la diferencia*/
float Pr1::Factoriza(int r,int s,std::vector< int>v){
  float fact=0;
    for(int k=0;k<tam;k++){
    if(k!=r&&k!=s){
    fact+=(matrizflujo[r][k]*( matrizcoste[v[s]][v[k]]-matrizcoste[v[r]][v[k]])+
    matrizflujo[s][k]*( matrizcoste[v[r]][v[k]]-matrizcoste[v[s]][v[k]])+
    matrizflujo[k][r]*( matrizcoste[v[k]][v[s]]-matrizcoste[v[k]][v[r]]) +
    matrizflujo[k][s]*( matrizcoste[v[k]][v[r]]-matrizcoste[v[k]][v[s]]));
    }
  }
  return fact;
}





/*
  Busca localmente el mejor vesino

*/

/*
std::vector<int> Pr1::MejorVecino(std::vector< int>v){
  improve_flags=false;//igual lo hago dato de la clase:
  std::vector< int>permuta=v;
  for(int i=0;i<tam;i++){
    if(mascara[i]==0){
    improve_flags=false;
    for(int j=0;j<tam;j++){
      float factorizar=Factoriza(i,j,v);
      if(factorizar<0){
        permuta=v;
        int t=permuta[i];
        permuta[i]=permuta[j];
        permuta[j]=t;
        mascara[i]=0;
        mascara[j]=0;
        improve_flags=true;
        return permuta;
    }
      mascara[i]=1;
    }

  }
  }
  return permuta;
}
*/
std::vector<int> Pr1::MejorVecino(std::vector< int>v){
  improve_flags=false;//igual lo hago dato de la clase:
  std::vector< int>permuta=v;
  for(int i=0;i<tam;i++){
    mascara[i]=0;
  }
  for(int i=0;i<tam;i++){
    if(mascara[i]==0){
    improve_flags=false;
    for(int j=0;j<tam;j++){
      float factorizar=Factoriza(i,j,v);
      if(factorizar<0){
        permuta=v;
        int t=permuta[i];
        permuta[i]=permuta[j];
        permuta[j]=t;
        mascara[i]=0;
        mascara[j]=0;
        improve_flags=true;
        return permuta;
    }
      mascara[i]=1;
    }

  }
  }
  return permuta;
}

float Pr1::Coste(std::vector< int>v){
  float value=0;
  for(int i=0;i<tam;i++){
      int l=v[i];
    for(int j=0;j<tam;j++){
      if(j!=i){
        int k=v[j];
        value+=matrizflujo[i][j]*matrizcoste[l][k];
      }
    }

  }
  return value;
}
