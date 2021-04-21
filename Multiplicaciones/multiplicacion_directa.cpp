void multiplicacion_directa(const double * A, const double * B, double* C, const int N)
{
  for(int i=0;i<N*N;i++)
    {
      for(int j=0;j<N;j++)
 {
   C[i]+=1.0*A[N*int(i/N)+j]*B[j*N+(i%N)];

 }
    }

};
