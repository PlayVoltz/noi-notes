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

struct wavelet_tree{//1 indexed
	int s, e, m;
	wavelet_tree *left, *right;
	vector<int> b;
	
	wavelet_tree(vector<int> vect, int x, int y){
		s=x, e=y, m=(s+e)/2;
		if (s==e||vect.empty())return;
		b.resize(vect.size()+1, 0);
		vector<int> l, r;
		for (int i=0; i<vect.size(); ++i){
			b[i+1]=b[i];
			if (vect[i]<=m)++b[i+1], l.pb(vect[i]);
			else r.pb(vect[i]);
		}
		left = new wavelet_tree(l, s, m);
		right = new wavelet_tree(r, m+1, e);
	}
	void swapadj(int i){
		if (s==e)return;
		b[i]=b[i-1]+b[i+1]-b[i];
		if (b[i+1]-b[i]==b[i]-b[i-1]){
			if (b[i]-b[i-1])left->swapadj(b[i]);
			else right->swapadj(i-b[i]);
		}
	}
	int kth(int l, int r, int k){
		if (l>r)return 0;
		if (s==e)return s;
		if (k<=b[r]-b[l-1])return left->kth(b[l-1]+1, b[r], k);
		return right->kth(l-b[l-1], r-b[r], k-(b[r]-b[l-1]));
	}
}*wt;

int32_t main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n, q, t, a, b, c;
	cin>>n>>q;
	vector<int> vect(n);
	for (int i=0; i<n; ++i)cin>>vect[i];
	wt = new wavelet_tree(vect, *min_element(vect.begin(), vect.end()), *max_element(vect.begin(), vect.end()));
	while (q--){
		cin>>t;
		if (t)cin>>a, wt->swapadj(a);
		else cin>>a>>b>>c, cout<<wt->kth(a, b, b-a-c+2)<<"\n";
	}
}
