#! /bin/bash

chicken=("fried" "yangnyeom" "ganjang")
test1=($(ls))

echo ${chicken[@]}
echo ${#chicken[@]}
echo $$
echo $0
echo $1
echo $#

n1=`expr \( 5 + 6 \) \* 8`
echo $n1
