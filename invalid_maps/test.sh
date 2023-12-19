#!bin/bash

rm -rf *.txt
make -C ..


for invalid_map in *
	do
	echo -n "$invalid_map: "
	output="$(../cub3D $invalid_map 2>&1)"
	if [ -z "$(echo $output | grep "Error")" ]
	then
		echo ×
		echo "$invalid_map:" >> error.txt
		echo >> error.txt
		cat $invalid_map >> error.txt
		echo >> error.txt
	else
		echo "✓ ${output#*$'\n'}"
	fi
done