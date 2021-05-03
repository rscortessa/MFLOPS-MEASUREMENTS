#include"Multiplicaciones.h"
#include <armadillo>
#include <vector>
#include <Eigen/Dense>
#include <cmath>

void multiplicacion_eigen(const Eigen::MatrixXd & A, const Eigen::MatrixXd & B, Eigen::MatrixXd & C)
{
    C=A*B;
}
void multiplicacion_directa(const std::vector<double> & A,const std::vector<double> & B,std::vector<double> & C)
{
    int N =std::sqrt(C.size());
    for(int i=0;i<N*N;i++)
    {
        for(int j=0;j<N;j++)
        {
            C[i]+=1.0*A[N*int(i/N)+j]*B[j*N+(i%N)];

        }
    }

}
void multiplicacion_blocking(const std::vector<double> a,const std::vector<double> b,std::vector<double> &c,int Nb)
{
    int M=std::sqrt(a.size());
    if( Nb > M )
    {
      multiplicacion_directa(a,b,c,M);
    }
    else
    {
    int N=M/Nb;

     for(int block_i=0;block_i<N;block_i++)
        {
             for(int block_j=0;block_j<N;block_j++)
             {
                 for(int block_k=0;block_k<N;block_k++)
                 {
                      for(int i=block_i*Nb;i<(block_i+1)*Nb;i++)
                      {
                          for(int j=block_j*Nb;j<(block_j+1)*Nb;j++)
                          {
                               for(int k=block_k*Nb;k<(block_k+1)*Nb;k++)
                              {
                            c[i*M+j]+=a[i*M+k]*b[M*k+j];
                              }
                         }
                     }
                 }
             }
         }
    }


}

void multplicacion_armadillo(arma::Mat<double> & A,arma::Mat<double>& B,arma::Mat<double> & C)
{
  C=A*B;
}
