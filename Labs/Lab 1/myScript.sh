#!/bin/bash 
echo Welcome to shell scripting.
myfirstvar=hello
echo $myfirstvar
myfirstvar=($myfirstvar there)
echo $myfirstvar
echo "Today is ‘date‘"
echo The program name is: $0
echo "The program name is: $0"
echo ’The program name is: $0’
echo The first argument is: $1
echo The second argument is: $2
echo All the arguments are: $*
echo The total number of argument is: $#
echo "Today is $(date)"
bash -xv your_csh_script
