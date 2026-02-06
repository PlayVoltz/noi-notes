#include <bits/stdc++.h>
using namespace std;

#define int long long
#define pii pair<int, int>
#define mp make_pair
#define pb push_back
#define fi first
#define se second

vector<vector<int> > graph, twok;

void twokdecomp(int node, int par){
	twok[node][0]=par;
	for (int i=1; i<20; ++i)twok[node][i]=twok[twok[node][i-1]][i-1];
	for (auto num:graph[node])if (num!=par)twokdecomp(num, node);
}

int kthpar(int a, int k){
	for (int i=19; i>=0; --i)if (k&(1<<i))a=twok[a][i];
	return a;
}

int32_t main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n, a, b, q;
	cin>>n;
	graph.resize(n);
	twok.resize(n, vector<int>(20));
	for (int i=1; i<n; ++i){
		cin>>a>>b;
		graph[a].pb(b);
		graph[b].pb(a);
	}
	twokdecomp(0, 0);
	cin>>q;
	while (q--){
		cin>>a>>b;
		if (!b){cout<<a<<"\n";continue;}
		int p1=kthpar(a, b), p2=kthpar(a, b-1);
		if (p1!=p2)cout<<p1<<"\n";
		else cout<<"-1\n";
	}
}
