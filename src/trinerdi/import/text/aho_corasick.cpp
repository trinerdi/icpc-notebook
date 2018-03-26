class trie {
  class __trieNode { 
    public: 
      vector<int> endsHere; 
      __trieNode *nextOutput, *son[32], *higher; 
      __trieNode() { nextOutput=higher=NULL; memset(son,0,sizeof(son)); } 
  };
  __trieNode *root;
  int __size;
  public:
  trie() { root = NULL; __size = 0; }

  inline void insert(const string &S) { 
    __trieNode *kde; 
    if (!root) root = new __trieNode(); 
    kde = root; 
    for (unsigned i=0; i<S.size(); i++) { 
      int idx = S[i]-'a'; 
      if (! kde->son[idx]) kde->son[idx] = new __trieNode(); 
      kde = kde->son[idx]; 
    } 
    kde->endsHere.push_back(__size++); 
  }

  inline int find(const string &S) { 
    __trieNode *kde = root; 
    for (unsigned i=0; i<S.size(); i++) { if (!kde) return -1; kde = kde->son[ S[i]-'a' ]; } 
    if (!kde || kde->endsHere.empty()) return -1; 
    return kde->endsHere[0]; 
  }

  inline void createAutomaton() { 
    if (!root) return; 
    queue<__trieNode*> Q;
    Q.push(root);
    __trieNode *superRoot = new __trieNode();
    for (int i=0; i<26; i++) superRoot->son[i] = root;
    root->higher = superRoot;
    while (!Q.empty()) { 
      __trieNode *kde = Q.front(); Q.pop();
      for (int i=0; i<26; i++) 
        if (kde->son[i]) { 
          __trieNode *cand = kde->higher; 
          while (! cand->son[i]) cand = cand->higher; 
          kde->son[i]->higher = cand->son[i]; 
          if (kde->son[i]->higher->endsHere.empty())
            kde->son[i]->nextOutput = kde->son[i]->higher->nextOutput; 
          else
            kde->son[i]->nextOutput = kde->son[i]->higher; 
          Q.push(kde->son[i]); 
        } 
    } 
  }
  
  inline vector<int> trie::reportMatchedWords(const string &S) { 
    vector<int> res(__size,0); 
    __trieNode *kde = root; 
    for (unsigned i=0; i<S.size(); i++) { 
      int idx = S[i]-'a'; 
      while (! kde->son[idx]) kde = kde->higher;
      kde = kde->son[idx]; 
      __trieNode *out = kde;
      while (out) { 
        for (unsigned j=0; j < out->endsHere.size(); j++) res[out->endsHere[j]]=1; 
        out = out->nextOutput; 
      } 
    } 
    return res; 
  }
};
