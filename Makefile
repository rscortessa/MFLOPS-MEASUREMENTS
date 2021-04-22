vpath %.cpp ./Multiplicaciones
vpath %.cpp ./Transpuesta
FIXED_DEPS=desviacion_estandar.cpp Measure_code.c
LIB_DEPS=-lpapi
%.x : %.cpp $(FIXED_DEPS)
	$(CXX) $(FIXED_DEPS) $< $(LIB_DEPS) -o $@
	./$@

.PHONY:
clean:
	rm *.x
