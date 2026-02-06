#include <bits/stdc++.h>
using namespace std;

#define int long long
#define pii pair<int, bool>
#define mp make_pair
#define pb push_back

int n;
vector<vector<int> > graph, tgraph, fgraph;
stack <int> st;
vector<bool> va, vb, pub;
vector<int> val, par, dp;
vector<pii> comp;

void dfs(int node){
	if (va[node])return;
	va[node] = true;
	for (auto num:graph[node])dfs(num);
	st.push(node);
}

void dfs2(int node, int scc){
	if (vb[node]){
		if (par[node]!=scc)fgraph[par[node]].pb(scc);
		return;
	}
	vb[node]=true;
	par[node]=scc;
	comp[scc].first+=val[node];
	comp[scc].second|=pub[node];
	for (auto num:tgraph[node])dfs2(num, scc);
}

int atm(int node){
	if (dp[node]!=-1)return dp[node];
	int maxnum=(comp[node].second ? comp[node].first:LLONG_MIN);
	for (auto num:fgraph[node])maxnum=max(maxnum, comp[node].first+atm(num));
	dp[node]=maxnum;
	return dp[node];
}

int32_t main(){
	int m, a, b, s, p;
	cin>>n>>m;
	graph.resize(n);
	tgraph.resize(n);
	fgraph.resize(n);
	val.resize(n);
	par.resize(n);
	dp.resize(n, -1);
	pub.resize(n, false);
	va.resize(n, false);
	vb.resize(n, false);
	comp.resize(n);
	while (m--){
		cin>>a>>b;--a;--b;
		graph[a].pb(b);
		tgraph[b].pb(a);
	}
	for (int i=0; i<n; ++i)cin>>val[i];
	cin>>s>>p;--s;
	while (p--){
		cin>>a;--a;
		pub[a]=1;
	}
	for (int i=0; i<n; ++i)dfs(i);
	while (!st.empty()){
		int node=st.top();
		st.pop();
		if (vb[node])continue;
		comp[node]=mp(0, 0);
		dfs2(node, node);
	}
	cout<<atm(par[s]);
}
