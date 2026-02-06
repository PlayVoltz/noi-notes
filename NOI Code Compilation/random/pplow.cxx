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

struct ooga{
	int x, l, r, v;
};

bool custom(ooga a, ooga b){
	return a.x<b.x;
}

struct node{
	int s, e, m, val, lazy, count;
	node *l, *r;
	void create(){
		if (l==nullptr){
			l = new node(s, m);
			r = new node(m+1, e);
		}
	}
	void propagate(){
		val+=lazy;
		if (s!=e){
			create();
			l->lazy+=lazy;
			r->lazy+=lazy;
		}
		lazy=0;
	}
	node(int S, int E){
		s = S, e = E, m = (s+e)/2;
		val=lazy=0;
		count=e-s+1;
		l=r=nullptr;
	}
	void up(int left, int right, int v){
		propagate();
		if (s==left && e==right)lazy+=v;
		else{
			create();
			if (right<=m)l->up(left, right, v);
			else if (left>m)r->up(left, right, v);
			else l->up(left, m, v), r->up(m+1, right, v);
			r->propagate(), l->propagate();
			if (l->val<r->val)val=l->val, count=l->count;
			else if (l->val>r->val)val=r->val, count=r->count;
			else val=r->val, count=l->count+r->count;
		}
		
	}
	int query(int left, int right){//idk
		propagate();
		if (s==left && e==right){
			if (!val)return e-s+1-count;
			return e-s+1;
		}
		create();
		if (right<=m)return l->query(left, right);
		else if (left>m)return r->query(left, right);
		else return l->query(left, m)+r->query(m+1, right);
	}
}*st;

int32_t main(){
	int n, m, q, a, b, c, d, cc=0, ans=0;
	cin>>n>>m>>q;
	vector<ooga> vect;
	while (q--){
		cin>>a>>b>>c>>d;
		vect.pb({a, b, d, 1});
		vect.pb({c+1, b, d, -1});
	}
	sort(vect.begin(), vect.end(), custom);
	st = new node(1, 1e9);
	for (int i=0; i<vect.size(); ++i){
		if(i)ans+=(vect[i].x-vect[i-1].x)*cc;
		st->up(vect[i].l, vect[i].r, vect[i].v);
		cc=st->query(1, 1e9);
	}
	cout<<ans;
}
