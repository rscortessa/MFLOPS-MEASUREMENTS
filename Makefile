
FIXED_DEPS=Multiplicaciones.cpp
LIB_DEPS=-lpapi -larmadillo


%.x : %.cpp $(FIXED_DEPS)
	for n in 0 3  ; do \
		$(CXX) $(FIXED_DEPS) $< $(LIB_DEPS) -O$$n -o $@O$$n ; \
	done

blocking.data:Performance_blocking.x
	for m in 20 40 ; do \
		for n in 0 3 ; do \
			./$<O$$n $$m  > $@O$$n-$$m ; \
		done ; \
	done
blocking.graph:plot_blocking.gp Performance_blocking.x
	gnuplot plot_blocking.gp

.PHONY:
clean:
	rm *.x *.o 
