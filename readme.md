# HOW TO USE MAKEFILE:

## Contenido:
> El Makefile del proyecto se compone de distintas reglas de creación de archivos, los archivos base son: **Performance_blocking.cpp** y **Performance_Matrix_Size.cpp**, el primero es asociado a los archivos de texto y gráficas relacionadas con la dependencia de las operaciones matriciales en función del tamaño de bloque (archivo de c++ exclusivo para el método de blocking), el segundo es asociado a los archivos de texto y gráficas relacionadas a las operaciones matriciales en función del tamaño de la matriz para los cuatro métodos realizados.
> ### Uso de variables en el Makefile
> El Makefile de este proyecto funciona por variables que determinan que proceso hacer, estas variables son: <br>
>  * **M_S** indica el tamaño de la matriz a usar para el código de Performance_blocking.cpp <br>
>  * **T_M** equivale a William en cada código, para indicar qué operación se va a realizar, 
>  * **CUENT** determina cuántas cuentas son realizadas, para establecer barras de error en cada gráfica. <br>
> Entonces, para usar el Makefile es necesario darle valores a estas variables según la operación que uno desee realizar.
> ### Reglas de creación en el Makefile
> El Makefile contiene 11 reglas de creación de archivos, 2 relacionadas con los ejecutables con y sin optimización, para diferenciarlos se denotará su terminación **0.x** y **3.x** respectivamente, las demás cuatro reglas generan los archivos .txt dos para cada archivo .cpp con y sin compilación.
> Las otros 5 tipos de reglas en el Makefile poseen generan las gráficas de formato pdf, vale la pena resaltar que en este tipo de reglas los target no son en específico el nombre de un archivo, las reglas de este tipo son:
> *  **block_all.pdf** Genera los .txt y .pdf para unas variables M_S, T_M y CUENT fijas.
> *  **block.pdf** Genera con base a los .txt ya existentes en el repo los  .pdf para unas variables M_S, T_M y CUENT fijas.
> *  **size_all.pdf** Genera los .txt y .pdf para unas variables T_M y CUENT fijas.
> *  **size.pdf** Genera con base a los .txt ya existentes en el repo los  .pdf para unas variables T_M y CUENT fijas.
> ### Ejemplo:
> Si se desea graficar los datos del performance según el tamaño de matriz de la multiplicación de Eigen con 3 cuentas, se debe ejecutar el siguiente comando: <br>
> **make "T_M"=0 "CUENT"=3 Msize.pdf** 

#INFORMACIÓN DE NORMALIZACIÓN
>los archivos .txt están normalizados con respecto al pico del procesador 18.6 Gflops
>
>los archivos .pdf están normalizados con respecto al pico del procesador por nucleo 2.8 Gflops
