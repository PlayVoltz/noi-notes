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
using namespace std;

#define int long long
#define pii pair<int, int>
#define mp make_pair
#define pb push_back
#define fi first
#define se second

struct upd{
	int l, r, v;
};

struct quer{
	int l, r, i;
};

struct fen{
	int n;
	vector<int> ft1, ft2;
	fen(int N){
		n=N;
		ft1.resize(n+1, 0);
		ft2.resize(n+1, 0);
	}
	void up(int l, int r, int v){
		for (int i=l; i<=n; i+=i&-i)ft1[i]+=v, ft2[i]-=v*(l-1);
		for (int i=r+1; i<=n; i+=i&-i)ft1[i]-=v, ft2[i]+=v*r;
	}
	int sum(int i){
		int res=0;
		for (int p=i;p;p-=p&-p)res+=ft1[p]*i+ft2[p];
		return res;
	}
	int query(int l, int r){
		return sum(r)-sum(l-1);
	}
}*ft1, *ft2;

int32_t main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n, u, q, a, b, c, d, e;
	cin>>n>>u>>q;
	vector<vector<upd> > update1(n+2), update2(n+2);
	vector<vector<quer> > queries(n+2);
	vector<int> ans(q+1, 0);
	while (u--){
		cin>>a>>b>>c>>d>>e;
		update1[a].pb({c, d, e}), update1[b+1].pb({c, d, -e});
		update2[a].pb({c, d, -e*(a-1)}), update2[b+1].pb({c, d, e*b});
	}
	for (int i=1; i<=q; ++i)cin>>a>>b>>c>>d, queries[a-1].pb({c, d, -i}), queries[b].pb({c, d, i});
	ft1 = new fen(n);
	ft2 = new fen(n);
	for (int i=1; i<=n; ++i){
		for (auto c:update1[i])ft1->up(c.l, c.r, c.v);
		for (auto c:update2[i])ft2->up(c.l, c.r, c.v);
		for (auto c:queries[i]){
			if (c.i<0)ans[-c.i]-=ft1->query(c.l, c.r)*i+ft2->query(c.l, c.r);
			else ans[c.i]+=ft1->query(c.l, c.r)*i+ft2->query(c.l, c.r);
		}
	}
	for (int i=1; i<=q; ++i)cout<<ans[i]<<"\n";
}
