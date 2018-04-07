#include "gtest/gtest.h"
#include "heavylight2.cpp"
#include "../test.hpp"

#define clean(a) a = {}, a.resize(n)

vector <ll> pref;
void flat_init(void) {
	pref = {ZERO};
	rep(i, 0, G.size())
		pref.push_back(rand() + pref.back());
}

ll flat_quepdate(int l, int r, bool upd, ll val) {
	assert(!upd);
	return pref[r + 1] - pref[l];
}

void gen(int n) {
	clean(G);
	rep(i, 0, n)
		if (i)
			G[rand() % i].push_back(i);
}

bool dfs(int v, int f, int d) {
	bool ok = par[v] == f && depth[v] == d;
	for (auto s: G[v])
		ok &= dfs(s, v, d + 1);
	return ok;
}

int dfs_sizes(int v) {
	int size = 1;
	for (auto s: G[v])
		size += dfs_sizes(s);
	EXPECT_EQ(size, subs[v]);
	return subs[v];
}

bool dfs_first_biggest(int v) {
	bool ok = true;
	for (auto s: G[v])
		ok &= subs[s] <= subs[G[v][0]];
	return ok;
}

TEST(LCA, Precomputation) {
	int n = 300;
	rep(i, 0, 30) {
		gen(n);
		vector <set <int> > F(n);
		rep(i, 0, n)
			for (auto s: G[i])
				EXPECT_TRUE(F[i].insert(s).second);

		initHLD();
		rep(i, 0, n)
			for (auto s: G[i])
				EXPECT_TRUE(F[i].erase(s));

		rep(i, 0, n)
			EXPECT_EQ(F[i].size(), 0);

		EXPECT_TRUE(dfs(0, par[0], 0));
		EXPECT_EQ(dfs_sizes(0), n);
		EXPECT_TRUE(dfs_first_biggest(0));

		EXPECT_EQ(et[0], 0);
		EXPECT_EQ(in[0], 0);
		EXPECT_EQ(out[0], n - 1);
		vector<int> v = et;
		sort(v.begin(), v.end());
		EXPECT_EQ(v.size(), n);
		rep(i, 0, n)
			EXPECT_EQ(v[i], i);

		rep(i, 0, n) {
			int a = rand() % (out[i] - in[i] + 1) + in[i];
			EXPECT_EQ(lca(et[a], i), i);
			EXPECT_EQ(lca(i, et[out[i]]), i);
			if (out[i] < n - 1)
				EXPECT_NE(lca(i, et[out[i] + 1]), i);
		}
	}
}

TEST(LCA, LCA) {
	int n = 100;
	rep(i, 0, 10) {
		gen(n);
		initHLD();
		rep(a, 0, n) rep(b, 0, n) {
			int l = lca(a, b);
			int ta = a, tb = b;
			while (ta != tb)
				if (depth[ta] < depth[tb])
					tb = par[tb];
				else
					ta = par[ta];

			EXPECT_EQ(l, ta);
		}
	}
}

TEST(LCA, Benchmark) {
	int n = 100000;
	gen(n);
	initHLD();
	rep(i, 0, 100000) {
		int a = rand() % n, b = rand() % n;
		EXPECT_EQ(lca(a, b), lca(b, a));
	}
}

TEST(HLD, BenchmarkPrefixSums) {
	int n = 100000;
	gen(n);
	initHLD();
	rep(i, 0, 100000)
		quepdate(rand() % n, rand() % n, false, ZERO);
}

TEST(HLD, PrefixSumsCorrect) {
	int n = 30;
	rep(i, 0, 10) {
		gen(n);
		initHLD();
		rep(a, 0, n) rep(b, 0, n) {
			ll val = quepdate(a, b, false, ZERO);
			for (int ta = a, tb = b; ta != tb; val -= flat_quepdate(in[ta], in[ta], false, 0), ta = par[ta])
				if (depth[ta] < depth[tb])
					swap(ta, tb);

			EXPECT_EQ(val, 0);
		}
	}
}

TEST(HLD, Preprocessing) {
	int n = 100;
	rep(i, 0, 100) {
		gen(n);
		initHLD();
		rep(i, 1, n)
			EXPECT_TRUE(top[i] == i || top[i] == top[par[i]]);
	}
}
