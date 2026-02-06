#include "towns.h"
#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define mp make_pair
#define pii pair<int, int>
#define fi first
#define se second

map<int, map<int, int> > mmm;

int query(int a, int b){
	if (a==b)return 0;
	if (!mmm[min(a, b)][max(a, b)])mmm[min(a, b)][max(a, b)]=getDistance(min(a, b), max(a, b))+1;
	return mmm[min(a, b)][max(a, b)]-1;
}

vector<int> dsu;

int fp(int a){
	if (dsu[a]==-1)return a;
	return dsu[a]=fp(dsu[a]);
}

void merge(int a, int b){
	a=fp(a), b=fp(b);
	if (a!=b)dsu[a]=b;
}

int hubDistance(int n, int sub){
	mmm.clear();
	int mx=-1, a=0, b=0, ans=INT_MAX/2, dia=0;
	for (int i=1; i<n; ++i)if (query(a, i)>mx)mx=query(a, i), b=i;
	for (int i=0; i<n; ++i)dia=max(dia, query(b, i));
	vector<pii> vect;
	for (int i=0; i<n; ++i)vect.pb(mp((query(a, b)+query(b, i)-query(a, i))/2, i)), ans=min(ans, max(vect.back().fi, dia-vect.back().fi));
	sort(vect.begin(), vect.end());
	for (int i=0; i<n; ++i)if (max(vect[i].fi, dia-vect[i].fi)==ans){
		int l=i, r=i, d=vect[i].fi, c=0, count=0, sz=0;
		while (r+1<n&&vect[r+1].fi==d)++r;
		if (l>n/2||n-r-1>n/2)continue;
		dsu.assign(n, -1);
		for (int j=l; j<=r; ++j){
			if (!count)count=1, c=vect[j].se;
			else if (query(vect[j].se, c)!=query(b, vect[j].se)+query(b, c)-2*d)++count, merge(vect[j].se, c);
			else --count;
		}
		vector<bool> ban(n, 0);
		for (int j=l; j<=r; ++j){
			if (ban[fp(vect[j].se)])continue;
			if (fp(c)==fp(vect[j].se)||query(vect[j].se, c)!=query(b, vect[j].se)+query(b, c)-2*d)++sz;
			else ban[fp(vect[j].se)]=1;
		}
		if (sz<=n/2)return ans;
		i=r;
	}
	return -ans;
}
