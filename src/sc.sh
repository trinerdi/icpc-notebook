name(){
	basename `realpath .`
}

b(){
	flags=-O2
	[ a"$1" = a-d ] && flags=-g

	f=`name`
	rm "$f" 2> /dev/null
	g++ -std=c++11 -lm -Wall -Wno-sign-compare -Wshadow -fsanitize=address $flags "$f".cpp -o "$f"
}

c(){
	f=`name`
	./"$f"
}

a(){
	b && c
}
