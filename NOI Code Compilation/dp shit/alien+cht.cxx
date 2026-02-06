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
#define pb push_back

int n;
pii ans;
vector<int> vect, psum;

struct line{
	int m, c, id;
	line (int m, int c, int id): m(m), c(c), id(id){}
	int operator()(int x){return m*x+c;}
};

deque <line> cht;

pii query(int x){
	while (cht.size()>1){
		if (cht[0](x)>cht[1](x))cht.pop_front();
		else break;
	}
	return mp(cht[0](x), cht[0].id);
}

long double intersect(line a, line b){
	return (long double)(b.c-a.c)/(a.m-b.m);
}

void insert(int m, int c, int id){
	line l = line(m, c, id);
	while (!cht.empty()&&cht.back().m==m){
		if (cht.back().c>c)cht.pop_back();
		else return;
	}
	while (cht.size()>1){
		int s = cht.size();
		if (intersect(cht[s-1], l)<=intersect(cht[s-2], l))cht.pop_back();
		else break;
	}
	cht.push_back(l);
}

void fertile(int pen){
	cht.clear();
	vector<pii> dp(n+1);
	dp[0]=mp(0, 0);
	ans=mp(LLONG_MAX/2, LLONG_MAX/2);
	for (int i=1; i<=n; ++i){
		insert(-vect[i-1], dp[i-1].first+i*vect[i-1]-psum[i-1], dp[i-1].second);
		pii res=query(i);
		dp[i]=mp(psum[i-1]+res.first+pen, res.second+1);
		ans=min(ans, mp(dp[i].first+psum[n]-psum[i]-vect[i]*(n-i), dp[i].second));
	}
}

int32_t main(){
	int k;
	cin>>n>>k;
	vect.resize(n+1, 0);
	psum.resize(n+1, 0);
	for (int i=1; i<=n; ++i)cin>>vect[i], psum[i]=psum[i-1]+vect[i];
	int low=-1, high=psum[n]+1;
	while (low+1<high){
		int mid=(low+high)/2;
		fertile(mid);
		if (ans.second<=k)high=mid;
		else low=mid;
	}
	fertile(high);
	cout<<ans.first-k*high;
}
