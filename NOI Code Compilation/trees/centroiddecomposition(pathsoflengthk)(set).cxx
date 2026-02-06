#include "race.h"
#include <bits/stdc++.h>
using namespace std;

#define pii pair<int, int>
#define mp make_pair
#define pb push_back

const int MAXN=2e5+5;

int n, k, ans=INT_MAX;
set<pii> graph[MAXN];
vector<pii> lazy;
int subtree[MAXN], par[MAXN], dist[1000005];
vector<int> revert;

int dfs_size(int u, int p){
	subtree[u] = 1;
	for (auto v:graph[u]){
		if (v.first==p)continue;
		subtree[u]+=dfs_size(v.first, u);
	}
	return subtree[u];
}

int centroidfind(int u, int p, int size){
	for (auto v:graph[u]){
		if (v.first!=p && subtree[v.first]>size/2)return centroidfind(v.first, u, size);
	}
	return u;
}

void check(int node, int par, int d, int e){
	if (d>k)return;
	ans=min(ans, dist[k-d]+e);
	lazy.pb(mp(d, e));
	for (auto num:graph[node])if (num.first!=par)check(num.first, node, d+num.second, e+1);
}

void build(int u, int p, int d){
	int size = dfs_size(u, p);
	int centroid = centroidfind(u, p, size);
	par[centroid] = p;
	for (auto num:revert)dist[num]=INT_MAX/2;
	revert.clear();
	dist[0]=0;
	for (auto v:graph[centroid]){
		lazy.clear();
		check(v.first, centroid, v.second, 1);
		for (auto num:lazy){
			dist[num.first]=min(dist[num.first], num.second);
			revert.pb(num.first);
		}
	}
	vector<pii> temp;
	for (auto v:graph[centroid])temp.pb(v);
	for (auto num:temp){
		graph[num.first].erase(mp(centroid, num.second));
		graph[centroid].erase(num);
		build(num.first, centroid, num.second);
	}
}

int best_path(int N, int K, int H[][2], int L[]){
	n=N, k=K;
	for (int i=0; i<n-1; ++i){
		graph[H[i][0]].insert(mp(H[i][1], L[i]));
		graph[H[i][1]].insert(mp(H[i][0], L[i]));
	}
	for (int i=0; i<=k; ++i)dist[i]=INT_MAX/2;
	build(0, -1, 0);
	return (ans>=INT_MAX/2 ? -1:ans);
}
