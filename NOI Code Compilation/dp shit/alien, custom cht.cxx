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
using namespace std;

#define int unsigned long long
#define pii pair<int, int>
#define mp make_pair
#define pb push_back
#define fi first
#define se second

struct trio{
	int id, l, r;
};

int n;
deque <trio> cht;
vector<int> dp, psum, c;

int f(int j, int i){
	return dp[j]+(i-j)*(psum[i]-psum[j]);
}

void insert(int i, int j){
	if (cht.empty()){
		cht.pb({j, i, n});
		return;
	}
	if (cht.front().r<i)cht.pop_front();
	else cht.front().l=i;
	while (!cht.empty()&&f(cht.back().id, cht.back().l)>f(j, cht.back().l))cht.pop_back();//use > if find min and < if find max
	if (cht.empty())cht.pb({j, i, n});
	else{
		int low=cht.back().l-1, high=cht.back().r+1;
		while (low+1<high){
			int mid=(low+high)/2;
			if (f(cht.back().id, mid)>f(j, mid))high=mid;//use > if find min and < if find max
			else low=mid;
		}
		cht.back().r=high-1;
		if (high!=n+1)cht.pb({j, high, n});
	}
}

void alien(int pen){
	cht.clear();
	c[0]=dp[0]=0;
	for (int i=1; i<=n; ++i){
		insert(i, i-1);
		dp[i]=f(cht.front().id, i)+pen;
		c[i]=c[cht.front().id]+1;
	}
}


int32_t main(){
	int k;
	cin>>n>>k;
	psum.resize(n+1, 0);
	dp.resize(n+1);
	c.resize(n+1);
	for (int i=1; i<=n; ++i)cin>>psum[i], psum[i]+=psum[i-1];
	int low=0, high=1e19;
	while (low+1<high){
		int mid=(low+high)/2;
		alien(mid);
		if (c[n]<=k)high=mid;
		else low=mid;
	}
	alien(high);
	cout<<dp[n]-k*high;
}
