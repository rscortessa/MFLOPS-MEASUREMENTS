#include <armadillo>        //Se incluye la librería armadillo
#include <Eigen/Dense>      //Se incluyen las funciones de Eigen relacionadas al tipo MatrixXd
#include <cmath>            //Se incluye la librería cmath para operar entre matrices
#include "Transpuestas.h"   //Se enlaza con la librería de Transpuestas.h
  void transpuesta_blocking(std::vector<double> & A, std::vector<double>&ABT, int P) //En esta función se divide la matriz en matrices más pequeñas de tamaño PxP y a cada una de estas se le realiza la transposición, hay que tener en cuenta que las matrices PxP en si mismas deben también ser transpuestas respecto a sus posiciones originales en la matriz A. 
{

    int N=std::sqrt(A.size()); //se calcula el tamaño de la matriz
    if( std::fmod(N,P)!=0 ) //En este paso se determina si la matriz puede ser dividida en bloques de tamaño PxP de manera exacta
    {
      transpuesta_directa(A); //Si no se puede se corre la funcion transpuesta_directa(std::vector<double> &A)
    }
    else //En caso contrario se procede al metodo de blocking
    {
    for(int ii=0; ii<N; ii+=P)  //Se establece un ciclo que va marcando las fronteras de los bloques (recorre la matriz de P en P) para las columnas
    {
        for(int jj=0; jj<N; jj+=P)  //Se hace otro ciclo similar al anterior pero esta vez para las filas, más adelante lo que se hará son ciclos que recorran estos bloques de PxP elemento por elemento
        {
            for(int ip=ii; ip<ii+P; ip++) //Este ciclo recorre las columnas del bloque de tamaño PxP dentro de la matriz
            {
                for(int jp=jj; jp<jj+P; jp++) //Este ciclo recorre las filas del bloque de tamaño PxP dentro de la matriz
                {
                    ABT[ip*N+jp]=1.0*A[jp*N+ip]; //En esta parte se crea la matriz transpuesta (ABT), cada elemento de la matriz PxP es transpuesto y la misma matriz PxP es también transpuesta dentro de ABT respecto a su posición original en A, así se obtiene la transpuesta de A, además, se ejecuta una operación de punto flotante para poder medir los FLOPS correspondientes
                    //cout<<ABT[ip*N+jp]<<"\t";
                }//cout<<endl;
            }
        }
    }
    }
}

void transpuesta_armadillo(arma::Mat<double> & AA)
{
    AA=1.0*AA.t();  //Se realiza la transpuesta de una matriz usando la libreria armadillo y se realiza una operación de punto flotante para medir los FLOPS
}

void transpuesta_directa(std::vector<double> &A)  //En este caso se transpone la matriz elemento por elemento sin dividirla en ningún tipo de bloques (esta es la operación que se realiza cuando la matriz no se puede dividir de forma exacta en bloques de tamaño PxP)
{
  int N=std::sqrt(A.size());  //Se detecta el tamaño de la matriz
    for(int ii=0; ii<N; ++ii){  //Se inicia un ciclo que recorre las columnas de la matriz
        for(int jj=0; jj<N; ++jj) //Se inicia otro ciclo que recorre las filas de la matriz
        {
            A[ii*N+jj]=(A[jj*N+ii])*(1.0);  //Se reubica cada uno de los elementos de la matriz original en su posición transpuesta y se realiza una operación de punto flotante para medir los FLOPS
        }
    }
}

void transpuesta_eigen(const Eigen::MatrixXd & AE, Eigen::MatrixXd & AET) //En este caso se obtiene la transpuesta mediante el uso de la librería Eigen
{
  AET=1.231*AE.transpose().eval(); //Como en casos anteriores, se realiza una operación de punto flotante para medir los FLOPS
}
