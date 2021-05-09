M_S=0  #Matrix size
T_M=0 #code To Measure, 1 is multiplication, 0 is transpose for the performance blocking code. On the other hand, 0 is for multiplication_eigen, 1 is for multiplication_arm, 2 
#is for transpose_eigen, 3 is for transpose_arm, for the performance matrix size code.
CUENT=1 #Number of times each operation is applied, para determinar el tamaño de la muestra. 
FIXED_DEPS=Multiplicaciones.cpp Transpuestas.cpp 		#Se definen las dependencias de todos programas que se usarán
LIB_DEPS=-lpapi -larmadillo					#Se definen todas las librerías para que se enlacen al momento de la compilación

%0.x : %.cpp $(FIXED_DEPS) 					#Se compilan SIN OPTIMIZACIÓN todos los archivos cpp junto con las dependencias y los enlaces con las librerías 
	g++ $(FIXED_DEPS) $< $(LIB_DEPS) -o $@   

%3.x : %.cpp $(FIXED_DEPS)	
	g++ $(FIXED_DEPS) $< $(LIB_DEPS) -O3 -o $@		#Se compilan CON OPTIMIZACIÓN O3 todos los archivos cpp junto con las dependencias y los enlaces con las librerías

Performance_blocking0.txt: Performance_blocking0.x   		#Se ejecuta el archivo Performance_blocking0.x según el tamaño de matriz y operaciones deseadas (multiplicación y
	./$< $(M_S) $(T_M) $(CUENT) > pdfdata/$(M_S)_$(T_M)$@		#transposición)

Performance_blocking3.txt: Performance_blocking3.x   		#Se ejecuta el archivo Performance_blocking3.x según el tamaño de matriz y operaciones deseadas (multiplicación y
	./$< $(M_S) $(T_M) $(CUENT) > pdfdata/$(M_S)_$(T_M)$@		#transposición)
	
Performance_Matrix_Size0.txt: Performance_Matrix_Size0.x   	#Se ejecuta el archivo Performance_Matrix_Size0.txt según la operación deseada (multiplicación por armadillo y 
	./$< $(T_M) $(CUENT) > pdfdata/$(T_M)$@				#eigen, transposición por armadillo y eigen)
	
Performance_Matrix_Size3.txt: Performance_Matrix_Size3.x   	#Se ejecuta elarchivo Performance_Matrix_Size0.txt según la operación deseada (multiplicación por armadillo y 
	./$< $(T_M) $(CUENT) > pdfdata/$(T_M)$@				#eigen, transposición por armadillo y eigen)

block_graph.pdf: Performance_blocking0.txt Performance_blocking3.txt #Block_graph es usado como objetivo para crear las gráficas creadas en el archivo plot.gp
	mv pdfdata/$(M_S)Performance_blocking0.txt aux0.txt     # Cambio de nombre a nombre auxiliar para ser utilizado por gnuplot 
	mv pdfdata/$(M_S)Performance_blocking3.txt aux3.txt
	gnuplot plot.gp
	mv file1.pdf pdfdata/blocking_$(M_S)_Mflops.pdf				#En el target plot.gp se crean las gráficas para estudiar la performance del blocking con los nombres file1.pdf y file2.pdf, 
	mv file2.pdf pdfdata/blocking_$(M_S)_Time.pdf				#es por eso que con los nombres file1.pdf y file2.pdf, es por eso que se les cambia el nombre según corresponda
	mv  aux0.txt pdfdata/$(M_S)Performance_blocking0.txt
	mv  aux3.txt pdfdata/$(M_S)Performance_blocking3.txt
size_graph.pdf: Performance_Matrix_Size0.txt Performance_Matrix_Size3.txt 	#En el target size_graph se crean las gráficas para estudiar el performance según el tamaño de la matriz
	mv pdfdata/$(M_S)Performance_Matrix_Size0.txt aux0.txt
	mv pdfdata/$(M_S)Performance_Matrix_Size3.txt aux3.txt
	gnuplot plot.gp
	mv file1.pdf pdfdata/Matrix_$(M_S)_Mflops.pdf				#En el target plot.gp se crean las gráficas para estudiar la performance del blocking con los nombres file1.pdf y file2.pdf, 
	mv file2.pdf pdfdata/Matrix_$(M_S)_Time.pdf				#es por eso que con los nombres file1.pdf y file2.pdf, es por eso que se les cambia el nombre según corresponda
	mv aux0.txt pdfdata/$(M_S)Performance_Matrix_Size0.txt
	mv aux3.txt pdfdata/$(M_S)Performance_Matrix_Size3.txt
.PHONY:
clean:								#Clean se usa para remover todos los archivos creados en este make
	rm *.x *.o
