M_S=0  #Matrix size
T_M=0 #code To Measure, 1 is multiplication, 0 is transpose for the performance blocking code. On the other hand, 0 is for multiplication_eigen, 1 is for multiplication_arm, 2 
#is for transpose_eigen, 3 is for transpose_arm, for the performance matrix size code.

FIXED_DEPS=Multiplicaciones.cpp Transpuestas.cpp 		#Se definen las dependencias de todos programas que se usarán
LIB_DEPS=-lpapi -larmadillo					#Se definen todas las librerías para que se enlacen al momento de la compilación

%0.x : %.cpp $(FIXED_DEPS) 					#Se compilan SIN OPTIMIZACIÓN todos los archivos cpp junto con las dependencias y los enlaces con las librerías 
	g++ $(FIXED_DEPS) $< $(LIB_DEPS) -o $@   

%3.x : %.cpp $(FIXED_DEPS)	
	g++ $(FIXED_DEPS) $< $(LIB_DEPS) -O3 -o $@		#Se compilan CON OPTIMIZACIÓN O3 todos los archivos cpp junto con las dependencias y los enlaces con las librerías

Performance_blocking0.txt: Performance_blocking0.x   		#Se ejecuta el archivo Performance_blocking0.x según el tamaño de matriz y operaciones deseadas (multiplicación y
	./$< $(MATRIX_SIZE) $(TO_MEASURE) > $@			#transposición)

Performance_blocking3.txt: Performance_blocking3.x   		#Se ejecuta el archivo Performance_blocking3.x según el tamaño de matriz y operaciones deseadas (multiplicación y
	./$< $(MATRIX_SIZE) $(TO_MEASURE) > $@			#transposición)
	
Performance_Matrix_Size0.txt: Performance_Matrix_Size0.x   	#Se ejecuta el archivo Performance_Matrix_Size0.txt según la operación deseada (multiplicación por armadillo y 
	./$< $(TO_MEASURE) > $@					#eigen, transposición por armadillo y eigen)
	
Performance_Matrix_Size3.txt: Performance_Matrix_Size3.x   	#Se ejecuta el archivo Performance_Matrix_Size0.txt según la operación deseada (multiplicación por armadillo y 
	./$< $(TO_MEASURE) > $@					#eigen, transposición por armadillo y eigen)

block_graph.pdf: Performance_blocking0.txt Performance_blocking3.txt	#Block_graph es usado como objetivo para crear las gráficas creadas en el archivo plot.gp
	gnuplot plot.gp
	mv file1.pdf $(MATRIX_SIZE)_Mflops.pdf				#En el target plot.gp se crean las gráficas para estudiar la performance del blocking con los nombres file1.pdf y file2.pdf, 
	mv file2.pdf $(MATRIX_SIZE)_Time.pdf				#es por eso que con los nombres file1.pdf y file2.pdf, es por eso que se les cambia el nombre según corresponda

size_graph.pdf: Performance_Matrix_Size0.txt Performance_Matrix_Size3.txt 	#En el target size_graph se crean las gráficas para estudiar el performance según el tamaño de la matriz
	gnuplot plot.gp
=======
>>>>>>> d1be79f48bfbb57911e0c3c9926d602ac0bf0cf9
.PHONY:
clean:								#Clean se usa para remover todos los archivos creados en este make
	rm *.x *.o
