set xlabel "poids0"
set ylabel "poids1"
set zlabel "poids2"
set title "Representation 3D des poids du graphe"
splot './/mescoordsDom.txt' title "Domines" lt rgb "black" lw 2 pt 5, './/mescoordsFront.txt' t "Frontieres" lt rgb "violet" lw 10 pt 10
