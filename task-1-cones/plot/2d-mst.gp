reset

set title "Kruskal 2: Spanning Forest and Clusters (2D)"
set xlabel "X"
set ylabel "Y"

set size ratio -1
set grid
set key outside

set terminal pngcairo size 1400,1000 enhanced
set output "mst-grid-2d.png"

# clusters.txt: x y cluster_id
stats "../txt/clusters.txt" using 3 nooutput
maxCluster = int(STATS_max)
colors = "#2878B5 #E87430 #39A66A #aa0000 #adff2f #ff00ff #C49A28 #00ffff #ffff00 #663333 #993333 "

plot "../txt/mst-grid.txt" using 1:2 \
     with lines lw 0.7 lc rgb "#444444" title "Kruskal 2 Forest", \
     for [k=0:maxCluster] "../txt/clusters.txt" \
     using (int($3)==k ? $1 : 1/0):(int($3)==k ? $2 : 1/0) \
     with points pt 7 ps 0.45 lc rgb word(colors, (k%11)+1) \
     title sprintf("Cluster %d", k)

unset output
