#include "simurgh.h"
#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define mp make_pair
#define pii pair<int, int>
#define fi first
#define se second

int n, counter=0;
vector<bool> in, visited;
vector<int> isroyal, low, disc, epar, par, up, ooga, tree, deg, dsu;
vector<pii> edges;
vector<vector<pii> > graph;

int query(){
	vector<int> temp;
	for (int i=0; i<in.size(); ++i)if (in[i])temp.pb(i);
	return count_common_roads(temp);
}

int fp(int a){
	if (dsu[a]==-1)return a;
	return dsu[a]=fp(dsu[a]);
}

bool merge(int a, int b){
	a=fp(a), b=fp(b);
	if (a==b)return 0;
	dsu[a]=b;
	return 1;
}

void dfs(int node, int p, int ep){
	par[node]=p;
	epar[node]=ep;
	disc[node]=low[node]=++counter;
	for (auto num:graph[node])if (num.se!=ep){
		if (disc[num.fi]==-1){
			dfs(num.fi, node, num.se);
			if (low[num.fi]<low[node])low[node]=low[num.fi], up[node]=up[num.fi];
			if (low[num.fi]>disc[node])isroyal[num.se]=1;
		}
		else if (low[node]>disc[num.fi])low[node]=disc[num.fi], up[node]=num.se;
	}
	if (ep!=-1)in[ep]=1, tree.pb(ep);
}

void dfs2(int node){
	for (auto num:graph[node])if (par[num.fi]==node)dfs2(num.fi);
	if (par[node]==-1||up[node]==-1||isroyal[epar[node]]!=-1)return;
	int a=edges[up[node]].fi, b=edges[up[node]].se;
	if (disc[a]>disc[b])swap(a, b);
	int mx=query(), mn=mx, r=-1;
	in[up[node]]=1;
	for (int c=b; c!=a; c=par[c])if (isroyal[epar[c]]==-1||r==-1){
		in[epar[c]]=0;
		ooga[epar[c]]=query();
		mn=min(mn, ooga[epar[c]]);
		mx=max(mx, ooga[epar[c]]);
		if (isroyal[epar[c]]!=-1)r=ooga[epar[c]]-!isroyal[epar[c]];
		in[epar[c]]=1;
	}
	in[up[node]]=0;
	for (int c=b; c!=a; c=par[c])if (isroyal[epar[c]]==-1){
		if (r!=-1)isroyal[epar[c]]=(r==ooga[epar[c]]);
		else if (mn==mx)isroyal[epar[c]]=0;
		else isroyal[epar[c]]=(ooga[epar[c]]==mn);
	}
}

int query_forest(vector<int> vect){
	int res=0;
	dsu.assign(n, -1);
	vector<int> del;
	for (auto c:vect)del.pb(c), merge(edges[c].fi, edges[c].se), in[c]=1;
	for (auto c:tree)if (merge(edges[c].fi, edges[c].se))del.pb(c), in[c]=1, res-=isroyal[c];
	res+=query();
	for (auto a:del)in[a]=0;
	return res;
}

void cut(int node){
	if (!deg[node]||visited[node])return;
	visited[node]=1;
	vector<int> e;
	for (auto num:graph[node])if (!visited[num.fi])e.pb(num.se);
	int low=-1, high=e.size()-1;
	while (low+1<high){
		int mid=(low+high)/2;
		vector<int> temp;
		for (int i=low+1; i<=mid; ++i)temp.pb(e[i]);
		if (query_forest(temp))high=mid;
		else low=mid;
	}
	int p=edges[e[high]].fi^edges[e[high]].se^node;
	isroyal[e[high]]=1;
	--deg[p];
	if (deg[p]==1)cut(p);
}

vector<int> find_roads(int N, vector<int> u, vector<int> v){
	n=N;
	epar.resize(n);
	par.resize(n);
	graph.resize(n);
	low.resize(n);
	up.resize(n, -1);
	disc.resize(n, -1);
	in.resize(u.size(), 0);
	deg.resize(n);
	ooga.resize(u.size());
	isroyal.resize(u.size(), -1);
	for (int i=0; i<u.size(); ++i){
		edges.pb(mp(u[i], v[i]));
		graph[u[i]].pb(mp(v[i], i));
		graph[v[i]].pb(mp(u[i], i));
	}
	dfs(0, -1, -1);
	dfs2(0);
	in.assign(u.size(), 0);
	for (int i=0; i<n; ++i){
		vector<int> temp;
		for (auto num:graph[i])temp.pb(num.se);
		deg[i]=query_forest(temp);
	}
	visited.resize(n, 0);
	for (int i=0; i<n; ++i)if (deg[i]==1)cut(i);
	vector<int> ans;
	for (int i=0; i<u.size(); ++i)if (isroyal[i]==1)ans.pb(i);
	return ans;
}
