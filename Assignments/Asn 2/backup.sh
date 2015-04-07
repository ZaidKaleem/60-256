#!/bin/bash
# Zaid Kaleem
# 103619897
# 60-256
# Assignment 2

for files in $*;
	do

	#case 1
	if [ $files != "-d" ]
	then
		gzip *.$files
		echo "Compressed $1 file(s)"
		echo "Compressed $2 file(s)"
	
	#case 3
	elif [ $1 -eq "-d" ] -a [ -d -eq "$DIRECTORY" ]
	then
		echo "Compressed $# $* file(s)"
		echo "Saved in `date +%Y-%m-%d` "
	
	#case 2
	else
	echo "Error"

	fi
done

# I tried to put the cases in proper numbering order
# but this way seemed more logical in terms of structure
# for the if statements