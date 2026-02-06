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
#include <random>
#include <fstream>
using namespace std;

#define int long long
#define pii pair<int, int>
#define mp make_pair
#define pb push_back
#define fi first
#define se second

int n, q;
vector<int> ft;

int query(int i){
	int res=0;
	for (;i>0;i-=i&-i)res+=ft[i];
	return res;
}

void up(int i, int val){
	for (;i<=n;i+=i&-i)ft[i]+=val;
}

int bsta(int val){
	int sum=0, i=0;
	for (int k=(1<<(int)log2(n));k;k>>=1)if (i+k<=n&&sum+ft[i+k]>=val)i+=k, sum+=ft[i], cout<<"{"<<i<<" "<<sum<<" "<<ft[i]<<"}\n";
	return i;
}

int32_t main(){
	cin>>n>>q;
	vector<int> vect(n+1), ans(q);
	ft.resize(n+1, 0);
	vector<vector<pii> > quer(n+1);
	for (int i=1; i<=n; ++i)cin>>vect[i], vect[i]=i-vect[i];
	for (int i=0, a, b; i<q; ++i)cin>>a>>b, quer[n-b].pb(mp(a+1, i));
	for (int i=1; i<=n; ++i){
		if (vect[i]>=0){
			int id=bsta(vect[i]);
			up(1, 1);
			up(min(i, id)+1, -1);
			cout<<"["<<min(i, id)<<"]\n";
		}
		for (auto a:quer[i])ans[a.se]=query(a.fi);
	}
	for (auto a:ans)cout<<a<<"\n";
}
