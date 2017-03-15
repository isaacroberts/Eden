#!/bin/bash

filename="_.h"
dir="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

cd $dir

echo > $filename
echo "#ifndef ALL_H" >> $filename
echo "#define ALL_H" >> $filename
echo >> $filename
echo "//The superincluder " >> $filename
echo >> $filename
echo "#include \"main.h\"" >> $filename
folder=( Biome Gui Matter Ref World "Gui/Popup")
for i in 0 1 2 3 4 5
do
	echo "#include \""${folder[i]}"/"$filename"\"" >> $filename
	cd $dir"/"${folder[i]}
#	echo ${folder[i]}
	def=${folder[i]}
	def=${def^^} 
	def=${def/"/"/"_"}
	echo "#ifndef ALL_"$def"_H" > $filename
	echo "#define ALL_"$def"_H" >> $filename	
	echo "//includes everything in folder" >> $filename
	echo "" >> $filename
	for file in ./*
	do
		file=${file:2}
		if [ $file != $filename ]
		then
			if [ ${file: -2}  == ".h" ]
			then
				echo "#include \""$file"\"" >> $filename
			fi
		fi
	done
	#check for any contained folders
	for ((m=i+1; m<=5; m++))
	do
		if [[ ${folder[m]} == ${folder[i]}* ]]
		then #true if m is a subfolder of i
			subfolder=${folder[m]}
			subfolder=${subfolder/${folder[i]}/""}
			subfolder=${subfolder/"/"/""}
			echo "#include \""$subfolder"/"$filename"\"" >> $filename
			#includes the all.h file of subfolder m
		fi
	done
	echo "" >> $filename
	echo "#endif" >> $filename
	cd $dir
done

echo >> $filename
echo "#endif " >> $filename


