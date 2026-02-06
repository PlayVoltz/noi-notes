#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main(){
	int n, w;
	cin>>n>>w;
	vector<int> val(n+1), weight(n+1);
	vector<vector<int> > dp(n+1, vector<int>(w+1, 0));
	for (int i=1; i<=n; ++i)cin>>weight[i]>>val[i];
	for (int i=1; i<=n; ++i){
		for (int j=0; j<=w; ++j){
			dp[i][j]=dp[i-1][j];
			if (j>=weight[i])dp[i][j]=max(dp[i][j], dp[i-1][j-weight[i]]+val[i]);
		}
	}
	cout<<dp[n][w];
}
