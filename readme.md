# HOW TO USE MAKEFILE:

## Contenido:

> El Makefile de este proyecto funciona por variables que determinan que proceso hacer, estas variables son: <br>

> M_S que indica el tamaño de la matriz a usar para el código de Performance_blocking.cpp <br>

> T_M que equivale a William en cada código, para indicar qué operación se va a realizar. <br>
> CUENT que determina cuántas cuentas son realizadas, para establecer barras de error en cada gráfica. <br>

> Entonces, para usar el Makefile es necesario darle valores a estas variables según la operación que uno desee realizar.
> ### Ejemplo:
> Si se desea graficar los datos del performance según el tamaño de matriz de la multiplicación de Eigen con 3 cuentas, se debe ejecutar el siguiente comando: <br>
> **make "T_M"=0 "CUENT"=3 Msize.pdf** 
