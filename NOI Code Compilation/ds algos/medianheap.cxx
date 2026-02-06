#include <bits/stdc++.h>
using namespace std;

#define pb push_back

multiset <int> top, down;
vector<vector<int> > graph;
vector<int> val, dp;

void bal(){
	if (down.size()){
		auto it=down.end();--it;
		top.insert(*it);
		down.erase(it);
	}
	while (down.size()<top.size()){
		down.insert(*top.begin());
		top.erase(top.begin());
	}
}

void del(int num){
	auto it=down.end();--it;
	if (*it<num)top.erase(top.lower_bound(num));
	else down.erase(down.lower_bound(num));
}

int median(){
	auto it=down.end();--it;
	if (down.size()==top.size())return((*it)+(*top.begin()))/2;
	else return *it;
}

void dfs(int node, int par, int dep){
	down.insert(val[node]);bal();
	int minnum=INT_MAX, maxnum=INT_MIN;
	for (auto num:graph[node]){
		if (num!=par){
			dfs(num, node, dep+1);
			minnum=min(minnum, dp[num]);
			maxnum=max(maxnum, dp[num]);
		}
	}
	if (minnum==INT_MAX)dp[node]=median();
	else if (dep%2)dp[node]=minnum;
	else dp[node]=maxnum;
	del(val[node]);bal();
}

int main(){
	int n, a, b;
	cin>>n;
	graph.resize(n);
	val.resize(n);
	dp.resize(n);
	for (int i=0; i<n; ++i)cin>>val[i];
	for (int i=1; i<n; ++i){
		cin>>a>>b;--a;--b;
		graph[a].pb(b);
		graph[b].pb(a);
	}
	dfs(0, -1, 0);
	cout<<dp[0];
}
