set terminal pngcairo size 800,600 enhanced font 'Verdana,10'
set output 'f1_score.png'
set title 'F1 Score'
set xlabel 'Niveau de Gris'
set ylabel 'F1 Score'
set grid
plot 'roc_curve.dat' using 1:4 with lines title 'F1 Score' lw 2 lc rgb 'blue'