//Sea una matriz A de dimesión N a la cual deseamos calcular su transpuesta
//Como modo alternativo a la operación directa usaremos blocking
//Primero, simplificaremos el problema con tal de usar arreglos unidimensionales

double TRBlock(const double * A, const double * ABT, const int N, int P)
{
    //Segundo, subdividimos la matriz A en pequeños bloques dentro de la matriz
    //de dimensión P, con el fin de trasponer estos pequeños bloques dentro de
    //la matriz A e internamente transponer los bloques

    for(int ii=0; ii<N; ii+=P){
        for(int jj=0; jj<N; jj+=P){

            for(int ip=ii; ip<ii+P; ip++){
                for(int jp=jj; jp<jj+P; jp++){
                    ABT[ip*N+jp]=1.0*A[jp*N+ip];
                    //cout<<ABT[ip*N+jp]<<"\t";
                }//cout<<endl;
            }
        }
    }

    return 0;
}
