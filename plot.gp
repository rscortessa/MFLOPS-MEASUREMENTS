set logscale x 2
set xlabel "Tamaño del bloque N_b"; set ylabel "Mflops/Mflops_{max}"
set key left top
set term pdf
set out "file.pdf"
plot "Performance_blocking0.txt" u 7:1 w lp title "O0"
plot "Performance_blocking3.txt" u 7:1 w lp title "O3"

