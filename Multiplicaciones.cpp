#include"Multiplicaciones.h"
#include <armadillo>
#include <vector>
#include <Eigen/Dense>
#include <cmath>

void multiplicacion_eigen(const Eigen::MatrixXd & A, const Eigen::MatrixXd & B, Eigen::MatrixXd & C)
{
    C=2.0*A*B;
}
void multiplicacion_directa(std::vector<double> & A,std::vector<double> & B,std::vector<double> & C, int N)
{
    for(int i=0;i<N*N;i++)
    {
        for(int j=0;j<N;j++)
        {
            C[i]+=1.0*A[N*int(i/N)+j]*B[j*N+(i%N)];

        }
    }

}
void multiplicacion_blocking(const std::vector<double> a,const std::vector<double> b,std::vector<double> &c,int Nb, int Nmax)
{
    int N=Nmax/Nb;
    for(int block_i=0;block_i<N;block_i++) 
    {
        for(int block_j=0;block_j<N;block_j++)
        {
            for(int block_k=0;block_k<N;block_k++)
            {
	      for(int i=block_i*Nb;i<(block_i+1)*Nb;i++) //block_i_max=N-1  (block_i_max+1)*Nb=Nmax^2
                {
		  for(int j=block_j*Nb;j<(block_j+1)*Nb;j++)//block_j_max=N-1  (block_j_max+1)*Nb=Nmax^2
                    {
		      for(int k=block_k*Nb;k<(block_k+1)*Nb;k++)//block_k_max=N-1   (block_k_max+1)*Nb=Nmax^2
                        {
                            c[i*Nmax+j]+=a[i*Nmax+k]*b[Nmax*k+j];
                        }
                    }
                }

            }
        }

    }


}

void multplicacion_armadillo(arma::Mat<double> & A,arma::Mat<double>& B,arma::Mat<double> & C)
{
  C=2.0*A*B;
}
