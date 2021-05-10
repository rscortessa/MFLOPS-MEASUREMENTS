#include <stdio.h>									
#include <stdlib.h>
#include <papi.h>
#include <random>
#include <iostream>
#include <fstream>
#include <cmath>
#include "Multiplicaciones.h"				//Se incluye el código de Multiplicaciones.cpp
#include "Transpuestas.h"				//Se incluye el código de transpuestas.cpp
double desviacion_estandar(std::vector<double> & MFLOPS);	//Se inicializa el vector de desviación estándar
void fill_random_vector(std::vector<double> & v);		//


int main(int argc,char**argv)
{
	std::cout.precision(7); std::cout.setf(std::ios::scientific);
	int Nb=8 ; //optimum size for blocking
	int William = std::atoi(argv[1]); //william determinates the code to measure
	//Variables for PAPI are initialized
	float real_time, proc_time,mflops;	
  	long long flpops;			
  	float ireal_time, iproc_time, imflops;	
  	long long iflpops;			
  	int retval;				
  	int cuentas= std::atoi(argv[2]);	//Determinates the number of counts made by the program
	//Aux variables are initialized
 	std::vector<double> MFLOPS(cuentas+1,0);
 	std::vector<double> REAL_TIME(cuentas+1,0);
 	std::vector<double> PROC_TIME(cuentas+1,0);

	//Variables used to measure the development of the code with PAPI are printed
	std::cout<<"MFLOPS"<<" \t "<<"MFLOPS%"<<" \t "<<"REAL_TIME"<<" \t "<<"REAL_TIME%"<<" \t "<<"PROC_TIME"<<" \t "<<"PROC_TIME%"<<" \t "<<"Nmax"<<std::endl;
 	for(int jj=0;jj<15;jj++) 	//For cicle to variate the size of the matrix for 1 to 16384
	{
       		int Nmax=std::pow(2,jj);	//Nmax determinates the size of the matrix
		for(int ii=0; ii<cuentas;ii++)		//For cicle to realize each count
  		{

     		 	//if(Nmax<Nb) exit(0);
     		 	if((retval=PAPI_flops_rate(PAPI_FP_OPS,&ireal_time,&iproc_time,&iflpops,&imflops)) < PAPI_OK)		//This code checks if PAPI can be used in the CPU
			{
		 		printf("Could not initialise PAPI_flops \n");
		 		printf("Your platform may not support floating point operation event.\n");
	 	 		printf("retval: %d\n", retval);
		 		exit(1);
			}
      		//Here William determinates the code to measure
	 		if( William == 0 )	//Initialization and calculation of Eigen Multiplication
	 		{
        			Eigen::MatrixXd AE = Eigen::MatrixXd::Random(Nmax,Nmax);
        			Eigen::MatrixXd BE = Eigen::MatrixXd::Random(Nmax,Nmax);	
				Eigen::MatrixXd CE = Eigen::MatrixXd::Zero(Nmax, Nmax);
     				multiplicacion_eigen(AE,BE,CE);
	 		}
	 		if( William == 1 )		//Initialization and calculation of Armadillo Multiplication
	 		{
       				arma::mat AA(Nmax, Nmax, arma::fill::randu);
        			arma::mat BA(Nmax, Nmax, arma::fill::randu);
				arma::mat CA(Nmax, Nmax); CA.zeros();
         		 	multplicacion_armadillo(AA,BA,CA);
	 		}
         		( William == 2 )|		//Initialization and calculation of Eigen Transposition
	 		{
			 	Eigen::MatrixXd AE = Eigen::MatrixXd::Random(Nmax,Nmax);
				Eigen::MatrixXd AET = Eigen::MatrixXd::Zero(Nmax, Nmax);
     			 	transpuesta_eigen(AE,AET);
	 		}
	 		if( William == 3 )		//Initialization and calculation of Armadillo Transposition
	 		{
				arma::mat AA(Nmax, Nmax, arma::fill::randu);
			 	transpuesta_armadillo(AA);
	 		}
			if( William == 4 )		//Initialization and calculation of Blocking multiplication
			{
				std::vector<double> a(Nmax*Nmax,0);
        			std::vector<double> b(Nmax*Nmax,0);
        			std::vector<double> c(Nmax*Nmax,0);
        			fill_random_vector(a);
        			fill_random_vector(b);
				multiplicacion_blocking(a,b,c,Nb);
			}
			if( William == 5 )		//Initialization and calculation of Blocking Transposition
			{
				std::vector<double> a(Nmax*Nmax,0);
				std::vector<double> b(Nmax*Nmax,0);
				fill_random_vector(a);
				fill_random_vector(b);
				transpuesta_blocking(a,b,Nb);
			}
			if( William == 6 )		//Initialization and calculation of Direct Multiplication
			{
				std::vector<double> a(Nmax*Nmax,0);
        			std::vector<double> b(Nmax*Nmax,0);
        			std::vector<double> c(Nmax*Nmax,0);
        			fill_random_vector(a);
        			fill_random_vector(b);
				multiplicacion_directa(a,b,c);
			}
			if( William == 7 )		//Initialization and calculation of Direct Transposition
			{
				std::vector<double> a(Nmax*Nmax,0);
				fill_random_vector(a);
				transpuesta_directa(a);
			}

      			if((retval=PAPI_flops_rate(PAPI_FP_OPS,&real_time, &proc_time, &flpops, &mflops))<PAPI_OK)
			{
	 	 		printf("retval: %d\n", retval);
	 			exit(1);
			}
			//Vectors of PAPI are filled for the code calculated by william
      			MFLOPS[0]+=mflops/cuentas;
      			REAL_TIME[0]+=real_time/cuentas;
      			PROC_TIME[0]+=proc_time/cuentas;
      			MFLOPS[ii+1]=mflops;
      			REAL_TIME[ii+1]=real_time;
      			PROC_TIME[ii+1]=proc_time;

      			//Some results of the code are printed and saved in a .txt file to forze the CPU to calculate them
      			std::ofstream trash ("Delete_me_please.txt");
      			double aux_sum=0.0;
			std::vector<double> c(Nmax*Nmax,0);
      			for(auto x: c)
      			{	
        		aux_sum += x;
   			}
      			trash << aux_sum ;
      			trash.close();
		}
	 //peak 18.64 Gflops
	 //The results that are gonna be used are printed 
	 std::cout<<MFLOPS[0]/(18640)<<"\t "<<desviacion_estandar(MFLOPS)/(18640)<<"\t "<<REAL_TIME[0]<<"\t "<<desviacion_estandar(REAL_TIME)<<"\t "<<PROC_TIME[0]<<"\t"<<desviacion_estandar(PROC_TIME)<<"\t"<<Nmax<<std::endl;
	 REAL_TIME[0]=0;
 	 MFLOPS[0]=0;
	 PROC_TIME[0]=0;
	}
	return 0;
}


double desviacion_estandar(std::vector<double> & MFLOPS)	//The function desviacion_estandar is defined
{
  double sigma=0;
  double N=MFLOPS.size();
  for(int i=1;i<N;i++)
    {
      sigma+=std::pow((MFLOPS[i]-MFLOPS[0]),2);		//The square of the standard deviation is calculated
    }
  sigma=std::sqrt(sigma/N);		//The standard deviation is finally calculated
  return sigma;
}


void fill_random_vector(std::vector<double> & v)		//This vector is used to fill the Matrixes used in direct/blocking multiplication and transposition
{
    std::mt19937 gen(1);
    std::uniform_real_distribution<> dist(-1.0,1.0);
    for(auto & x: v)
    {
        x=dist(gen);
    }
}
