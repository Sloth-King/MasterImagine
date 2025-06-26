set terminal pngcairo size 800,600 enhanced font 'Verdana,10'
set output 'roc_curve.png'
set title 'ROC Curve'
set ylabel 'TPR'
set xlabel 'FPR'
set grid
plot 'roc_curve.dat' using 2:3 with lines title 'ROC Curve' lw 2 lc rgb 'red'