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
	if [ -z $(../cub3D $invalid_map 2>&1 | grep "Error") ]
	then
		echo ×
		echo "$invalid_map:" >> error.txt
		echo >> error.txt
		cat $invalid_map | grep -m 1 -B 1000 '1111111' >> error.txt
		echo >> error.txt
	else
		echo ✓
	fi
done }