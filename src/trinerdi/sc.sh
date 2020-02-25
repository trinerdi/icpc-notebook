# Usage: e [-d] test1.in … testN.in
# Compiles the solution (if it has changed since the last time) and runs it on test1.in … testN.in.
# If no tests are given, runs the solution on all files whose name contains 'in'.
# If -d is given, compiles the solution with debug flags and runs it with valgrind.
e(){
	t=$(basename `pwd`)
	if [ "$1" = -d ]; then fl=-g; v=valgrind; d=$t-debug; shift
	else fl=-O2\ -fsanitize=address; v=; d=$t; fi
	if [ $# = 0 ]; then args=*in*
	else args="$@"; fi
	[ $t.cpp -nt $d ] && ( g++ -std=c++14 -lm -Wall -Wextra -Wno-sign-compare -Wshadow -DLOCAL $fl $t.cpp -o $d || return )
	for i in $args; do echo $i:; $v ./$d < $i; done
}
create(){
	for i in {a..z}; do  # Change z as needed
		mkdir "$i" && cd "$i" || continue
		cp -n ../template.cpp "$i".cpp; touch "$i".in1; cd ..
	done
}
