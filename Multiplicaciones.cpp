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
    for(int ii=0;ii<N;ii++)      //ciclo que recorre las filas
    {
        for(int jj=0;jj<N;jj++)        //ciclo que recorre las columnas
        {
            {
                  C[ii*N+jj]+=A[ii*N+kk]*B[kk*N+jj];     //Algoritmo de multiplicación
            }
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

     for(int bi=0;bi<N;bi++)         //Se ubica el bloque según las filas en a y en c
        {
             for(int bj=0;bj<N;bj++)         //Se ubica el bloque según las columnas de b y c
             {
                 for(int bk=0;bk<N;bk++)         //Se ubica el bloque para la multiplicación de a y b
                 {
                      for(int i=bi*Nb;i<(bi+1)*Nb;i++)        //Se recorren las filas del bloque 
                      {
                          for(int j=bj*Nb;j<(bj+1)*Nb;j++)        //Se recorren las columnas del bloque 
                          { 
                               for(int k=bk*Nb;k<(bk+1)*Nb;k++)   	    //Se emplea k para implementar el algorítmo de la multiplicación por blocking
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
