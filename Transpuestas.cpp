#include <armadillo>
#include <Eigen/Dense>
#include <cmath>
#include "Transpuestas.h"
  void transpuesta_blocking(std::vector<double> & A, std::vector<double>&ABT, int P)
{
    //Segundo, subdividimos la matriz A en pequeños bloques dentro de la matriz
    //de dimensión P, con el fin de trasponer estos pequeños bloques dentro de
    //la matriz A e internamente transponer los bloques

    int N=std::sqrt(A.size());
    if( std::fmod(N,P)!=0 )
    {
      transpuesta_directa(A);
    }
    else
    {
    for(int ii=0; ii<N; ii+=P)
    {
        for(int jj=0; jj<N; jj+=P)
        {
            for(int ip=ii; ip<ii+P; ip++)
            {
                for(int jp=jj; jp<jj+P; jp++)
                {
                    ABT[ip*N+jp]=1.0*A[jp*N+ip];
                    //cout<<ABT[ip*N+jp]<<"\t";
                }//cout<<endl;
            }
        }
    }
    }
}

void transpuesta_armadillo(arma::Mat<double> & A)
{
    A=1.0*A.t();
}

void transpuesta_directa(std::vector<double> &A)
{
  int N=std::sqrt(A.size());
    for(int ii=0; ii<N; ++ii){
        for(int jj=0; jj<N; ++jj)
        {
            A[ii*N+jj]=(A[jj*N+ii])*(1.0);
        }
    }
}

void transpuesta_eigen(Eigen::MatrixXd & A)
{
  A=1.0*A.transpose();
}
