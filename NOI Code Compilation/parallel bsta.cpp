#include <cstdio>
#include <stdio.h>
#include <stdbool.h>
#include <iostream>
#include <map>
#include <vector>
#include <climits>
#include <stack>
#include <string>
#include <queue>
#include <algorithm>
#include <set>
#include <unordered_set>
#include <unordered_map>
#include <cmath>
#include <cctype>
#include <bitset>
#include <iomanip>
#include <cstring>
#include <numeric>
#include <cassert>
#include <random>
using namespace std;
 
#define int long long
#define pii pair<int, int>
#define mp make_pair
#define pb push_back
#define fi first
#define se second

struct ooga{
	int a, b, g, s, i;
};

int counter=1;
vector<int> in, out, depth, ft, mx;
vector<vector<int> > graph, twok;

void dfs(int node, int p, int d){
	in[node]=counter++;
	depth[node]=d;
	twok[node][0]=p;
	for (int i=1; i<20; ++i)twok[node][i]=twok[twok[node][i-1]][i-1];
	for (auto num:graph[node])if (num!=p)dfs(num, node, d+1);
	out[node]=counter;
}

int lca(int a, int b){
	if (depth[a]<depth[b])swap(a, b);
	for (int i=0, k=depth[a]-depth[b]; i<20; ++i)if (k&(1<<i))a=twok[a][i];
	if (a==b)return a;
	for (int i=19; i>=0; --i)if (twok[a][i]!=twok[b][i])a=twok[a][i], b=twok[b][i];
	return twok[a][0];
}

void up(int i, int v){
	for (;i<=counter;i+=i&-i)ft[i]+=v;
}

int query(int i){
	int res=0;
	for (;i;i-=i&-i)res+=ft[i];
	return res;
}

bool custom(ooga a, ooga b){
	return mx[a.i]<mx[b.i];
}

int32_t main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n, m, q, a, b, c, d, p=-1;
	cin>>n>>m>>q;
	graph.resize(n+1);
	in.resize(n+1);
	out.resize(n+1);
	depth.resize(n+1);
	twok.resize(n+1, vector<int>(20));
	vector<pii> edges(n), vect(m);
	for (int i=1; i<n; ++i){
		cin>>a>>b;
		graph[a].pb(b);
		graph[b].pb(a);
		edges[i]=mp(a, b);
	}
	dfs(1, 1, 0);
	ft.resize(counter+1, 0);
	for (int i=0; i<m; ++i){
		cin>>a>>b;
		if (depth[edges[a].fi]>depth[edges[a].se])a=edges[a].fi;
		else a=edges[a].se;
		vect[i]=mp(b, a);
	}
	sort(vect.begin(), vect.end());
	vector<ooga> quer(q);
	vector<int> ans(q), cc(q);
	mx.resize(q);
	for (int i=0; i<m; ++i)up(in[vect[i].se], 1), up(out[vect[i].se], -1);
	for (int i=0; i<q; ++i)cin>>a>>b>>c>>d, quer[i]={a, b, c, d, i}, cc[i]=query(in[a])+query(in[b])-2*query(in[lca(a, b)]);
	for (int i=0; i<m; ++i)up(in[vect[i].se], -1), up(out[vect[i].se], 1);
	queue<pair<pii, vector<ooga> > > ord;
	ord.push(mp(mp(-1, m), quer));
	while (ord.size()){
		int low=ord.front().fi.fi, high=ord.front().fi.se, mid=(low+high)/2;
		vector<ooga> cq=ord.front().se;
		ord.pop();
		if (low+1>=high){
			for (auto a:cq)mx[a.i]=low;
			continue;
		}
		while (p<mid)++p, up(in[vect[p].se], vect[p].fi), up(out[vect[p].se], -vect[p].fi);
		while (p>mid)up(in[vect[p].se], -vect[p].fi), up(out[vect[p].se], vect[p].fi), --p;
		vector<ooga> left, right;
		for (auto c:cq){
			if (query(in[c.a])+query(in[c.b])-2*query(in[lca(c.a, c.b)])<=c.s)right.pb(c);
			else left.pb(c);
		}
		if (left.size())ord.push(mp(mp(low, mid), left));
		if (right.size())ord.push(mp(mp(mid, high), right));
	}
	while (p!=-1)up(in[vect[p].se], -vect[p].fi), up(out[vect[p].se], +vect[p].fi), --p;
	sort(quer.begin(), quer.end(), custom);
	p=0;
	for (auto c:quer){
		while (p<=mx[c.i])up(in[vect[p].se], 1), up(out[vect[p].se], -1), ++p;
		ans[c.i]=max(-1ll, c.g-(cc[c.i]-query(in[c.a])-query(in[c.b])+2*query(in[lca(c.a, c.b)])));
	}
	for (auto a:ans)cout<<a<<"\n";
}
