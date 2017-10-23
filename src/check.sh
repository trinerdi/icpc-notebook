IFS=
while read a; do
	# Doesn't really work in general (multiline comments are broken, ...), but works well enough
	printf "%s  %s\n" "$(echo "$a" | sed -re 's/\s*([^a-zA-Z_])\s*/\1/g;s/.*\*\/|\/[/*].*|^\s*|\s*$//g' | md5sum | head -c3)" "$a"
done
