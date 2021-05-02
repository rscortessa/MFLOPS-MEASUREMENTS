
FIXED_DEPS=Multiplicaciones.cpp
LIB_DEPS=-lpapi -larmadillo


%.x : %.cpp $(FIXED_DEPS)
	for n in 0 3  ; do \
		$(CXX) $(FIXED_DEPS) $< $(LIB_DEPS) -O$$n -o $@O$$n ; \
	done

blocking_mult:Performance_blocking.x
	for m in 20 40 ; do \
		for n in 0 3 ; do \
			./$<O$$n $$m $$1  > $@O$$n-$$m.data ; \
		done ; \
	done

blocking_trans:Performance_blocking.x
	for m in 2048 4096 ; do \
		for n in 0 3 ; do \
			./$<O$$n $$m $$0  > $@O$$n-$$m.data ; \
		done ; \
	done

blocking.graph:plot_blocking.gp Performance_blocking.x
	gnuplot plot_blocking.gp


.PHONY:
clean:
	rm *.x *.o 
