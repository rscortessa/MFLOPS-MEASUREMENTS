vpath desviacion_estandar.cpp ../
FIXED_DEPS=desviacion_estandar.cpp
C_DEPS=PAPI_flops.c
LIB_DEPS=-lpapi
%.x : %.cpp $(FIXED_DEPS)
	$(CXX) $(C_DEPS) ../$(FIXED_DEPS) $< $(LIB_DEPS) -o $@
	./$@
.PHONY:
clean:
	rm  *.x
