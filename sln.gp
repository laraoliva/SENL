set terminal pdf enhanced


set output "snl.pdf"


set xlabel "Iterações"
set ylabel "Norma de y"
set title "SNL-solução: 0.5, 0.0, -0.52"
set grid



plot "norma1.dat" ps 2 lc 4 t "vetor tentativa: 0.1, 0.1,-0.1" with lines,"norma2.dat" ps 2 lc 10 t "vetor tentativa: 1.0,2.0,3.0" with lines,"norma3.dat" ps 2 lc 15 t "vetor tentativa: 0.3, 0.5,-1.0" with lines



#############################################################################################################################################

set output
