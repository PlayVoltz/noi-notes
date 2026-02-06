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

#define int long long

struct msum{
	int s, r, l, m;
};

struct node{
	int s, e, m;
	msum val;
	node *l, *r;
	
	node(int S, int E){
		s = S, e = E, m = (s+e)/2;
		val={0, 0, 0, 0};
		if (s!=e){
			l = new node(s, m);
			r = new node(m+1, e);
		}
	}
	void up(int ind, int nv){
		if (s==e)val.s=nv, val.l=val.r=val.m=max(0ll, nv);
		else{
			if (ind<=m)l->up(ind, nv);
			else r->up(ind, nv);
			val.s=r->val.s+l->val.s;
			val.l=max(l->val.l, l->val.s+r->val.l);
			val.r=max(r->val.r, r->val.s+l->val.r);
			val.m=max(max(max(val.r, val.l), max(r->val.m, l->val.m)), r->val.l+l->val.r);
		}
	}
	msum query(int left, int right){
		if (s==left && e==right)return val;
		if (right<=m)return l->query(left, right);
		else if (left>m)return r->query(left, right);
		msum temp, le=l->query(left, right), ri=r->query(left, right);
		temp.s=le.s+ri.s;
		temp.l=max(le.l, le.s+ri.l);
		temp.r=max(ri.r, ri.s+le.r);
		temp.m=max(max(max(temp.l, temp.r), max(ri.m, le.m)), le.r+ri.l);
		return temp;
	}
}*st;

int32_t main(){
	int n, q, a, b;
	cin>>n;
	st = new node(0, n-1);
	for (int i=0; i<n; ++i)cin>>a, st->up(i, a);
	cout<<st->query(0, n-1).m<<"\n";
	cin>>q;
	while (q--){
		cin>>a>>b;
		st->up(a, b);
		cout<<st->query(0, n-1).m<<"\n";
	}
}
