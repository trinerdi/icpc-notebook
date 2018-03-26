class MaximumMatching {
    vector< vector<int> > left_to_right, right_to_left;
    public:
    void add_edge(int left, int right);
    int maximum_matching_size() { return maximum_matching().size(); }
    vector< pair<int,int> > maximum_matching();
    pair< vector<int>, vector<int> > minimum_vertex_cover();
};

void MaximumMatching::add_edge(int left, int right) {
    if ( int(left_to_right.size()) <= left ) left_to_right.resize(left+1);
    if ( int(right_to_left.size()) <= right ) right_to_left.resize(right+1);
    left_to_right[left].push_back(right);
    right_to_left[right].push_back(left);
}

vector< pair<int,int> > MaximumMatching::maximum_matching() {
    int L = left_to_right.size(), R = right_to_left.size();
    vector<int> match(L,-1);
    for (int r=0; r<R; r++) {
        bool found = false;
        vector<int> from(L,-1);
        queue<int> Q;
        for (int x : right_to_left[r]) { Q.push(x); from[x]=x; }
        while (!Q.empty() && !found) {
            int l = Q.front(); Q.pop();
            if (match[l]==-1) {
                found = true;
                while (from[l]!=l) { match[l] = match[from[l]]; l = from[l]; }
                match[l]=r;
            } else {
                for (int x : right_to_left[ match[l] ]) if (from[x]==-1) { Q.push(x); from[x]=l; }
            }
        }
    }
    vector< pair<int,int> > result;
    for (int i=0; i<L; i++) if (match[i] != -1) result.push_back(make_pair(i,match[i]));
    return result;
}

pair< vector<int>, vector<int> > MaximumMatching::minimum_vertex_cover() {
    int L = left_to_right.size(), R = right_to_left.size();
    vector< pair<int,int> > matching = maximum_matching();
    vector<int> match(L,-1);
    vector<bool> matched(R,false);
    for (auto m : matching) { match[m.first]=m.second; matched[m.second]=true; }

    vector<bool> visited(L,false);
    queue<int> Q;
    for (int r=0; r<R; r++) if (!matched[r])
        for (int x : right_to_left[r]) if (!visited[x]) { visited[x]=true; Q.push(x); }
    while (!Q.empty()) {
        int l = Q.front(); Q.pop();
        for (int x : right_to_left[ match[l] ]) if (!visited[x]) { Q.push(x); visited[x]=true; }
    }

    vector<int> left_cover, right_cover;
    for (int l=0; l<L; l++) 
        if (visited[l]) left_cover.push_back(l);
        else if (match[l]!=-1) right_cover.push_back(match[l]);

    return make_pair( left_cover, right_cover );
}
