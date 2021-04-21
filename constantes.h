#include <stdio.h>
#include <stdlib.h>
#include "papi.h"
#include <cmath>
#include<iostream>
#include "./Multiplicaciones/funciones_de_multiplicacion.h"
#include "./Transpuesta/funciones_de_transposicion.h"
//Calcular desviación estandar e imprimir
double desviacion_estandar(double * MFLOPS,double mu);
void print(double *A,double mu);
//Variables
 float real_time, proc_time,mflops;
 long long flpops;
 float ireal_time, iproc_time, imflops;
 long long iflpops;
 int retval;
int cuentas=100;
double MFLOPS[100]={0};
double mu_MFLOPS=0;
double REAL_TIME[100]={0};
double mu_REAL_TIME=0;
double PROC_TIME[100]={0};
double mu_PROC_TIME=0;
 double A[4]={1,0,0,1};
 double B[4]={1,1,1,1};
 double C[4]={0};
