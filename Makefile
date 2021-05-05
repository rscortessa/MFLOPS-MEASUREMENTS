MATRIX_SIZE=0
OPTIM=0
TO_MEASURE=0

%0.x : %.cpp $(FIXED_DEPS)	
	g++ $(FIXED_DEPS) $< $(LIB_DEPS) -o $@   

%3.x : %.cpp $(FIXED_DEPS)	
	g++ $(FIXED_DEPS) $< $(LIB_DEPS) -O3 -o $@

Performance_blocking0.txt: Performance_blocking0.x   
	./$< $(MATRIX_SIZE) $(TO_MEASURE) > $@

Performance_blocking3.txt: Performance_blocking3.x   
	./$< $(MATRIX_SIZE) $(TO_MEASURE) > $@

block_graph.pdf: Performance_blocking0.txt Performance_blocking3.txt
	gnuplot plot.gp
	mv file.pdf $(MATRIX_SIZE).pdf




$(MATRIX_SIZE)_$(OPTIM)_$(TO_MEASURE)blocking: Performance_blocking.cpp #Regla de compilación para archivo individual
	g++ $(FIXED_DEPS) $< $(LIB_DEPS) -O$(OPTIM) -o $@.x  
	./$@.x $(MATRIX_SIZE) $(TO_MEASURE) > $@.txt



all: blocking.graph


FIXED_DEPS=Multiplicaciones.cpp Transpuestas.cpp 
LIB_DEPS=-lpapi -larmadillo
M_1=16;
M_2=32;



blocking.txt: Performance_blocking3.x Performance_blocking0.x  #this creates 8 txt files concerning the performance of the blocking algorithm for diferent matrix sizes,  
	./$< $(M_1) 1 > O3_$(M_1)_1$@				#compilation flags, and operations like multiplication and transpose
	./$< $(M_2) 1 > O3_$(M_2)_1$@
	./$(word 2,$^) $(M_1) 1 > O0_$(M_1)_1$@			
	./$(word 2,$^) $(M_2) 1 > O0_$(M_2)_1$@
	./$< $(M_1) 0 > O3_$(M_1)_0$@
	./$< $(M_2)$ 0 > O3_$(M_2)_0$@
	./$(word 2,$^) $(M_1) 0 > O0_$(M_1)_0$@
	./$(word 2,$^) $(M_2) 0 > O0_$(M_2)_0$@

blocking.graph:plot_blocking.gp blocking.txt
	gnuplot plot_blocking.gp



.PHONY:
clean:
	rm *.x *.o
