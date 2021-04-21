#include <stdio.h>
#include <stdlib.h>
#include "papi.h"
#include<iostream>
//Funciones de transposición
void transpuesta(double * A, const int N);
//Calcular desviación estandar e imprimir
double desviacion_estandar(double * MFLOPS,double mu);
void print(double *A,double mu);
// Variables

float real_time, proc_time,mflops;
  long long flpops;
  float ireal_time, iproc_time, imflops;
  long long iflpops;
  int retval;
  int N=5;
int cuentas=100;
double MFLOPS[100]={0};
double mu_MFLOPS=0;
double REAL_TIME[100]={0};
double mu_REAL_TIME=0;
double PROC_TIME[100]={0};
double mu_PROC_TIME=0;
  double A[25]={0};


