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
#include <fstream>
using namespace std;

#define int long long
#define pii pair<int, int>
#define mp make_pair
#define pb push_back
#define fi first
#define se second

int n, k, s, t;
vector<vector<pii> > graph, rev;
vector<int> dj, ans, p, ord;

struct leftist_heap{
	struct node{
		int val, nx, l, r, s;
		node(): val(0), nx(0), l(0), r(0), s(0){}
		node(int a, int b): val(a), nx(b), l(0), r(0), s(1){}
	}h[11000000];//size is 2(e)log(e) where e is edges
	int counter=1;
	int create(int a, int b){
		h[counter]=node(a, b);
		++counter;
		return counter-1;
	}
	void bal(int i){
		if (h[h[i].l].s<h[h[i].r].s)swap(h[i].l, h[i].r);
		h[i].s=h[h[i].r].s+1;
	}
	int merge(int a, int b){
		if (!a||!b)return a^b;
		if (h[a].val>h[b].val)swap(a, b);
		int id=create(h[a].val, h[a].nx);
		h[id].l=h[a].l;
		h[id].r=merge(h[a].r, b);
		bal(id);
		return id;
	}
}lh;

void dijk(){
	dj.resize(n, LLONG_MAX/2);
	p.resize(n, -1);
	vector<bool> visited(n, 0);
	priority_queue<pii, vector<pii>, greater<pii> > pq;
	dj[t]=0;
	pq.push(mp(0, t));
	while (pq.size()){
		int node=pq.top().se;
		pq.pop();
		if (visited[node])continue;
		visited[node]=1;
		ord.pb(node);
		for (auto num:rev[node])if (!visited[num.fi]&&dj[node]+num.se<dj[num.fi]){
			dj[num.fi]=dj[node]+num.se;
			pq.push(mp(dj[num.fi], num.fi));
			p[num.fi]=node;
		}
	}
}

void simple_eppstein(){
	dijk();
	if (dj[s]==LLONG_MAX/2)return;
	vector<int> heap(n, 0);
	for (auto node:ord){
		bool par=0;
		if (p[node]!=-1)heap[node]=heap[p[node]];
		for (auto num:graph[node]){
			if (dj[num.fi]==LLONG_MAX/2)continue;
			if (!par&&num.fi==p[node]&&!(num.se+dj[num.fi]-dj[node])){par=1;continue;}
			heap[node]=lh.merge(heap[node], lh.create(num.se+dj[num.fi]-dj[node], num.fi));
		}
	}
	ans.pb(dj[s]);
	priority_queue<pii, vector<pii>, greater<pii> > pq;
	if (heap[s])pq.push(mp(dj[s]+lh.h[heap[s]].val, heap[s]));
	while (pq.size()&&ans.size()<k){
		int d=pq.top().fi, c=pq.top().se;
		pq.pop();
		ans.pb(d);
		if (heap[lh.h[c].nx])pq.push(mp(d+lh.h[heap[lh.h[c].nx]].val, heap[lh.h[c].nx]));
		if (lh.h[c].l)pq.push(mp(d-lh.h[c].val+lh.h[lh.h[c].l].val, lh.h[c].l));
		if (lh.h[c].r)pq.push(mp(d-lh.h[c].val+lh.h[lh.h[c].r].val, lh.h[c].r));
	}
}

int32_t main(){
	int m, a, b, c;
	cin>>n>>m>>k;
	s=0, t=n-1;
	graph.resize(n);
	rev.resize(n);
	while (m--)cin>>a>>b>>c, --a, --b, graph[a].pb(mp(b, c)), rev[b].pb(mp(a, c));
	simple_eppstein();
	if (ans.size()<k)cout<<"-1\n";
	else cout<<ans[k-1];
}
