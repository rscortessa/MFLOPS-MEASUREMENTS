set logscale x 2
set xlabel "Tamaño del bloque N_b"; set ylabel "Mflops/Mflops_{max}"
set key left top
set term pdf
set out "file1.pdf"
set title "Mflops vs Nb"
plot "Performance_blocking0.txt" u 7:1 w lp title "O0", "Performance_blocking3.txt" u 7:1 w lp title "O3"
unset output
set output "file2.pdf"
set title "Time vs Nb"
plot "Performance_blocking0.txt" u 7:5 w lp title "O0", "Performance_blocking3.txt" u 7:5 w lp title "O3"
unset output
unset terminal
