#!bin/bash

rm -rf *.txt

{ for invalid_map in "$1/"*
	do
	echo -n "$invalid_map: "
	output=$(../cub3D $invalid_map)
	if [ "$output" = "Error" ]
	then
		echo ✓
	else
		echo ×
		echo "code $invalid_map" >> error.txt
	fi
done } &> log.txt