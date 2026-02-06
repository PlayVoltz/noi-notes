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

#define pii pair<int, int>
#define mp make_pair

int n;
vector<vector<int> > twok;
vector<vector<pii> > graph;
vector<int> depth;
vector <int> dist;

void twokdecomp(int node, int par, int dep){
	twok[node][0] = par;
	depth[node] = dep;
	for (int i=1; i<20; ++i){
		if (twok[node][i-1]==-1){
			twok[node][i] = -1;
			continue;
		}
		twok[node][i] = twok[twok[node][i-1]][i-1];
	}
	for (auto num:graph[node]){
		if (num.first!=par){
			twokdecomp(num.first, node, dep+1);
		}
	}
}

int kthparent(int node, int k){
	for (int i=0; i<20; ++i){
		if (k&(1<<i)){
			node = twok[node][i];
		}
	}
	return node;
}

void dfs(int node, int par, int d){
	dist[node] = d;
	for (auto num:graph[node]){
		if (num.first!=par){
			dfs(num.first, node, d+num.second);
		}
	}
}

int lca(int a, int b){
	if (depth[a]<depth[b]){
		swap(a, b);
	}
	a = kthparent(a, depth[a]-depth[b]);
	if (a==b){
		return a;
	}
	for (int i=19; i>=0; --i){
		if (twok[a][i]!=twok[b][i]){
			a = twok[a][i];
			b = twok[b][i];
		}
	}
	return twok[a][0];
}

int main(){
	int q, a, b, c;
	cin>>n>>q;
	graph.resize(n+1);
	twok.resize(n+1, vector<int>(20));
	depth.resize(n+1);
	dist.resize(n+1);
	for (int i=1; i<n; ++i){
		cin>>a>>b>>c;
		graph[a].push_back(mp(b, c));
		graph[b].push_back(mp(a, c));
	}
	dfs(1, -1, 0);
	twokdecomp(1, -1, 0);
	while (q--){
		cin>>a>>b;
		int val = dist[a]+dist[b]-2*dist[lca(a, b)];
		cout<<val<<"\n";
	}
}
