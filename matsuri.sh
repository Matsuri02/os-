#!/bin/bash
cd $1
for files in `ls -l | grep ^[^d] | awk '{print $9}'`
do
       final=${files##*.}
       filename=${files%.*}
       filename=${filename/-*-*-*-*-*-*}
       time="-`date +%Y-%m-%d-%H-%M-%S`"
       file=$filename$time
       mv $files $file.$final 
done
