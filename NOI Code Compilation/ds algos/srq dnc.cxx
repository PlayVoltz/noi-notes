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
#include <iostream>
#include <unordered_map>
#include <cmath>
#include <cctype>
#include <bitset>
#include <iomanip>
#include <cstring>
using namespace std;

#define int long long
#define pii pair<int, bool>
#define mp make_pair
#define pb push_back
#define fi first
#define se second

struct quer{
	int a, b, x, id;
};

int k=0;
vector<int> w, val, ans;
vector<vector<int> > dp;

void dnc(int l, int r, vector<quer> query){
	if (l==r||query.empty())return;
	int m=(l+r)/2;
	for (int i=0; i<=k; ++i)dp[m][i]=(w[m]<=i?val[m]:0), dp[m+1][i]=(w[m+1]<=i?val[m+1]:0);
	for (int i=m+2; i<=r; ++i)for (int j=0; j<=k; ++j)dp[i][j]=max(dp[i-1][j], (w[i]<=j?dp[i-1][j-w[i]]+val[i]:0));
	for (int i=m-1; i>=l; --i)for (int j=0; j<=k; ++j)dp[i][j]=max(dp[i+1][j], (w[i]<=j?dp[i+1][j-w[i]]+val[i]:0));
	vector<quer> left, right;
	for (auto c:query){
		if (c.a<=m&&c.b>m)for (int i=0; i<=c.x; ++i)ans[c.id]=max(ans[c.id], dp[c.a][i]+dp[c.b][c.x-i]);
		else if (c.b<=m)left.pb(c);
		else right.pb(c);
	}
	dnc(l, m, left);
	dnc(m+1, r, right);
}

int32_t main(){
	int n, q, a, b, c;
	cin>>n;
	w.resize(n+1);
	val.resize(n+1);
	vector<quer> query;
	for (int i=1; i<=n; ++i)cin>>w[i]>>val[i];
	cin>>q;
	ans.resize(q, 0);
	for (int i=0; i<q; ++i){
		cin>>a>>b>>c;
		if (a==b)ans[i]=(w[a]<=c?val[a]:0);
		else query.pb({a, b, c, i});
		k=max(k, c);
	}
	dp.resize(n+1, vector<int>(k+1));
	dnc(1, n, query);
	for (int i=0; i<q; ++i)cout<<ans[i]<<"\n";
}
