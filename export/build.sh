(
	echo "\\input head"
	base=../src
	while read a; do
		echo "\\header{$a}"
		python3 totex.py < "$base"/"$a"
	done

	echo "\\bye"
) > out.tex < files
xetex out
