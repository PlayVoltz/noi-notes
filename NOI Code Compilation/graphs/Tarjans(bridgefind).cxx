#include <bits/stdc++.h>
using namespace std;

#define pii pair<int, int>
#define mp make_pair
#define pb push_back

int counter=0;
vector<vector<int> > graph;
vector<int> low, disc;

void dfs(int node, int par){
	disc[node]=low[node]=counter++;
	bool done=false;
	for (auto num:graph[node]){
		if (disc[num]==-1){
			dfs(num, node);
			low[node]=min(low[node], low[num]);
			if (low[num]>disc[node])cout<<node+1<<" "<<num+1<<"\n";
		}
		else if (num==par && !done)done=1;
		else low[node]=min(low[node], disc[num]);
	}
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n, m, a, b;
	cin>>n>>m;
	graph.resize(n);
	disc.resize(n, -1);
	low.resize(n);
	while (m--){
		cin>>a>>b;--a;--b;
		graph[a].pb(b);
		graph[b].pb(a);
	}
	for (int i=0; i<n; ++i)if (disc[i]==-1)dfs(i, -1);
}
