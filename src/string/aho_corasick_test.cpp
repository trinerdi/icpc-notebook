#include <gtest/gtest.h>
#include "aho_corasick.cpp"

// TODO: add more tests

string gen(int n, int k) {
	string s;
	rep(i, 0, n)
		s.push_back('a' + rand() % k);
	return s;
}

set<pair<int, int>> se;

void occurence(int i, int index) {
	EXPECT_FALSE(se.count({i, index}));
	se.insert({i, index});
}

bool matches(const string &hay, const string &needle, int start) {
	return start + needle.size() <= hay.size()
	       && needle == hay.substr(start, needle.size());
}

TEST(AC, Valid) {
	rep(i, 0, 20) {
		string s = gen(1000, i / 2 + 1);
		set<string> needles;
		rep(j, 0, 10)
			needles.insert(gen(rand() % 8 + 1, i / 2 + 1));

		vector<string> n;
		for (auto a : needles)
			n.push_back(a);

		se = {};
		ac(s, n);
		rep(j, 0, n.size())
			rep(k, 0, s.size())
				EXPECT_EQ(matches(s, n[j], k), se.count({k, j}));
	}
}
