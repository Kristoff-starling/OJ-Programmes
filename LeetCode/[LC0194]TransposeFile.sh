#!/bin/bash

ncol=`head -n1 file.txt | wc -w`

for i in `seq 1 $ncol`
do
	echo `cat file.txt | awk '{print $'$i'}' | paste -d\ `
done