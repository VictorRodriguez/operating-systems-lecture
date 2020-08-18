#!/bin/bash
#C_NUMBER=$(cd linux; find . -type f | grep \\.c | wc -l);
#T_NUMBER=$(cd linux; find . -type f | grep \\.t | wc -l);
#H_NUMBER=$(cd linux; find . -type f | grep \\.h | wc -l);

if [ -f "directories.csv" ];
then
	rm directories.csv;
fi
cd linux;
ls -d */ | while read line
do
	cd $line;
	find . -type f > temp.txt;
	NUMBER=$(cat temp.txt | wc -l);
	C_NUMBER=$(cat temp.txt | grep \\.c |  wc -l);
	H_NUMBER=$(cat temp.txt | grep \\.h |  wc -l);
	#PL_NUMBER=$(cd $line; find . -type f | grep \\.pl |  wc -l);
	#README=$(cd $line; find . -type f | grep README |  wc -l);
	#KCONFIG=$(cd $line; find . -type f | grep Kconfig |  wc -l);
	#KBUILD=$(cd $line; find . -type f | grep Kbuild |  wc -l);
	echo $line,$NUMBER,$C_NUMBER,$H_NUMBER >> ../../directories.csv;
	rm temp.txt;
	cd ..;
done

cd ..;

if [ ! -f "Plotter.class" ];
then
   javac Plotter.java
fi
java Plotter
