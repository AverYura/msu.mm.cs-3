set title "Gaussian Clusters"
set xlabel "X"
set ylabel "Y"

set size ratio -1
set grid

set terminal pngcairo size 1400,1000
set output "clusters.png"

# Цвет точки определяется номером кластера
set palette defined (0 "blue", 1 "red", 2 "green", 3 "orange", 4 "violet", 5 "cyan")

set cblabel "Cluster ID"

plot "txt/clusters.txt" using 1:2:3 with points \
     pointtype 7 pointsize 0.5 palette \
     title "Clusters"

