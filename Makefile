
vpath %.cpp ./
FIXED_DEPS=Measure_code.c
LIB_DEPS=-lpapi -larmadillo 
%.x : %.cpp $(FIXED_DEPS)
	$(CXX) $(FIXED_DEPS) $< $(LIB_DEPS) -o $@
	./$@
.PHONY:
clean:
	rm *.x
