#!/bin/sh
(
	printf '\\input head\n'
	base=../src
	while read a; do
		printf '\\header{%s}\n' "$a"
		python3 to_tex.py < "$base"/"$a"
	done

	printf '\\bye\n'
) > out.tex < files
xetex out
