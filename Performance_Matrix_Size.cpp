#include <stdio.h>
#include <stdlib.h>
#include <papi.h>
#include <random>
#include <iostream>
#include <fstream>
#include <cmath>
#include "Multiplicaciones.h"
#include "Transpuestas.h"
double desviacion_estandar(std::vector<double> & MFLOPS);
void fill_random_vector(std::vector<double> & v);


int main(int argc,char**argv)
{
	int Nb=8 ; //optim size blocking
	int William = std::atoi(argv[1]); //william determines the code to measure
	float real_time, proc_time,mflops;
  	long long flpops;
  	float ireal_time, iproc_time, imflops;
  	long long iflpops;
  	int retval;
  	int cuentas= std::atoi(argv[2]);
	//Inicializar las variables auxiliares
 	std::vector<double> MFLOPS(cuentas+1,0);
 	std::vector<double> REAL_TIME(cuentas+1,0);
 	std::vector<double> PROC_TIME(cuentas+1,0);


	 std::cout<<"MFLOPS"<<" \t "<<"MFLOPS%"<<" \t "<<"REAL_TIME"<<" \t "<<"REAL_TIME%"<<" \t "<<"PROC_TIME"<<" \t "<<"PROC_TIME%"<<" \t "<<"N_B"<<std::endl;
 	for(int jj=0;jj<15;jj++)
	{
       		int Nmax=std::pow(2,jj);
		for(int ii=0; ii<cuentas;ii++)
  		{

     		 	//if(Nmax*Nmax<Nb) exit(0);
     		 	if((retval=PAPI_flops_rate(PAPI_FP_OPS,&ireal_time,&iproc_time,&iflpops,&imflops)) < PAPI_OK)
			{
		 		printf("Could not initialise PAPI_flops \n");
		 		printf("Your platform may not support floating point operation event.\n");
	 	 		printf("retval: %d\n", retval);
		 		exit(1);
			}
      		//Se coloca el código a medir...
	 		if( William == 0 )
	 		{
        			Eigen::MatrixXd AE = Eigen::MatrixXd::Random(Nmax,Nmax);
        			Eigen::MatrixXd BE = Eigen::MatrixXd::Random(Nmax,Nmax);	
				Eigen::MatrixXd CE = Eigen::MatrixXd::Zero(Nmax, Nmax);
     				multiplicacion_eigen(AE,BE,CE);
	 		}
	 		if( William == 1 )
	 		{
       				arma::mat AA(Nmax, Nmax, arma::fill::randu);
        			arma::mat BA(Nmax, Nmax, arma::fill::randu);
				arma::mat CA(Nmax, Nmax); CA.zeros();
         		 	multplicacion_armadillo(AA,BA,CA);
	 		}
         		if( William == 2 )
	 		{
			 	Eigen::MatrixXd AE = Eigen::MatrixXd::Random(Nmax,Nmax);
				Eigen::MatrixXd AET = Eigen::MatrixXd::Zero(Nmax, Nmax);
     			 	transpuesta_eigen(AE,AET);
	 		}
	 		if( William == 3 )
	 		{
				arma::mat AA(Nmax, Nmax, arma::fill::randu);
			 	transpuesta_armadillo(AA);
	 		}
			if( William == 4 )
			{
				std::vector<double> a(Nmax*Nmax,0);
        			std::vector<double> b(Nmax*Nmax,0);
        			std::vector<double> c(Nmax*Nmax,0);
        			fill_random_vector(a);
        			fill_random_vector(b);
				multiplicacion_blocking(a,b,c,Nb);
			}
			if( William == 5 )
			{
				std::vector<double> a(Nmax*Nmax,0);
				fill_random_vector(a);
				transpuesta_blocking(a,Nb);
			}
			if( William == 6 )
			{
				std::vector<double> a(Nmax*Nmax,0);
        			std::vector<double> b(Nmax*Nmax,0);
        			std::vector<double> c(Nmax*Nmax,0);
        			fill_random_vector(a);
        			fill_random_vector(b);
				multiplicacion_directa(a,b,c);
			}
			if( William == 7 )
			{
				std::vector<double> a(Nmax*Nmax,0);
				fill_random_vector(a);
				transpuesta_blocking(a);
			}

      			if((retval=PAPI_flops_rate(PAPI_FP_OPS,&real_time, &proc_time, &flpops, &mflops))<PAPI_OK)
			{
	 	 		printf("retval: %d\n", retval);
	 			exit(1);
			}
      			MFLOPS[0]+=mflops/cuentas;
      			REAL_TIME[0]+=real_time/cuentas;
      			PROC_TIME[0]+=proc_time/cuentas;
      			MFLOPS[ii+1]=mflops;
      			REAL_TIME[ii+1]=real_time;
      			PROC_TIME[ii+1]=proc_time;

      			// En este espacio se imprime algún resultado del código
      			std::ofstream trash ("Delete_me_please.txt");
      			double aux_sum=0.0;
      			// Se guarda en un archivo de texto dado que no se quiere que aparezca en al ejecución
      			for(auto x : c)
      			{	
        		aux_sum += c[ll];
   			}
      			trash << aux_sum ;
      			trash.close();
		}
	 //peak 18.64 Gflops
	 std::cout<<MFLOPS[0]/(18640)<<"\t "<<desviacion_estandar(MFLOPS)/(18640)<<"\t "<<REAL_TIME[0]<<"\t "<<desviacion_estandar(REAL_TIME)<<"\t "<<PROC_TIME[0]<<"\t"<<desviacion_estandar(PROC_TIME)<<"\t"<<Nmax<<std::endl;
	 REAL_TIME[0]=0;
 	 MFLOPS[0]=0;
	 PROC_TIME[0]=0;
	}
	return 0;
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
