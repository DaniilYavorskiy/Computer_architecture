#!/bin/bash
echo -en "\033[31m" 
echo -e "\033[5;8H\033(0lqqqqqqqqqqk\033(B"
echo -e "\033(0\033[6;8Hx\033[6;19Hx\033(B"
echo -e "\033(0\033[7;8Hx\033[7;19Hx\033(B"
echo -e "\033(0\033[8;8Hx\033[8;19Hx\033(B"
echo -e "\033(0\033[9;8Hx\033[9;19Hx\033(B"
echo -e "\033(0\033[10;8Hx\033[10;19Hx\033(B"
echo -e "\033(0\033[11;8Hx\033[11;19Hx\033(B"
echo -e "\033(0\033[12;8Hx\033[12;19Hx\033(B"
echo -e "\033(0\033[13;8Hx\033[13;19Hx\033(B"
#echo -e "\033[H\E[2J"
let number=0x7F03060C18306000
let x=5
let y=10
for i in {64..1}; do
    j=$(($number >> ($i - 1) & 0x1));
    if (( $i % 8 == 0 ))
    then
        x=$(($x + 1))
        y=10
    else
        y=$(($y + 1))
    fi
    #echo $i $x $y
    if (($j == 0))
    then
        echo -en "\033[$x; $(($y * 1))H"
    else
        echo -en "\033[$x;$(($y * 1))H\033(0a\033(B"
    fi
done
echo -e "\033[14;8H\033(0mqqqqqqqqqqj\033(B"
