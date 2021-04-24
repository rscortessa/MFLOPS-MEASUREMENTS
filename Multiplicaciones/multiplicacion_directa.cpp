#include<vector>
void multiplicacion_directa(std::vector<double> & A,std::vector<double> & B,std::vector<double> & C, int N)
{
  for(int i=0;i<N*N;i++)
    {
      for(int j=0;j<N;j++)
 {
   C[i]+=1.0*A[N*int(i/N)+j]*B[j*N+(i%N)];

 }
    }

};
