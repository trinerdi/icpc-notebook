alias t="basename \$(realpath .)" # Assumption: prints an alphanumeric string
b(){
	fl=-O2\ -fsanitize=address
	[ a"$1" = a-d ] && fl=-g && v=valgrind
	g++ -std=c++11 -lm -Wall -Wno-sign-compare -Wshadow $fl `t`.cpp -o `t`
	for i in `t`.in*; do echo $i:; $v ./`t` < $i; done
}
n(){
	mkdir "$1"
	cd "$1"
	cp -rn ../template.cpp "$1".cpp
}
