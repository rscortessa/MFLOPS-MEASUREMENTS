#include <cmath>
#include <iostream>
double desviacion_estandar(double * MFLOPS,double mu)
{
  double sigma=0;
  for(int i=0;i<100;i++)
    {
      sigma+=std::pow((MFLOPS[i]-mu),2);
    }
  sigma=std::sqrt(sigma/100);
  return sigma;
}
void print(double *A,double mu)
{
  std::cout<<mu<<"("<<desviacion_estandar(A,mu)<<") ";
}
