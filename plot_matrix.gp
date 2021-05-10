set style data linespoints
set logscale x 2
set xlabel "Tamaño de lado matriz (N)"; set ylabel "Mflops/Mflops_{max}"
set key left top
set term pdf
show style data
set out "file1.pdf"
set title "Mflops vs N"
show bars
plot "aux0.txt" u 7:1:2 w yerrorbars linecolor "black" pt 7 ps 0.4 notitle,\
"aux0.txt" u 7:1:2 w lines title "O0" lt rgb "navy", \
"aux3.txt" u 7:1:2 with yerrorbars linecolor "black" pt 7 ps 0.4 notitle, \
"aux3.txt" u 7:1:2 with lines title "O3" lt rgb "red" 
unset output
set output "file2.pdf"
set xlabel "Tamaño de lado matriz (N)"; set ylabel "tiempo(s)"
set title "Time vs N"
plot "aux0.txt" u 7:5:6 w yerrorbars linecolor "black" pt 7 ps 0.4 notitle,\
"aux0.txt" u 7:5:6 w lines title "O0" lt rgb "navy", \
"aux3.txt" u 7:5:6 with yerrorbars linecolor "black" pt 7 ps 0.4 notitle, \
"aux3.txt" u 7:5:6 with lines title "O3" lt rgb "red" 
unset output
unset terminal
