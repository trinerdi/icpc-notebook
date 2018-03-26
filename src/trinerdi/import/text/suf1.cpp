struct suffix { 
    int idx; // pozicia, na ktorej tento suffix zacina
    int por[2]; // pomocne premenne na jeho aktualne poradie
};

char s[1000047]; // samotny string
suffix SUF[1000047]; // pole suffixov, ktore ideme triedit
int pom[1000047]; // take jedno pomocne pole

inline int compare(const suffix &a, const suffix &b) {   // porovnavacia fcia pre suffixy
    if (a.por[0] != b.por[0]) return a.por[0] < b.por[0]; else return a.por[1] < b.por[1];
}

int main() {
    scanf("%s",s);
    int N = strlen(s);

    if (N==0) {return 0; }   // pre istotu osetrime okrajove pripady
    if (N==1) { printf("0\n"); return 0; }
    
    FOR(i,N) { SUF[i].idx = i; SUF[i].por[0] = s[i]; }   // inicializacia pola suffixov (tady bylo s[i]-'a')
     
    int sl = 1;    // sl je dlzka prefixu, podla ktoreho su aktualne zotriedene
    do {
        FOR(i,N) pom[ SUF[i].idx ] = SUF[i].por[0];   // naplnime pomocne pole aktualnymi poziciami suffixov

        FOR(i,N) {      // vypocitame druhu zlozku kluca pre kazdy suffix
            int x = SUF[i].idx + sl;     // tu zacinaju dalsie jeho pismena
            SUF[i].por[1] = (x>=N) ? -1 : pom[x];     // tu sa nachadzaju v utriedenom poradi
        }
    
        sort(SUF,SUF+N,compare); // utriedime pole suffixov podla aktualnych hodnot
 
        pom[0]=0;     // a este zneuzijeme nase pomocne pole na vypocitanie noveho poradia
        for (int i=1; i<N; i++) 
            if (SUF[i].por[0]==SUF[i-1].por[0] && SUF[i].por[1]==SUF[i-1].por[1]) pom[i]=pom[i-1]; else pom[i]=i;
        FOR(i,N) SUF[i].por[0] = pom[i];

        sl<<=1;       // a mame utriedene 2x take dlhe kusy sufixov
    } while (sl < N);
    FOR(i,N) printf("%d\n",SUF[i].idx); // vypiseme indexy zaciatkov suffixov v utriedenom poradi
}
