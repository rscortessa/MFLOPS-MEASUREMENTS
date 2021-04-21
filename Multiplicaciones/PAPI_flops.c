#include "constantes.h"
int main()
{
  for(int i=0; i<cuentas;i++)
    {
  if((retval=PAPI_flops_rate(PAPI_FP_OPS,&ireal_time,&iproc_time,&iflpops,&imflops)) < PAPI_OK)
  { 
    printf("Could not initialise PAPI_flops \n");
    printf("Your platform may not support floating point operation event.\n"); 
    printf("retval: %d\n", retval);
    exit(1);
  }
    multiplicacion_directa(A,B,C,2);  

    if((retval=PAPI_flops_rate(PAPI_FP_OPS,&real_time, &proc_time, &flpops, &mflops))<PAPI_OK)
  {    
    printf("retval: %d\n", retval);
    exit(1);
  }
  mu_MFLOPS+=mflops/100;
  mu_REAL_TIME+=real_time/100;
  mu_PROC_TIME+=proc_time/100;
  MFLOPS[i]=mflops;
  REAL_TIME[i]=real_time;
  PROC_TIME[i]=proc_time;
    }
  std::cout<<"Real time ";
  print(REAL_TIME,mu_REAL_TIME);
    std::cout<<"Proc_time ";
    print(PROC_TIME,mu_PROC_TIME);
    std::cout<<"Mflops ";
    print(MFLOPS,mu_MFLOPS);
    std::cout<<std::endl;
    }



