#include<cmath>
void multiplicacion_blocking(const std::vector<double> a,const std::vector<double> b,std::vector<double> &c,int Nb)
{
  int N=sqrt(a.size())/Nb;
  for(int block_i=1;block_i<N+1;block_i++)
    {
      for(int block_j=1;block_j<N+1;block_j++)
	{
	  for(int block_k=1;block_k<N+1;block_k++)
	    {
	      for(int i=(block_i-1)*Nb;i<block_i*Nb;i++)
		{
		  for(int j=(block_j-1)*Nb;i<block_j*Nb;j++)
		    {
		       for(int k=(block_k-1)*Nb;i<block_k*Nb;k++)
			 {
			   c[i,j]+=a[i,k]*b[k,j];
			 }
		    }
		}

	    }
	}

    }


}
