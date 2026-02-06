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

int n, counter=1, ans=0, tsz=0, bcc=0;
vector<int> disc, low, sz;
vector<vector<int> > graph, fgraph;
stack<int> st;

void dfs(int node, int p){
	++tsz;
	disc[node]=low[node]=counter++;
	st.push(node);
	for (auto num:graph[node])if (num!=p){
		if (disc[num])low[node]=min(low[node], disc[num]);
		else{
			dfs(num, node);
			low[node]=min(low[node], low[num]);
			if (low[num]>=disc[node]){
				++bcc;
				fgraph[node].pb(n+bcc);
				while (fgraph[n+bcc].empty()||fgraph[n+bcc].back()!=num)fgraph[n+bcc].pb(st.top()), st.pop();
			}
		}
	}
}

void dfs2(int node){
	if (node<=n)sz[node]=1;
	for (auto num:fgraph[node]){
		dfs2(num);
		sz[node]+=sz[num];
		if (node>n)ans-=fgraph[node].size()*sz[num]*(sz[num]-1);
	}
	if (node>n)ans-=fgraph[node].size()*(tsz-sz[node])*(tsz-sz[node]-1);
}

int32_t main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int m, a, b;
	cin>>n>>m;
	graph.resize(n+1);
	fgraph.resize(2*n+2);
	disc.resize(n+1, 0);
	low.resize(n+1);
	sz.resize(2*n+2, 0);
	while (m--){
		cin>>a>>b;
		graph[a].pb(b);
		graph[b].pb(a);
	}
	for (int i=1; i<=n; ++i)if (!disc[i]){
		tsz=0;
		dfs(i, 1);
		ans+=tsz*(tsz-1)*(tsz-2);
		dfs2(i);
	}
	cout<<ans;
}
