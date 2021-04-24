#include<vector>
#include<cmath>
double desviacion_estandar(std::vector<double> & MFLOPS)
{
  double sigma=0;
  double N=MFLOPS.size();
  for(int i=1;i<N;i++)
    {
      sigma+=std::pow((MFLOPS[i]-MFLOPS[0]),2);
    }
  sigma=std::sqrt(sigma/N);
  return sigma;
}

