
reset

set title "Distribution of MST / Forest Edge Lengths"
set xlabel "Edge length"
set ylabel "Number of edges"

set grid
set key top right
set xrange [0:*]
set yrange [0:*]

bin_width = 0.001
bin(x) = bin_width * floor(x/bin_width) + bin_width/2.0

set boxwidth bin_width
set style fill transparent solid 0.45 noborder

set terminal pngcairo size 1400,900 enhanced
set output "histogram.png"

plot "../txt/lengths-grid.txt" using (bin($1)):(1.0) \
     smooth frequency with boxes \
     lc rgb "blue" title "Kruskal 2 (Forest)"

unset output

