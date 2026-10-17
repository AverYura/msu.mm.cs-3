set title "Cones and 2-Gauss points"
set xlabel "X"
set ylabel "Y"
set zlabel "Z"

set grid
set view 65, 45
set ticslevel 0
set key outside
set terminal pngcairo size 1400,1000
set output "2-gauss-points.png"

splot "cone-points.txt" using 1:2:3 with lines lc rgb "gray" title "Cones", \
		"gauss-points.txt" using 1:2:(0) \
		with points pt 7 ps 0.4 lc rgb "red" title "Gaussian-points"
