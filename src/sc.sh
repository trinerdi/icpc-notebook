name(){
	basename `realpath .`
}
b(){
	flags=-O2\ -fsanitize=address
	[ a"$1" = a-d ] && flags=-g
	g++ -std=c++11 -lm -Wall -Wno-sign-compare -Wshadow $flags "$(name)".cpp -o "$(name)"
}
c(){
	`[ a"$1" = a-d ] && echo valgrind` ./"$(name)"
}
run(){
	b "$@" && c "$@"
}
e(){
	b "$@"
	for i in "$(name)".in*; do echo $i:; c "$@" < $i; done
}
check(){
	{ IFS=
	while read -r a; do
		# Doesn't really work in general (multiline comments are broken, ...), but works well enough
		printf "%s  %s\n" "$(echo "$a" | sed -re 's/\s+|\/\/.*//g' | md5sum | head -c3)" "$a"
	done } < "$(name)".cpp
}
