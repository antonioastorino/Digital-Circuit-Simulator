base_dir="`pwd`/`dirname $0`/../"
head_file="$base_dir/doc/head.md"
readme_file="$base_dir/README.md"
search_path="$base_dir/include"
parsed_md="paresed_md.tmp"

# create a readme file starting with a saved header
cp "$head_file" "$readme_file"
echo ""                        >> "$readme_file"
echo "---"                     >> "$readme_file"
echo "# Component description" >> "$readme_file"
echo ""                        >> "$readme_file"
touch "$parsed_md"

uncommented_line=""
pinout_found=0
diagram_found=0
table_found=0


function parse_comments() {
	while read -r l; do
		remove_comment_marker "$l"
		# echo "$uncommented_line"
		if `echo "$uncommented_line" | grep -q "^@class "`; then
			class_name=`echo "$uncommented_line" | sed 's/@class\ //'`
			echo "Class $class_name found"
			echo "## Class $class_name" >> "$parsed_md"
			echo ""                     >> "$parsed_md"
		elif `echo "$uncommented_line" | grep -q "^@struct "`; then
			struct_name=`echo "$uncommented_line" | sed 's/@struct\ //'`
			echo "Struct $struct_name found"
			echo "## Struct $struct_name" >> "$parsed_md"
			echo ""                      >> "$parsed_md"
		elif `echo "$uncommented_line" | grep -q '^@pinout$'`; then
			pinout_begin=`grep -n '@pinout' "$hpp_file" | head -n1 | cut -f1 -d:`
			pinout_end=`grep -n '@end_pinout' "$hpp_file" | head -n1 | cut -f1 -d:`
			if (( $pinout_begin < $pinout_end )); then
				pinout_found=1
				echo "Pinout block found"
				echo "#### Pinout"  >> "$parsed_md"						
				echo '```'         >> "$parsed_md" # start code block
			fi
		elif `echo "$uncommented_line" | grep -q '^@end_pinout$'`; then
			if (( $pinout_found == 1 )); then
				echo '```' >> "$parsed_md" # end code block
				echo ""    >> "$parsed_md"
			fi
		elif `echo "$uncommented_line" | grep -q '^@diagram$'`; then
      diagram_begin=`grep -n '@diagram' "$hpp_file" | head -n1 | cut -f1 -d:`
			diagram_end=`grep -n '@end_diagram' "$hpp_file" | head -n1 | cut -f1 -d:`
			if (( $diagram_begin < $diagram_end )); then
        diagram_found=1
        echo "Diagram block found"
        echo "#### Time diagram" >> "$parsed_md"							
        echo '```'              >> "$parsed_md" # start code block
			fi
		elif `echo "$uncommented_line" | grep -q '^@end_diagram$'`; then
			if (( $diagram_found == 1 )); then
				echo '```' >> "$parsed_md" # end code block
				echo ""    >> "$parsed_md"
			fi
    		elif `echo "$uncommented_line" | grep -q '^@table$'`; then
      table_begin=`grep -n '@table' "$hpp_file" | head -n1 | cut -f1 -d:`
			table_end=`grep -n '@end_table' "$hpp_file" | head -n1 | cut -f1 -d:`
			if (( $table_begin < $table_end )); then
        table_found=1
        echo "table block found"
        echo "#### Table"   >> "$parsed_md"				
        echo ""            >> "$parsed_md"
			fi
		elif `echo "$uncommented_line" | grep -q '^@end_table$'`; then
			if (( $table_found == 1 )); then
				echo ""    >> "$parsed_md"
			fi
		else
			echo "$uncommented_line" >> "$parsed_md"
		fi
	done < "$1"
}

function remove_comment_marker() {
	uncommented_line=`printf "$1" | sed 's/^\/\*\*//g' | sed 's/\*\/$//' | sed 's/^\*\ //' | sed 's/^\*//'`
}

# look for all .hpp files in seach_path
hpp_file_list=`find "$search_path" \( -name "*.hpp" -o -name "*.h" \) | sort`
for hpp_file in ${hpp_file_list[@]}; do
	# keep only the files which contain documentation
	if grep -q '^/\*\*' "$hpp_file" && grep -q '^\ \*/$' "$hpp_file" ; then
		pinout_foud=0 # reset variable that says if a valid pinout block exists
		diagram_found=0
    table_found=0
    comment_begin=`grep -n '^/\*\*' "$hpp_file" | head -n1 | cut -f1 -d:`
		comment_end=`grep -n '^\ \*/$' "$hpp_file" | head -n1 | cut -f1 -d:`
		sed -n "${comment_begin},${comment_end}p;${comment_end}p" "$hpp_file" > comment_file.tmp
		parse_comments "comment_file.tmp"
	fi
done

cat "$parsed_md" >> "$readme_file"
rm -rf comment_file.tmp "$parsed_md"