name(){
	basename `realpath .`
}

b(){
	flags=-O2\ -fsanitize=address
	[ a"$1" = a-d ] && flags=-g

	f=`name`
	g++ -std=c++11 -lm -Wall -Wno-sign-compare -Wshadow $flags "$f".cpp -o "$f"
}

c(){
	f=`name`
	cmd=
	[ a"$1" = a-d ] && cmd=valgrind
	$cmd ./"$f"
}

run(){
	b "$@" && c "$@"
}

e(){
	f=`name`
	b "$@"
	for i in $f.in*; do
		echo $i:
		c "$@" < $i
	done
}
