# Badly written makefile, needs to be run twice
# first time generates the graphviz input
# second time updates the png.
# After that a single run works unless the number of images change.

G=$(wildcard *.gv)
all: ${G:.gv=.png} vuln2

%.png: %.gv
	neato -Tpng -o $@ $<

$G: animate.awk steps
	awk -f animate.awk steps

clean:
	rm -f 1*.gv 1*.png

