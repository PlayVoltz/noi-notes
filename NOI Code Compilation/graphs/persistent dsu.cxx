#include "swap.h"
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

#define pb push_back
#define mp make_pair
#define pii pair<int, int>
#define fi first
#define se second

vector<int> tt, s, e, line, sz;
vector<vector<pii> > dsu;

int fp(int t, int node){
	int id = (upper_bound(dsu[node].begin(), dsu[node].end(), mp(t, INT_MAX/2))-dsu[node].begin())-1;
	if (dsu[node][id].se==-1)return node;
	return fp(t, dsu[node][id].se);
}

void merge(int t, int a, int b){
	int aa=a, bb=b;
	a=fp(t, a), b=fp(t, b);
	if (a==b){
		line[a]=min(line[a], t);
		return;
	}
	if (sz[a]<sz[b])swap(a, b);
	line[a]=min(line[a], max(line[b], t));
	if ((s[a]==aa&&s[b]==bb)||(s[a]==bb&&s[b]==aa))s[a]=e[b];
	else if ((e[a]==aa&&e[b]==bb)||(e[a]==bb&&e[b]==aa))e[a]=s[b];
	else if ((s[a]==aa&&e[b]==bb)||(s[a]==bb&&e[b]==aa))s[a]=s[b];
	else if ((e[a]==aa&&s[b]==bb)||(e[a]==bb&&s[b]==aa))e[a]=e[b];
	else line[a]=min(line[a], t);
	sz[a]+=sz[b];
	dsu[b].pb(mp(t, a));
}

void init(int n, int m, vector<int> u, vector<int> v, vector<int> w){
	vector<pair<int, pii> > edges;
	for (int i=0; i<m; ++i)edges.pb(mp(w[i], mp(u[i], v[i]))), tt.pb(w[i]);
	sort(edges.begin(), edges.end());
	sort(tt.begin(), tt.end());
	tt.erase(unique(tt.begin(), tt.end()), tt.end());
	s.resize(n);
	e.resize(n);
	dsu.resize(n);
	sz.resize(n, 1);
	line.resize(n, tt.size());
	for (int i=0; i<n; ++i)s[i]=e[i]=i, dsu[i].pb(mp(-1, -1));
	for (int i=0, p=0; i<tt.size(); ++i)while (p<edges.size()&&edges[p].fi==tt[i])merge(i, edges[p].se.fi, edges[p].se.se), ++p;
}

int getMinimumFuelCapacity(int x, int y){
	int low=-1, high=tt.size();
	while(low+1<high){
		int mid=(low+high)/2, a=fp(mid, x), b=fp(mid, y);
		if (a==b&&line[a]<=mid)high=mid;
		else low=mid;
	}
	return (high==tt.size()?-1:tt[high]);
}
