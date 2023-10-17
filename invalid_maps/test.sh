#!bin/bash

rm -rf *.txt
make -C ..

if [ -z $1 ]
then
	exit
fi

{ for invalid_map in "$1/"*
	do
	echo -n "$invalid_map: "
	output=$(../cub3D $invalid_map)
	if [ "$output" = "Error" ]
	then
		echo ✓
	else
		echo ×
		echo "$invalid_map:" >> error.txt
		cat $invalid_map >> error.txt
		echo >> error.txt
	fi
done }