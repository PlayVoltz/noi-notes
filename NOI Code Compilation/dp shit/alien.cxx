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
#define pii pair<int, int>
#define mp make_pair

int n;
vector<int> vect, psum;
vector<pii> dp;

pii pmax(pii a, pii b){
	if (a.first==b.first)return a.second<b.second?a:b;
	return a.first>b.first?a:b;
}

pii feast(int pen){
	dp[0]=mp(0, 0);
	pii best=mp(0, 0);
	for (int i=1; i<=n; ++i){
		dp[i]=pmax(dp[i-1], mp(best.first+psum[i]-pen, best.second+1));
		best=pmax(best, mp(dp[i].first-psum[i], dp[i].second));
	}
	return dp[n];
}

int32_t main(){
	int k;
	cin>>n>>k;
	vect.resize(n+1);
	dp.resize(n+1);
	psum.resize(n+1, 0);
	for (int i=1; i<=n; ++i)cin>>vect[i], psum[i]=psum[i-1]+vect[i];
	int low=-1, high=LLONG_MAX/100000;
	while (low+1<high){
		int mid = (low+high)/2;
		if (feast(mid).second>=k)low=mid;
		else high=mid;
	}
	pii res=feast(low);
	cout<<res.first+res.second*low;
}
