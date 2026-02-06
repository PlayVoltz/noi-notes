#include "more_lca2.h"
#include <bits/stdc++.h>
using namespace std;

#define pii pair<int, int>
#define mp make_pair
#define pb push_back
#define fi first
#define se second

int counter=-1;
vector<vector<int> > graph;
vector<vector<pii> > rmq;
vector<int> in;
vector<pii> euler;

void dfs(int node, int d){
	in[node]=++counter;
	euler.pb(mp(d, node));
	for (auto num:graph[node])dfs(num, d+1), euler.pb(mp(d, node)), ++counter;
}

void init(int n, vector<int> p){
	in.resize(n);
	graph.resize(n);
	for (int i=1; i<n; ++i)graph[p[i]].pb(i);
	dfs(0, 0);
	rmq.resize(20, vector<pii>(euler.size()));
	rmq[0]=euler;
	for (int i=1; i<20; ++i)for (int j=0; j+(1<<i)<euler.size(); ++j)rmq[i][j]=min(rmq[i-1][j], rmq[i-1][j+(1<<(i-1))]);
}

int findLCA(int k, vector<int> vect){
	int mn=in[vect[0]], mx=in[vect[0]];
	for (int i=1; i<k; ++i)mn=min(mn, in[vect[i]]), mx=max(mx, in[vect[i]]);
	int lg=31-__builtin_clz(mx-mn+1);
	return min(rmq[lg][mn], rmq[lg][mx-(1<<lg)+1]).se;
}
