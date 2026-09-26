set title "Cone"
set xlabel "X"
set ylabel "Y"
set zlabel "Z"

set grid
set view 60, 30

splot "cone-points.txt" using 1:2:3 with points pointtype 7 pointsize 0.3
