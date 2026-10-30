reset

set title "Cones and Spanning Forest (Kruskal 2)"
set xlabel "X"
set ylabel "Y"
set zlabel "Z"

set grid
set view 65,45
set ticslevel 0
set key outside
set xyplane at 0

set terminal pngcairo size 1400,1000 enhanced
set output "mst-grid.png"

# Convert edge separators for splot; original txt/mst-grid.txt stays unchanged.
system("awk 'NF == 0 {print \"\"; print \"\"; next} {print}' ../txt/mst-grid.txt > ../txt/mst-grid-3d.txt")

# clusters.txt: x y cluster_id; render all cluster points at z=0.
stats "../txt/clusters.txt" using 3 nooutput
maxCluster = int(STATS_max)
colors = "#2878B5 #E87430 #39A66A #aa0000 #adff2f #ff00ff #C49A28 #00ffff #ffff00 #663333 #993333 "



splot "../txt/cone-points.txt" using 1:2:3 \
      with lines lc rgb "#888888" lw 0.7 title "Cones", \
      "../txt/mst-grid-3d.txt" using 1:2:3 \
      with lines lc rgb "#D1493F" lw 0.8 title "Kruskal 2 Forest", \
      for [k=0:maxCluster] "../txt/clusters.txt" \
      using (int($3)==k ? $1 : 1/0):(int($3)==k ? $2 : 1/0):(0) \
      with points pt 7 ps 0.35 lc rgb word(colors, (k%11)+1) \
      title sprintf("Cluster %d", k)

unset output
