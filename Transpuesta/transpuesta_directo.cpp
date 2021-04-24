void transpuesta(std::vector<double> &A, int N)
{
   for(int ii=0; ii<N; ++ii){
   for(int jj=0; jj<N; ++jj){
     A[ii*N+jj]=(A[jj*N+ii])*(e);
   }
}
}
