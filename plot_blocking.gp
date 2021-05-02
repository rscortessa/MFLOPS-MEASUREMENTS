set logscale x 2
set xlabel "Tamaño del bloque N_b"; set ylabel "Mflops/Mflops_{max}"
set key left top
set term pdf
do for [k in "0 1"]{
do for [j in "2048 4096"]{
set out "blocking-data-".j.".pdf"
plot for[i in "0 3"]  "O".i."".j."".k."blocking.txt" u 7:1 w lp title "O".i."
}
}
