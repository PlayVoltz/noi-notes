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
#include <bitset>
using namespace std;

#define int long long
#define pii pair<int, int>
#define mp make_pair
#define pb push_back

vector<vector<pii> > graph;
vector<vector<int> > dp;
vector <int> subtree;

void dfs(int node, int par){
	for (auto num:graph[node]){
		if (num.first!=par){
			dfs(num.first, node);
			subtree[node]+=subtree[num.first];
		}
	}
	dp[node][0]=0;
	dp[node][1]=0;
	int s=1;
	for (auto num:graph[node]){
		for (int i=s; i>0; --i){
			for (int j=1; j<=subtree[num.first]; ++j){
				dp[node][i+j]=min(dp[node][i+j], dp[node][i]+dp[num.first][j]+2*num.second);
			}
		}
		s+=subtree[num.first];
	}
}

int32_t main(){
	int n, a, b, c;
	cin>>n;
	graph.resize(n);
	dp.resize(n, vector <int>(n+1, LLONG_MAX/2));
	subtree.resize(n, 1);
	for (int i=1; i<n; ++i){
		cin>>a>>b>>c;--a;--b;
		graph[a].pb(mp(b, c));
		graph[b].pb(mp(a, c));
	}
	dfs(0, -1);
	for (int i=2; i<=n; ++i){
		cout<<dp[0][i]<<"\n";
	}
}
