e(){ # run on [problem].in*
	t=$(basename `pwd`)
	if [ "$1" = -d ]; then fl=-g; v=valgrind
	else fl=-O2\ -fsanitize=address; v=; fi
	g++ -std=c++11 -lm -Wall -Wno-sign-compare -Wshadow $fl $t.cpp -o $t
	for i in $t.in*; do echo $i:; $v ./$t < $i; done
}
create(){
	for i in {a..z}; do  # Change z as needed
		mkdir "$i" && cd "$i" || continue
		cp -n ../template.cpp "$i".cpp; touch "$i".in1; cd ..
	done
}
