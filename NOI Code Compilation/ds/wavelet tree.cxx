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
	int kth(int l, int r, int k){
		if (l>r)return 0;
		if (s==e)return s;
		if (k<=b[r]-b[l-1])return left->kth(b[l-1]+1, b[r], k);
		return right->kth(l-b[l-1], r-b[r], k-(b[r]-b[l-1]));
	}
	int lte(int l, int r, int k){
		if (l>r||k<s)return 0;
		if (e<=k)return r-l+1;
		return left->lte(b[l-1]+1, b[r], k)+right->lte(l-b[l-1], r-b[r], k);
	}
	int mte(int l, int r, int k){
		if (l>r||k>e)return 0;
		if (k<=s)return r-l+1;
		return left->mte(b[l-1]+1, b[r], k)+right->mte(l-b[l-1], r-b[r], k);
	}
	int count(int l, int r, int k){
		if (l>r||s>k||e<k)return 0;
		if (s==e)return r-l+1;
		if (k<=m)return left->count(b[l-1]+1, b[r], k);
		return right->count(l-b[l-1], r-b[r], k);
	}
}*wt;

int32_t main(){
	int n, q, mn=LLONG_MAX/2, mx=LLONG_MIN/2, a, b;
	cin>>n>>q;
	vector<int> vect(n);
	for (int i=0; i<n; ++i)cin>>vect[i], mx=max(mx, vect[i]), mn=min(mn, vect[i]);
	wt = new wavelet_tree(vect, mn, mx);
	while (q--){
		cin>>a>>b;
		int low=0, high=b-a+2;
		while (low+1<high){
			int mid=(low+high)/2;
			if (wt->mte(a, b, mid)>=mid)low=mid;
			else high=mid;
		}
		cout<<low<<"\n";
	}
}
