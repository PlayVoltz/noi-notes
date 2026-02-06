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
using namespace std;

#define int long long
#define pb push_back
#define mp make_pair
#define pii pair<int, int>
#define fi first
#define se second

int n, k;
vector<int> vect;

bool can(int lim){
	vector<int> temp;
	for (int i=0; i<n; ++i){
		if (!i||vect[i]-vect[i-1]>=lim)temp.pb(1);
		else ++temp.back();
	}
	unordered_map<int, int> c;
	for (auto a:temp)++c[a];
	bitset<500005> dp;
	dp[0]=1;
	for (auto [a, b]:c){
		for (int i=0; (1<<i)<=b; b-=(1<<i), ++i)dp|=(dp<<(a*(1<<i)));
		dp|=(dp<<(a*b));
	}
	return dp[k];
}

int32_t main(){
	cin>>n>>k;
	vect.resize(n);
	for (int i=0; i<n; ++i)cin>>vect[i];
	sort(vect.begin(), vect.end());
	int low=0, high=LLONG_MAX/2;
	while (low+1<high){
		int mid=(low+high)/2;
		if (can(mid))low=mid;
		else high=mid;
	}
	cout<<low;
}
