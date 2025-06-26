set terminal pngcairo enhanced font "Arial,12" size 800,600
set output "bpp_vs_psnr.png"

set title "bpp vs. PSNR pour différents N"
set xlabel "PSNR (dB)"
set ylabel "bpp (bits par pixel)"
set grid
set key outside

set datafile separator whitespace

# Tracer bpp en fonction de PSNR, regroupé par N
plot for [n=1:6] "data.txt" using 4:3:($1 == n ? $4 : 1/0) with linespoints title sprintf("N=%d", n)
