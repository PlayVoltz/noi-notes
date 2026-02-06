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
#define fi first
#define se second

struct trio{
	int l, r, id;
};

vector<int> closest;
vector<vector<int> > lefts, rights;
vector<bool> ans;

void dnc(int l, int r, vector<trio> query){
	if (query.empty())return;
	if (l==r){
		bool can=0;
		for (auto c:rights[l])can=(can||l==c);
		for (auto c:query)ans[c.id]=can;
		return;
	}
	int m=(l+r)/2;
	stack<pii> st;
	for (int i=m; i>=l; --i){
		int low=-1, high=LLONG_MAX/2;
		for (auto num:rights[i]){
			if (num>=m)high=min(high, num);
			else low=max(low, num);
		}
		closest[i]=high;
		while (!st.empty()&&(st.top().first<=low+1||closest[i]<=st.top().second))closest[i]=min(closest[i], st.top().second), st.pop();
		st.push(mp(i, closest[i]));
	}
	while (!st.empty())st.pop();
	for (int i=m+1; i<=r; ++i){
		int low=-1, high=LLONG_MAX/2;
		for (auto num:lefts[i]){
			if (num<=m+1)low=max(low, num);
			else high=min(high, num);
		}
		closest[i]=low;
		while (!st.empty()&&(st.top().first>=high-1||closest[i]>=st.top().second))closest[i]=max(closest[i], st.top().second), st.pop();
		st.push(mp(i, closest[i]));
	}
	vector<trio> lq, rq;
	for (auto c:query){
		if (c.l<=m&&c.r>=m+1)ans[c.id]=(closest[c.l]<=c.r&&closest[c.r]>=c.l);
		else if (c.r<=m)lq.pb(c);
		else rq.pb(c);
	}
	dnc(l, m, lq);
	dnc(m+1, r, rq);
}

int32_t main(){
	int n, m, q, l, r;
	cin>>n>>m>>q;
	ans.resize(q);
	lefts.resize(n+1);
	rights.resize(n+1);
	closest.resize(n+1);
	vector<trio> query;
	for (int i=0; i<m; ++i){
		cin>>l>>r;
		rights[l].pb(r);
		lefts[r].pb(l);
	}
	for (int i=0; i<q; ++i){
		cin>>l>>r;
		query.pb({l, r, i});
	}
	dnc(1, n, query);
	for (auto a:ans)cout<<(a?"YES\n":"NO\n");
}
