#ifndef PR1_H_INCLUDED
#define PR1_H_INCLUDED

#include <vector>
#include <iostream>


class Pr1
{
  private:
    long int seed=1;
    int tam =-1;
    int steps;
    std::vector< std::string > problemas={"./src/data/Instancias_QAP/chr22a.dat","./src/data/Instancias_QAP/chr22b.dat","./src/data/Instancias_QAP/chr25a.dat","./src/data/Instancias_QAP/esc128.dat","./src/data/Instancias_QAP/had20.dat","./src/data/Instancias_QAP/lipa60b.dat","./src/data/Instancias_QAP/lipa80b.dat","./src/data/Instancias_QAP/nug28.dat","./src/data/Instancias_QAP/sko81.dat","./src/data/Instancias_QAP/sko90.dat","./src/data/Instancias_QAP/sko100a.dat","./src/data/Instancias_QAP/sko100f.dat","./src/data/Instancias_QAP/tai100a.dat","./src/data/Instancias_QAP/tai100b.dat","./src/data/Instancias_QAP/tai150b.dat","./src/data/Instancias_QAP/tai256c.dat","./src/data/Instancias_QAP/tho40.dat","./src/data/Instancias_QAP/tho150.dat","./src/data/Instancias_QAP/wil50.dat","./src/data/Instancias_QAP/wil100.dat"};

    std::vector< std::pair <float,int> > vectorflujos;
    std::vector< std::pair <float,int> > vectorcostes;
    float **matrizflujo;
    float **matrizcoste;
    std::vector< std::pair <float,int> > vectsolucionflujo;
    std::vector< std::pair <float,int> > vectsolucioncostes;
    bool improve_flags;
    void leefichero();
    float Factoriza(int r,int s,std::vector< int>v);
    std::vector<int> MejorVecino(std::vector< int>v);
    std::vector<int> mascara;
    std::string Permutastring(std::vector<int>v);
    float Coste(std::vector< int>v);
    std::vector<int> Perturbacion(std::vector< int>v);
    int z;
  public :
    Pr1();

    void CalculaGreedy();
    void CalculaBusquedaLocal();
  };


#endif
