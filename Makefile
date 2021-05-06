M_S=0  #Matrix size
T_M=0 #code To Measure, 1 is multiplication, 0 is transpose

FIXED_DEPS=Multiplicaciones.cpp Transpuestas.cpp 
LIB_DEPS=-lpapi -larmadillo

%0.x : %.cpp $(FIXED_DEPS)	
	g++ $(FIXED_DEPS) $< $(LIB_DEPS) -o $@   

%3.x : %.cpp $(FIXED_DEPS)	
	g++ $(FIXED_DEPS) $< $(LIB_DEPS) -O3 -o $@

Performance_blocking0.txt: Performance_blocking0.x   
	./$< $(MATRIX_SIZE) $(TO_MEASURE) > $@

Performance_blocking3.txt: Performance_blocking3.x   
	./$< $(MATRIX_SIZE) $(TO_MEASURE) > $@
	
Performance_Matrix_Size0.txt: Performance_Matrix_Size0.x   
	./$< $(TO_MEASURE) > $@
	
Performance_Matrix_Size3.txt: Performance_Matrix_Size3.x   
	./$< $(TO_MEASURE) > $@

block_graph.pdf: Performance_blocking0.txt Performance_blocking3.txt
	gnuplot plot.gp
	mv file1.pdf $(MATRIX_SIZE)_Mflops.pdf
	mv file2.pdf $(MATRIX_SIZE)_Time.pdf

size_graph.pdf: Performance_Matrix_Size0.txt Performance_Matrix_Size3.txt
	gnuplot plot.gp
.PHONY:
clean:
	rm *.x *.o
