#include <bits/stdc++.h>
#include "factories.h"
using namespace std;

#define int long long
#define pb push_back
#define mp make_pair
#define pii pair<int, int>

const int MAXN = 5e5+5;

int counter=0, twok[MAXN][20], subtree[MAXN], mindist[MAXN], par[MAXN], depth[MAXN], dist[MAXN], in[MAXN], out[MAXN];
vector<pii> graph[MAXN];
bool done[MAXN];

int dfs_size(int u, int p, int d){
	subtree[u] = 1;
	for (auto v:graph[u]){
		if (done[v.first])continue;
		if (v.first==p)continue;
		subtree[u]+=dfs_size(v.first, u, d);
	}
	return subtree[u];
}

int centroidfind(int u, int p, int size){
	for (auto v:graph[u]){
		if (done[v.first])continue;
		if (v.first!=p && subtree[v.first]>size/2)return centroidfind(v.first, u, size);
	}
	return u;
}

void build(int u, int p, int d){
	int size = dfs_size(u, p, d);
	int centroid = centroidfind(u, p, size);
	par[centroid] = p;
	done[centroid] = true;
	for (auto v:graph[centroid]){
		if (done[v.first])continue;
		build(v.first, centroid, d+1);
	}
}

void twokdecomp(int node, int par, int dep, int d){
	in[node] = ++counter;
	twok[node][0] = par;
	depth[node] = dep;
	dist[node] = d;
	for (int i=1; i<20; ++i)twok[node][i] = twok[twok[node][i-1]][i-1];
	for (auto num:graph[node])if (num.first!=par)twokdecomp(num.first, node, dep+1, d+num.second);
	out[node] = counter;
}

bool ispar(int a, int b){
	return in[a]<=in[b] && out[a]>=in[b];
}

int lca(int a, int b){
	if (ispar(a, b))return a;
	if (ispar(b, a))return b;
	for (int i=19; i>=0; --i)if (!ispar(twok[a][i], b))a=twok[a][i];
	return twok[a][0];
}

void update(int u){
	for (int v=u; v!=-1; v=par[v])mindist[v]=min(mindist[v], dist[u]+dist[v]-2*dist[lca(u, v)]);
}

int query(int u){
	int ans = LLONG_MAX;
	for (int v=u; v!=-1; v=par[v])ans=min(ans, mindist[v]+dist[u]+dist[v]-2*dist[lca(u, v)]);
	return ans;
}

void Init(signed n, signed A[], signed B[], signed D[]) {
	for (int i=0; i<n-1; ++i){
		graph[A[i]].pb(mp(B[i], D[i]));
		graph[B[i]].pb(mp(A[i], D[i]));
	}
	build(0, -1, 0);
	twokdecomp(0, 0, 0, 0);
	fill(mindist, mindist+n, LLONG_MAX/2);
}

long long Query(signed s, signed x[], signed t, signed y[]) {
	for (int i=0; i<s; ++i)update(x[i]);
	int ans = LLONG_MAX;
	for (int i=0; i<t; ++i)ans = min(ans, query(y[i]));
	for (int i=0; i<s; ++i){
		for (int v=x[i]; v!=-1 && mindist[v]!=LLONG_MAX/2; v=par[v])mindist[v]=LLONG_MAX/2;
	}
	return ans;
}
