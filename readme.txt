HOW TO USE MAKEFILE:

El Makefile de este proyecto funciona por variables que determinan que proceso hacer, estas variables son:

--> M_S que indica el tamaño de la matriz a usar para el código de Performance_blocking.cpp
--> T_M que equivale a William en cada código, para indicar qué operación se va a realizar
--> CUENT que determina cuántas cuentas son realizadas, para establecer barras de error en cada gráfica

Entonces, para usar el Makefile es necesario darle valores a estas variables según la operación que uno desee realizar.

Por ejemplo, si se desea graficar los datos del performance según el tamaño de matriz de la multiplicación de Eigen con 3 cuentas, se debe ejecutar el siguiente comando:

make "T_M"=0 "CUENT"=3 Msize_0_3.pdf 
