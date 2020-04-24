echo "# Makefile auto generated using custom generator" > Makefile # Initialize Makefile

function pf () { printf "$1" >> Makefile; }

pf "\n"
pf "CFLAGS=-c -Wall -std=c++11\n"
pf "CC=g++\n"

# Find all the directories containing header files
cat /dev/null > hpp-dir.list       # dir only
cat /dev/null > hpp-file.list      # file name only
cat /dev/null > hpp-full.list      # full path
for f in `find ./ -name "*hpp"`; do
	echo "$f" >> hpp-full.list
	echo "`basename $f | awk -F '.' '{print $1}'`" >> hpp-file.list
	echo `dirname $f` >> hpp-dir.list
done
# Remove duplicates from directory list
sort hpp-dir.list | uniq > hpp-sorted-dir.list

cat /dev/null > cpp-file.list      # file name only
cat /dev/null > cpp-full.list      # full path
for f in `find ./ -name "*cpp"`; do
	echo "$f" >> cpp-full.list
	echo "`basename $f | awk -F '.' '{print $1}'`" >> cpp-file.list
done

pf "INC="
while read -r folder; do
	pf " -I$folder\\"
	pf "\n"
done < hpp-sorted-dir.list
pf "\n"

pf "all: DCS.out\n"

pf "\nDCS.out:"
while read -r file_name; do
	pf " build/$file_name.o"
done < cpp-file.list
	pf "\n\t\$(CC) \$(INC) -o \$@"
while read -r file_name; do
	pf " build/$file_name.o"
done < cpp-file.list

pf "\n"

while read -r cpp_full_path; do
	cat /dev/null > hpp-file.list # dependency list
	echo "Parsing $cpp_full_path"

	cpp_file_name="`echo $(basename $cpp_full_path) | awk -F '.' '{print $1}'`"
	cpp_dir_name="`dirname $cpp_full_path`"
	pf "\nbuild/$cpp_file_name.o: $cpp_dir_name/$cpp_file_name.cpp "

	echo "Adding headers to dependency list"
	#find all the included libraries in the cpp file
	grep "#include" "$cpp_full_path" | awk -F '"' '{print $2}' | tee hpp-file.list
	#find all the included libraries in the hpp file
	hpp_full_path="`find ./ -name "$cpp_file_name.hpp"`"
	# if the hpp file exists, look for dependencies in the hpp file as well
	if [ "$hpp_full_path" != "" ]; then
		grep "#include" "$hpp_full_path" | awk -F '"' '{print $2}' | tee -a hpp-file.list
	else
		echo "No headers in $cpp_file_name.hpp"
	fi
	
	# [ "`sort hpp-file.list | uniq -c | head -1`" != ""] && echo "Warning"

	sort hpp-file.list | uniq -c | head -1

	while read -r hpp; do
		pf "`find ./ -name $hpp` "
	done < hpp-file.list

	pf "\n"
	pf "\t\$(CC) \$(INC) \$(CFLAGS) \$< -o \$@\n"
	# pf "\n $file_name.o: "
done < cpp-full.list

pf "\nclean:\n\trm -f build/*"

rm *.list