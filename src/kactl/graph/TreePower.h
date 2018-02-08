/**
 * Author: Johan Sannemo
 * Date: 2015-02-06
 * License: CC0
 * Source: Folklore
 * Status: Tested at Petrozavodsk
 * Description: Calculate power of two jumps in a tree.
 *  Assumes the root node points to itself.
 * Time: $O(|V| \log |V|)$
 */
#pragma once

vector<vector<int>> treeJump(vector<int>& P){
	int on = 1, d = 1;
	while(on < P.size()) on *= 2, d++;
	vector<vector<int>> jmp(d, P);
	rep(i,1,d) rep(j,0,P.size())
		jmp[i][j] = jmp[i-1][jmp[i-1][j]];
	return jmp;
}

int jmp(vector<vector<int>>& tbl, int nod, int steps){
	rep(i,0,tbl.size())
		if(steps&(1<<i)) nod = tbl[i][nod];
	return nod;
}
