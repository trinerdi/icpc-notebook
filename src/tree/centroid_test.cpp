#include "centroid.cpp"
#include "gtest/gtest.h"

Graph gen_tree(int n, int mode) {
	Graph G(n);
	rep(i, 1, n) {
		int p;
		switch (mode) {
		case 0:
			p = rand() % i; // Expected number of sons of v is greater for smaller v's
			break;
		case 1:
			p = i - 1; // A path
			break;
		case 2:
			p = sqrt(rand() % (i * i)); // Choose more recent vertices with greater probability
			break;
		case 3: // A binary tree
			p = (i - 1) / 2;
			break;
		case 4: // Random tree with longer paths
			if (rand() % 4)
				p = i - 1;
			else
				p = rand() % i;
			break;
		}

		G[p].push_back(i);
		G[i].push_back(p);
	}

	return G;
}

Graph gen_tree(int n) {
	int mode = rand() % 5;
	return gen_tree(n, mode);
}

TEST(FIND, OneOrTwo) {
	Graph G(1), F = {{1}, {0}};
	EXPECT_EQ(find_centroid(G, 0), 0);
	int c = find_centroid(F, 0), d = find_centroid(F, 1);
	EXPECT_TRUE(c == 0 || c == 1);
	EXPECT_TRUE(d == 0 || d == 1);
}

TEST(FIND, CountsAll) {
	int runs = 50, size = 100;
	rep(i, 0, runs) {
		Graph G = gen_tree(size);
		EXPECT_EQ(_find_centroid(G, rand() % size, -1, 0).first, size);
	}
}

TEST(FIND, AlwaysExists) {
	int runs = 50, size = 100;
	rep(i, 0, runs) {
		Graph G = gen_tree(size);
		int c = find_centroid(G, rand() % size);
		EXPECT_TRUE(c != -1 && c < size);
	}
}

int sub_size(Graph &G, int v, int father)
{
	int s = 1;
	for (int s: G[v])
		if (s != father)
			s += sub_size(G, s, v);

	return s;
}

TEST(FIND, AlwaysACentroid) {
	int runs = 100, size = 100;
	rep(i, 0, runs) {
		Graph G = gen_tree(size);
		int c = find_centroid(G, rand() % size);
		for (int s: G[c])
			EXPECT_TRUE(sub_size(G, s, c) <= size);
	}
}


TEST(DECOMPOSE, OneOrTwo) {
	Graph G = {{}}, F = {{1}, {0}};
	EXPECT_EQ(example_decompose(G), (vector<int> {0}));
	EXPECT_EQ(example_decompose(F), (vector<int> {1, 1}));
}

vector<int> deg(Graph G) {
	vector<int> r;
	for (vector<int> es: G)
		r.push_back(es.size());

	return r;
}

TEST(DECOMPOSE, PreservesDegree) {
	int runs = 30, size = 30;
	rep(i, 0, runs) {
		Graph G = gen_tree(size);
		vector<int> pre = deg(G);
		example_decompose(G);
		vector<int> pos = deg(G);
		EXPECT_EQ(pre, pos);
	}
}

TEST(DECOMPOSE, PreservesEdges) {
	int runs = 30, size = 30;
	rep(i, 0, runs) {
		Graph G = gen_tree(size);
		Graph F = G;
		example_decompose(G);
		EXPECT_EQ(G.size(), F.size());
		rep(i, 0, G.size()) {
			vector<int> gs = G[i], fs = F[i];
			sort(gs.begin(), gs.end());
			sort(fs.begin(), fs.end());
			EXPECT_EQ(gs, fs);
		}
	}
}

TEST(DECOMPOSE, CalculatesCorrectly) {
	int runs = 30, size = 30;
	rep(i, 0, runs) {
		Graph G = gen_tree(size);
		vector<int> degs = deg(G);
		vector<int> calcdegs = example_decompose(G);
		EXPECT_EQ(degs, calcdegs);
	}
}

TEST(DECOMPOSE, Benchmark5times1e4) {
	int runs = 5, size = 10000;
	rep(i, 0, runs) {
		Graph G = gen_tree(size, i);
		vector<int> degs = deg(G);
		vector<int> calcdegs = example_decompose(G);
		EXPECT_EQ(degs, calcdegs);
	}
}
