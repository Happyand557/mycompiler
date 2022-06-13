#!/bin/bash

for ((i = 84; i <= 99; i ++))
do 
	str="s/${i}_/0${i}_/"
	eval rename '$str' *
done
