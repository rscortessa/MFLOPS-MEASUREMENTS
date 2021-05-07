#include "Multiplicaciones.h"    //Se enlaza el código Multiplicaciones.cpp a su correspondiente librería Multiplicaciones.h
#include <armadillo>    //Se incluye la librería armadillo
#include <vector>       //Se incluye la librería vector, ya que esta se usará para la creación de matrices
#include <Eigen/Dense>  //Se incluye la librería de Eigen
#include <cmath>        //Se incluye la librería cmath para realizar operaciones entre matrices

void multiplicacion_eigen(const Eigen::MatrixXd & A, const Eigen::MatrixXd & B, Eigen::MatrixXd & C)     //Se define la multiplicación usando Eigen
{
    C=A*B;
}
void multiplicacion_directa(const std::vector<double> & A,const std::vector<double> & B,std::vector<double> & C)    //Se define la multiplicación directa de matrices
{
    int N =std::sqrt(C.size());     //Se calcula el tamaño de la matriz
    for(int i=0;i<N*N;i++)      //ciclo que recorre las filas
    {
        for(int j=0;j<N;j++)        //ciclo que recorre las columnas
        {
            C[i]+=1.0*A[N*int(i/N)+j]*B[j*N+(i%N)];     //Algoritmo de multiplicación

        }
    }

}
void multiplicacion_blocking(const std::vector<double> a,const std::vector<double> b,std::vector<double> &c,int Nb)     //Se define la multiplicación usando blo
{
    int M=std::sqrt(a.size());      //Se calcula el tamaño de la matriz
    if( Nb > M )        //Se usa un ciclo if para que la función sea definida incluso cuando el bloque es mayor a la matriz
    {
      multiplicacion_directa(a,b,c);        //En este caso se usa la multiplicación directa
    }
    else
    {
    int N=M/Nb;         //Se calcula el número de bloques que se tendrán en la función

     for(int block_i=0;block_i<N;block_i++)         //Se ubica el bloque según las filas en a y en c
        {
             for(int block_j=0;block_j<N;block_j++)         //Se ubica el bloque según las columnas de b y c
             {
                 for(int block_k=0;block_k<N;block_k++)         //Se ubica el bloque para la multiplicación de a y b
                 {
                      for(int i=block_i*Nb;i<(block_i+1)*Nb;i++)        //Se recorren las filas del bloque 
                      {
                          for(int j=block_j*Nb;j<(block_j+1)*Nb;j++)        //Se recorren las columnas del bloque 
                          {
                               for(int k=block_k*Nb;k<(block_k+1)*Nb;k++)   	    //Se emplea k para implementar el algorítmo de la multiplicación por blocking
                              {
                                c[i*M+j]+=a[i*M+k]*b[M*k+j];        //Se implementa el algorítmo de multiplicación
                              }
                         }
                     }
                 }
             }
         }
    }


}

void multplicacion_armadillo(arma::Mat<double> & A,arma::Mat<double>& B,arma::Mat<double> & C)      //Se define la multiplicacion usando Armadillo
{
  C=A*B;
}
