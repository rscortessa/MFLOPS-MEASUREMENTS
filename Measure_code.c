#include "constantes.h"
#include <stdio.h>
#include <stdlib.h>
#include "papi.h"
#include <random>

double desviacion_estandar(std::vector<double> & MFLOPS)
void fill_random_vector(std::vector<double> & v);


int main()
{
 //Inicializar las variables auxiliares
 std::vector<double> MFLOPS(cuentas+1,0);
 std::vector<double> REAL_TIME(cuentas+1,0);
 std::vector<double> PROC_TIME(cuentas+1,0);

 //En caso de que se vaya a variar el tamaño del arreglo, el for debe empezar en la siguiente linea.
 int Nmax=5;
 //Se inicializan los arreglos a utilizar std::vector<double> A(N,0), Eigen::MatrixXd as(N,N) o arma::mat a(N,N,arma::fill::ones);
 std::vector<double> a(Nmax*Nmax,0);
 std::vector<double> b(Nmax*Nmax,0);
 std::vector<double> c(Nmax*Nmax,0);


 for(int i=0; i<cuentas;i++)
    {
      if((retval=PAPI_flops_rate(PAPI_FP_OPS,&ireal_time,&iproc_time,&iflpops,&imflops)) < PAPI_OK)
	{ 
	  printf("Could not initialise PAPI_flops \n");
	  printf("Your platform may not support floating point operation event.\n"); 
	  printf("retval: %d\n", retval);
	  exit(1);
	}
      //Se coloca el código a medir...  
      multiplicacion_directa(a,b,c,Nmax);
      if((retval=PAPI_flops_rate(PAPI_FP_OPS,&real_time, &proc_time, &flpops, &mflops))<PAPI_OK)
	{    
	  printf("retval: %d\n", retval);
	  exit(1);
	}
      MFLOPS[0]+=mflops/cuentas;
      REAL_TIME[0]+=real_time/cuentas;
      PROC_TIME[0]+=proc_time/cuentas;
      MFLOPS[i+1]=mflops;
      REAL_TIME[i+1]=real_time;
      PROC_TIME[i+1]=proc_time;
      
      // En este espacio se imprime algún resultado del código
      std::ofstream fout;
      fout.open("Data.txt"); // Se guarda en un archivo de texto dado que no se quiere que aparezca en al ejecución
      for(int i=0;i<Nmax;i++)
	{
	  fout<<c[i]<<"\t";
	}
    }
      std::cout<<"MFLOPS"<<" \t "<<"MFLOPS%"<<" \t "<<"REAL_TIME"<<" \t "<<"REAL_TIME%"<<" \t "<<"PROC_TIME"<<" \t "<<"PROC_TIME%"<<std::endl;
      std::cout<<MFLOPS[0]<<"\t "<<desviacion_estandar(MFLOPS)<<"\t "<<REAL_TIME[0]<<"\t "<<desviacion_estandar(REAL_TIME)<<"\t "<<PROC_TIME[0]<<"\t"<<desviacion_estandar(PROC_TIME)<<"\n";
  
}

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

void fill_random_vector(std::vector<double> & v)
{
    std::mt19937 gen(1);
    std::uniform_real_distribution<> dist(-1.0,1.0);
    for(auto & x: v)
    {
        x=dist(gen);
    }
}

