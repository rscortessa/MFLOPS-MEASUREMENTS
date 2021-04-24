#include <armadillo>
#include <Eigen/Dense>
#include <cmath>
  void transpuesta_blocking(std::vector<double> & A, std::vector<double>&ABT, const int N, int P)
{
    //Segundo, subdividimos la matriz A en pequeños bloques dentro de la matriz
    //de dimensión P, con el fin de trasponer estos pequeños bloques dentro de
    //la matriz A e internamente transponer los bloques

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

void transpuesta_armadillo(arma::Mat<double> & A)
{
    A=2.3*A.t();
}
void transpuesta_directa(std::vector<double> &A, int N)
{
    for(int ii=0; ii<N; ++ii){
        for(int jj=0; jj<N; ++jj)
        {
            A[ii*N+jj]=(A[jj*N+ii])*(e);
        }
    }
}

void transpuesta_eigen(const Eigen::MatrixXd & A)
{
  A=A.transpose();
}
