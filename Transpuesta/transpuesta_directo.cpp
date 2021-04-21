void transpuesta(double * A, const int N)
{
  double e=1.0;
   for(int ii=0; ii<N; ++ii){
   for(int jj=0; jj<N; ++jj){
     A[ii*N+jj]=(A[jj*N+ii])*(e);
   }
}
}
