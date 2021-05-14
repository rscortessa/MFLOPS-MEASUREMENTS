M_S=0
#Matrix size
T_M=0
# Performance_blocking code To Measure, 1 is multiplication, 0 is transpose. 
# Performance_Matrix_size code to measure 0,1,4,5 are multiplication eigen, arma, direct, blocking respectively
#                                         2,3,6,7 are transpose      eigen, arma, direct, blocking respectively
CUENT=1
#Number of times each operation is applied, para determinar el tamaño de la muestra. 
FIXED_DEPS=Multiplicaciones.cpp Transpuestas.cpp 		#Se definen las dependencias de todos programas que se usarán
LIB_DEPS=-lpapi -larmadillo					#Se definen todas las librerías para que se enlacen al momento de la compilación

%0.x : %.cpp $(FIXED_DEPS) 					#Se compilan SIN OPTIMIZACIÓN todos los archivos cpp junto con las dependencias y los enlaces con las librerías 
	g++ $(FIXED_DEPS) $< $(LIB_DEPS) $(DEBUG) -o $@   

%3.x : %.cpp $(FIXED_DEPS)	
	g++ $(FIXED_DEPS) $< $(LIB_DEPS) $(DEBUG) -O3 -o $@		#Se compilan CON OPTIMIZACIÓN O3 todos los archivos cpp junto con las dependencias y los enlaces con las librerías

Performance_blocking0.txt: Performance_blocking0.x   		#Se ejecuta el archivo Performance_blocking0.x según el tamaño de matriz y operaciones deseadas (multiplicación y #transposición)
	./$< $(M_S) $(T_M) $(CUENT) > pdfdata/$(M_S)_$(T_M)_$(CUENT)_$@		

Performance_blocking3.txt: Performance_blocking3.x   		#Se ejecuta el archivo Performance_blocking3.x según el tamaño de matriz y operaciones deseadas (multiplicación y transposición)
	./$< $(M_S) $(T_M) $(CUENT) > pdfdata/$(M_S)_$(T_M)_$(CUENT)_$@		

Performance_Matrix_Size0.txt: Performance_Matrix_Size0.x   	#Se ejecuta el archivo Performance_Matrix_Size0.txt según la operación deseada (multiplicación por armadillo y eigen, transposición por armadillo y eigen)
	./$< $(T_M) $(CUENT) > pdfdata/$(T_M)_$(CUENT)_$@				

Performance_Matrix_Size3.txt: Performance_Matrix_Size3.x   	#Se ejecuta elarchivo Performance_Matrix_Size0.txt según la operación deseada (multiplicación por armadillo y eigen, transposición por armadillo y eigen)
	./$< $(T_M) $(CUENT) > pdfdata/$(T_M)_$(CUENT)_$@				


#El target Block_graph se utiliza si se necesita graficar la curva con y sin optimización 
   #para determinado estudio de blocking para dado M_S. T_M, CUENT.
  #Se cambia el nombre de los archivos para ser utilizados por el archivo.gp. en seguida se devuelven estos archivos a su nombre original
block_graph.pdf: Performance_blocking0.txt Performance_blocking3.txt  
	mv pdfdata/$(M_S)_$(T_M)_$(CUENT)_Performance_blocking0.txt aux0.txt        
	mv pdfdata/$(M_S)_$(T_M)_$(CUENT)_Performance_blocking3.txt aux3.txt         
	gnuplot plot_block.gp
	mv file1.pdf pdfdata/blocking_$(M_S)_$(T_M)_$(CUENT)_Mflops.pdf				 
	mv file2.pdf pdfdata/blocking_$(M_S)_$(T_M)_$(CUENT)_Time.pdf				
	mv  aux0.txt pdfdata/$(M_S)_$(T_M)_$(CUENT)_Performance_blocking0.txt
	mv  aux3.txt pdfdata/$(M_S)_$(T_M)_$(CUENT)_Performance_blocking3.txt 
block$(M_S)_$(T_M)_$(CUENT).pdf: pdfdata/$(M_S)_$(T_M)_$(CUENT)_Performance_blocking0.txt pdfdata/$(M_S)_$(T_M)_$(CUENT)_Performance_blocking3.txt #grafica si el archivo .txt deseado ya existe
	mv pdfdata/$(M_S)_$(T_M)_$(CUENT)_Performance_blocking0.txt aux0.txt        
	mv pdfdata/$(M_S)_$(T_M)_$(CUENT)_Performance_blocking3.txt aux3.txt         
	gnuplot plot_block.gp
	mv file1.pdf pdfdata/blocking_$(M_S)_$(T_M)_$(CUENT)_Mflops.pdf
	mv file2.pdf pdfdata/blocking_$(M_S)_$(T_M)_$(CUENT)_Time.pdf
	mv aux0.txt pdfdata/$(M_S)_$(T_M)_$(CUENT)_Performance_blocking0.txt
	mv aux3.txt pdfdata/$(M_S)_$(T_M)_$(CUENT)_Performance_blocking3.txt

#En el target size_graph se crean las gráficas para estudiar el performance según el tamaño de la 
#su funcionamiento es análogo al caso de block_graph
size_graph.pdf: Performance_Matrix_Size0.txt Performance_Matrix_Size3.txt 	
	mv pdfdata/$(T_M)_$(CUENT)_Performance_Matrix_Size0.txt aux0.txt			
	mv pdfdata/$(T_M)_$(CUENT)_Performance_Matrix_Size3.txt aux3.txt
	gnuplot plot_matrix.gp
	mv file1.pdf pdfdata/Matrix_$(T_M)_$(CUENT)_Mflops.pdf				
	mv file2.pdf pdfdata/Matrix_$(T_M)_$(CUENT)_Time.pdf				
	mv aux0.txt pdfdata/$(T_M)_$(CUENT)_Performance_Matrix_Size0.txt
	mv aux3.txt pdfdata/$(T_M)_$(CUENT)_Performance_Matrix_Size3.txt

Msize_$(T_M)_$(CUENT).pdf: pdfdata/$(T_M)_$(CUENT)_Performance_Matrix_Size0.txt pdfdata/$(T_M)_$(CUENT)_Performance_Matrix_Size3.txt #grafica si ya existen los archivos .txt
	mv pdfdata/$(T_M)_$(CUENT)_Performance_Matrix_Size0.txt aux0.txt
	mv pdfdata/$(T_M)_$(CUENT)_Performance_Matrix_Size3.txt aux3.txt
	gnuplot plot_matrix.gp
	mv file1.pdf pdfdata/Matrix_$(T_M)_$(CUENT)_Mflops.pdf				
	mv file2.pdf pdfdata/Matrix_$(T_M)_$(CUENT)_Time.pdf				
	mv aux0.txt pdfdata/$(T_M)_$(CUENT)_Performance_Matrix_Size0.txt
	mv aux3.txt pdfdata/$(T_M)_$(CUENT)_Performance_Matrix_Size3.txt

.PHONY:
clean:								
	rm *.x *.o
