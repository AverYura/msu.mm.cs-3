
set title "Cones and Clusters"
set xlabel "X"
set ylabel "Y"
set zlabel "Z"

set grid
set view 65, 45
set ticslevel 0
set key outside

set terminal pngcairo size 1400,1000
set output "cones-clusters.png"

splot "txt/cone-points.txt" using 1:2:3 \
      with lines lc rgb "gray" title "Cones", \
      "txt/clusters.txt" using ($3==0 ? $1 : 1/0):($3==0 ? $2 : 1/0):(0) \
      with points pt 7 ps 0.5 lc rgb "blue" title "Cluster 0", \
      "txt/clusters.txt" using ($3==1 ? $1 : 1/0):($3==1 ? $2 : 1/0):(0) \
      with points pt 7 ps 0.5 lc rgb "cyan" title "Cluster 1"

unset output

