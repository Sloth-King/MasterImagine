# File: plot_results.gnuplot

set terminal pngcairo size 800,600 enhanced font 'Arial,12'
set output 'results.png'

set title "Valeurs TP, FP, TN, FN"
set xlabel "Niveau de gris (NDG)"
set ylabel "Valeurs"

plot 'results.dat' using 1:2 with lines lc rgb "blue" title "True Positives", \
    'results.dat' using 1:3 with lines lc rgb "green" title "True Negatives", \
    'results.dat' using 1:4 with lines lc rgb "red" title "False Positives", \
    'results.dat' using 1:5 with lines lc rgb "orange" title "False Negatives"
