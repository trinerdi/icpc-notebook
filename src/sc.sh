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
