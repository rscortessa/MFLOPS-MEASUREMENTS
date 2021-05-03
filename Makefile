
MATRIX_SIZE=0
OPTIM=0
TO_MEASURE=0

O$(MATRIX_SIZE)_$(OPTIM)_$(TO_MEASURE)blocking: Performance_blocking.cpp #Regla de compilación para archivo individual
	$(CXX) $(FIXED_DEPS) $< $(LIB_DEPS) -O$(OPTIM) -o $@.x  
	./ $@.x $(MATRIX_SIZE) $(TO_MEASURE) > $@.txt
	
all: blocking.graph 

FIXED_DEPS=Multiplicaciones.cpp Transpuestas.cpp 
LIB_DEPS=-lpapi -larmadillo


%0.x : %.cpp $(FIXED_DEPS)	
	$(CXX) $(FIXED_DEPS) $< $(LIB_DEPS) -o $@   
		
%3.x : %.cpp $(FIXED_DEPS)	
	$(CXX) $(FIXED_DEPS) $< $(LIB_DEPS) -O3 -o $@ 

blocking.txt: Performance_blocking3.x Performance_blocking0.x  #this creates 4 txt files 
	./$< 2048 1 > O3_2048_1$@
	./$< 4096 1 > O3_4096_1$@
	./$(word 2,$^) 2048 1 > O0-2048_1$@
	./$(word 2,$^) 4096 1 > O0-4096_1$@
	./$< 2048 0 > O3_2048$@
	./$< 4096 0 > O3_4096$@
	./$(word 2,$^) 2048 0 > O0_2048_0$@
	./$(word 2,$^) 4096 0 > O0_4096_0$@
	
blocking.graph:plot_blocking.gp blocking_trans.txt blocking_mult.txt
	gnuplot plot_blocking.gp



.PHONY:
clean:
	rm *.x *.o 
