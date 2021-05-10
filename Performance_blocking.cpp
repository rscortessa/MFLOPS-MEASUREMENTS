#include <stdio.h>
#include <stdlib.h>
#include <papi.h>
#include <random>
#include<iostream>
#include<fstream>
#include<cmath>
#include"Multiplicaciones.h"
#include"Transpuestas.h"
double desviacion_estandar(std::vector<double> & MFLOPS);
void fill_random_vector(std::vector<double> & v);


int main(int argc,char**argv)
{
	std::cout.precision(7); std::cout.setf(std::ios::scientific);
	int William = std::atoi(argv[2]); //Variable William determina que código será medido, 1 para multiplicación, 0 para transpuesta
  	float real_time, proc_time,mflops;
  	long long flpops;
  	float ireal_time, iproc_time, imflops;
  	long long iflpops;
  	int retval;
  	int cuentas=std::atoi(argv[3]); //Cuentas determina el número del tamaño de la muestra para cada operación.
 	//Inicializar las variables auxiliares
 	std::vector<double> MFLOPS(cuentas+1,0);
 	std::vector<double> REAL_TIME(cuentas+1,0);
 	std::vector<double> PROC_TIME(cuentas+1,0);

 	//En caso de que se vaya a variar el tamaño del arreglo, el for debe empezar en la siguiente linea.
 	int Nmat=std::atoi(argv[1]);
 	//Se inicializan los arreglos a utilizar como matrices
 	std::vector<double> a(Nmat*Nmat,0); 
	std::vector<double> b(Nmat*Nmat,0);
 	std::vector<double> c(Nmat*Nmat,0);
 	fill_random_vector(a); //Se llenan las matrices con números aleatorios
 	fill_random_vector(b); //Se llenan las matrices con números aleatorios
 
 	std::cout<<"MFLOPS"<<" \t "<<"MFLOPS%"<<" \t "<<"REAL_TIME"<<" \t "<<"REAL_TIME%"<<" \t "<<"PROC_TIME"<<" \t "<<"PROC_TIME%"<<" \t "<<"N_B"<<std::endl;
 	for(int ii=0;ii<13;ii++)
	{
		  int Nb=std::pow(2,ii);
		  
		for(int jj=0; jj<cuentas;jj++) 
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
		 	if( William ==1)
	 		{
     			 multiplicacion_blocking(a,b,c,Nb);
	 		} 
			if( William ==0)
	 		{
			 transpuesta_blocking(a,c,Nb);
			 }
      
      			if((retval=PAPI_flops_rate(PAPI_FP_OPS,&real_time, &proc_time, &flpops, &mflops))<PAPI_OK)
			{    
			  printf("retval: %d\n", retval);
			  exit(1);
			}
      			MFLOPS[0]+=mflops/cuentas;
      			REAL_TIME[0]+=real_time/cuentas;
      			PROC_TIME[0]+=proc_time/cuentas;
      			MFLOPS[jj+1]=mflops;
      			REAL_TIME[jj+1]=real_time;
      			PROC_TIME[jj+1]=proc_time;
      
      			// En este espacio se imprime algún resultado del código
      			std::ofstream trash ("TRASH.txt");
      			double aux_sum=0.0;
      			// Se guarda en un archivo de texto dado que no se quiere que aparezca en al ejecución
      			for(auto x : c)
     			{
       		 		aux_sum += x;
				x=0.0; //Se vacia C para volvera usarlo en la próxima medición
   			}
      			trash << aux_sum ;
      			trash.close();
    		}
 		//peak 18.64 Gflops
 		std::cout<<MFLOPS[0]/(18640)<<"\t "<<desviacion_estandar(MFLOPS)/(18640)<<"\t "<<REAL_TIME[0]<<"\t "<<desviacion_estandar(REAL_TIME)<<"\t "<<PROC_TIME[0]<<"\t"<<desviacion_estandar(PROC_TIME)<<"\t"<<Nb<<std::endl;
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

