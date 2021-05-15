set style data linespoints
set logscale x 2
set xlabel "Tamaño del bloque N_b"; set ylabel "Mflops/Mflops_{max}"
set key left top
set term pdf
show style data
set out "file1.pdf"
set title "Mflops vs Nb"
show bars
plot "aux0.txt" u 7:(6.67*$1):(6.67*$2) w yerrorbars linecolor "black" pt 7 ps 0.4 notitle,\
"aux0.txt" u 7:(6.67*$1):(6.67*$2) w lines title "O0" lt rgb "navy", \
"aux3.txt" u 7:(6.67*1):(6.67*$2) with yerrorbars linecolor "black" pt 7 ps 0.4 notitle, \
plot "aux0.txt" u 7:1:2 w yerrorbars linecolor "black" pt 7 ps 0.4 notitle,\
"aux0.txt" u 7:(6.67*$1):(6.67*$2) w lines title "O0" lt rgb "navy", \
"aux3.txt" u 7:(6.67*$1):(6.67*$2) with yerrorbars linecolor "black" pt 7 ps 0.4 notitle, \
>>>>>>> d72dc7418d228bb65cb34bf895a41d2de974cb0d
"aux3.txt" u 7:(6.67*$1):(6.67*$2) with lines title "O3" lt rgb "red" 
unset output
set output "file2.pdf"
set xlabel "Tamaño del bloque N_b"; set ylabel "tiempo(s)"
set title "Time vs Nb"
plot "aux0.txt" u 7:5:6 w yerrorbars linecolor "black" pt 7 ps 0.4 notitle,\
"aux0.txt" u 7:5:6 w lines title "O0" lt rgb "navy", \
"aux3.txt" u 7:5:6 with yerrorbars linecolor "black" pt 7 ps 0.4 notitle, \
"aux3.txt" u 7:5:6 with lines title "O3" lt rgb "red" 
unset output
unset terminal
