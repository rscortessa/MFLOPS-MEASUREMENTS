
MATRIX_SIZE=0
OPTIM=0
TO_MEASURE=0

Performance_blocking$(MATRIX_SIZE)_$(OPTIM)_$(TO_MEASURE): Performance_blocking.cpp #Regla de compilación para archivo individual
	$(CXX) $(FIXED_DEPS) $< $(LIB_DEPS) -O$(OPTIM) -o $@.x  
	./ $@.x $(MATRIX_SIZE) $(TO_MEASURE) > $@.txt
	
all: blocking.graph 

FIXED_DEPS=Multiplicaciones.cpp Transpuestas.cpp 
LIB_DEPS=-lpapi -larmadillo


%0.x : %.cpp $(FIXED_DEPS)	
	$(CXX) $(FIXED_DEPS) $< $(LIB_DEPS) -o $@   
		
%3.x : %.cpp $(FIXED_DEPS)	
	$(CXX) $(FIXED_DEPS) $< $(LIB_DEPS) -O3 -o $@ 

blocking_mult.txt: Performance_blocking3.x Performance_blocking0.x  #this creates 4 txt files 
	./$< 2048 1 > O3-2048$@
	./$< 4096 1 > O3-4096$@
	./$(word 2,$^) 2048 1 > O0-2048$@
	./$(word 2,$^) 4096 1 > O0-4096$@

blocking_trans.txt: Performance_blocking3.x Performance_blocking0.x 
	./$< 2048 0> O3-2048$@
	./$< 4096 0> O3-4096$@
	./$(word 2,$^) 2048 0 > O0-2048$@
	./$(word 2,$^) 4096 0 > O0-4096$@
	
blocking.graph:plot_blocking.gp blocking_trans.txt blocking_mult.txt
	gnuplot plot_blocking.gp



.PHONY:
clean:
	rm *.x *.o 
