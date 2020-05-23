base_dir="`pwd`/`dirname $0`/../"
make_file="$base_dir/Makefile"
build_folder="build/objects"
profile_folder="gui/performance-analyzer/assets"
output_folder="gui/logic-analyzer/assets"
executable_folder="build"
pushd $base_dir

function pf () { printf "$1" >> Makefile; }

echo "# Makefile auto generated using custom generator" > "$make_file" # Initialize Makefile

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

pf "\nCFLAGS=-c -Wextra -std=c++17 -O\$(OPT) -g"
pf "\nCC=g++"
pf "\nINC="
while read -r folder; do
	pf " -I$folder\\"
	pf "\n"
done < hpp-sorted-dir.list
pf "\n.PHONY: all clean cleanall check-directory make-opt check-opt-value"
pf "\n"
pf "\nall: check-directory"
pf "\n"

pf "\ncheck-directory:"
pf "\n\t@[ -d \"$build_folder\" ] || mkdir -p $build_folder"
pf "\n\t@[ -d \"$executable_folder\" ] || mkdir -p $executable_folder"
pf "\n\t@make check-opt-value OPT=\$(OPT)"
pf "\n"

pf "\ncheck-opt-value:"
pf "\n\t@[ \"\$(OPT)\" == \"\" ] && make make-opt OPT=0 || make make-opt OPT=\$(OPT)\n"

pf "\nmake-opt:"
pf "\n\t@if [ ! -f \"$executable_folder/.out-\$(OPT)\" ]; then \\"
pf "\n\t\trm -rf $executable_folder/*; \\"
pf "\n\t\tmkdir -p $build_folder; \\"
pf "\n\t\ttouch $executable_folder/.out-\$(OPT); \\"
pf "\n\tfi"
pf "\n\t@make $executable_folder/test-out-\$(OPT) OPT=\$(OPT)"
pf "\n\t@make $executable_folder/prj-out-\$(OPT) OPT=\$(OPT)"
pf "\n"

# test executable
pf "\n$executable_folder/test-out-\$(OPT):"
while read -r file_name; do
	[[ "$file_name" != "prj-"* ]] && pf " $build_folder/$file_name.o"
done < cpp-file.list
pf "\n\t\$(CC) \$(INC) -o \$@ \$^"
pf "\n"

# project executable
pf "\n$executable_folder/prj-out-\$(OPT):"
while read -r file_name; do
	[[ "$file_name" != "test-"* ]] && pf " $build_folder/$file_name.o"
done < cpp-file.list
pf "\n\t\$(CC) \$(INC) -o \$@ \$^"
pf "\n"

echo "Adding headers to dependency list"
while read -r cpp_full_path; do
	echo "Parsing $cpp_full_path"

	cpp_file_name="`echo $(basename $cpp_full_path) | awk -F '.' '{print $1}'`"
	cpp_dir_name="`dirname $cpp_full_path`"
	pf "\n$build_folder/$cpp_file_name.o: $cpp_dir_name/$cpp_file_name.cpp "

	# find all the included libraries in the cpp file
	includes=`grep "^#include" "$cpp_full_path" | grep -v "<" | awk -F '"' '{print $2}'`
	for hpp_file in ${includes[@]}; do
		pf "`find ./ -name $hpp_file` "
	done
	# find all the included libraries in the hpp file
	hpp_full_path="`find ./ -name "$cpp_file_name.hpp"`"
	# if the hpp file exists, look for dependencies in the hpp file as well
	if [ "$hpp_full_path" != "" ]; then
		hpp_dep=`grep "^#include" "$hpp_full_path" | grep -v "<" | awk -F '"' '{print $2}' | awk -F '.hpp' '{print $1}'`
		for hpp_file in ${hpp_dep[@]}; do
			# echo $hpp_file); exit
			cpp_dep=`find ./ -name "$(basename $hpp_file).cpp"`
			[ "$cpp_dep" != "" ] && echo $build_folder/$hpp_file.o && pf "$build_folder/$hpp_file.o "
		done
	else
		echo "No headers in $cpp_file_name.hpp"
	fi

	pf "\n\t\$(CC) \$(INC) \$(CFLAGS) \$< -o \$@\n"
done < cpp-full.list

pf "\nclean:\n\trm -rf $executable_folder/*\n"

pf "\ncleanall:\n\trm -rf $executable_folder/* $profile_folder/* $output_folder/*"

rm *.list

popd