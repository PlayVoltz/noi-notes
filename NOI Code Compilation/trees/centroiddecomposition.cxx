#include <iostream>
#include <map>
#include <vector>
#include <climits>
#include <stack>
#include <string>
#include <queue>
#include <algorithm>
#include <set>
#include <unordered_map>
#include <cmath>
#include <cctype>
#include <unordered_set>
using namespace std;

#define pb push_back
#define mp make_pair
#define pii pair<int, int>

vector <vector<int> > graph, twok;
vector <int> subtree, lvl, mindist, par, depth;

int dfs_size(int u, int p){
	subtree[u] = 1;
	for (auto v:graph[u]){
		if (lvl[v]!=-1)continue;
		if (v==p)continue;
		subtree[u]+=dfs_size(v, u);
	}
	return subtree[u];
}

int centroidfind(int u, int p, int size){
	for (auto v:graph[u]){
		if (lvl[v]!=-1)continue;
		if (v!=p && subtree[v]>size/2)return centroidfind(v, u, size);
	}
	return u;
}

void build(int u, int p, int d){
	int size = dfs_size(u, p);
	int centroid = centroidfind(u, p, size);
	par[centroid] = p;
	lvl[centroid] = d;
	for (auto v:graph[centroid]){
		if (lvl[v]!=-1)continue;
		build(v, centroid, d+1);
	}
}

void twokdecomp(int node, int par, int dep){
	twok[node][0] = par;
	depth[node] = dep;
	for (int i=1; i<20; ++i)twok[node][i] = twok[twok[node][i-1]][i-1];
	for (auto num:graph[node])if (num!=par)twokdecomp(num, node, dep+1);
}

int kthparent(int node, int k){
	for (int i=0; i<20; ++i)if (k&(1<<i))node = twok[node][i];
	return node;
}

int lca(int a, int b){
	if (depth[a]<depth[b])swap(a, b);
	a = kthparent(a, depth[a]-depth[b]);
	if (a==b)return a;
	for (int i=19; i>=0; --i){
		if (twok[a][i]!=twok[b][i]){
			a = twok[a][i];
			b = twok[b][i];
		}
	}
	return twok[a][0];
}

int dist(int a, int b){
	return depth[a]+depth[b]-2*depth[lca(a, b)];
}

void update(int u){
	for (int v=u; v!=-1; v=par[v])mindist[v]=min(mindist[v], dist(v, u));
}

int query(int u){
	int ans = INT_MAX;
	for (int v=u; v!=-1; v=par[v])ans=min(ans, mindist[v]+dist(v, u));
	return ans;
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n, q, a, b;
	cin>>n>>q;
	graph.resize(n+1);
	subtree.resize(n+1);
	lvl.resize(n+1, -1);
	par.resize(n+1);
	depth.resize(n+1);
	twok.resize(n+1, vector<int>(20));
	mindist.resize(n+1, INT_MAX/2);
	for (int i=1; i<n; ++i){
		cin>>a>>b;
		graph[a].pb(b);
		graph[b].pb(a);
	}
	build(1, -1, 0);
	twokdecomp(1, 1, 0);
	update(1);
	while (q--){
		cin>>a>>b;
		if (a==1){
			update(b);
		}
		else{
			cout<<query(b)<<"\n";
		}
	}
}
