#!/bin/bash
set term png
set output "chart.png"
set ylabel "Temperature[Celsius]"
set xlabel "Time[Seconds]"
plot "Cooling.pt" u 1:2 t "Tb" w lines lc 1, "Cooling.pt" u 1:3 t "Tw" w lines lc 5
set output


