#include <bits/stdc++.h>
using namespace std;

#define int long long

struct node{
	int s, e, m, val, lazy;
	node *l, *r;
	void create(){
		if (l==nullptr){
			l = new node(s, m);
			r = new node(m+1, e);
		}
	}
	void propagate(){
		val+=lazy*(e-s+1);
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
			val=l->val+r->val;
		}
		
	}
	int query(int left, int right){
		propagate();
		if (s==left && e==right)return val;
		create();
		if (right<=m)return l->query(left, right);
		else if (left>m)return r->query(left, right);
		else return l->query(left, m)+r->query(m+1, right);
	}
}*st;

int32_t main(){
	int n, q, a, b, c, d;
	cin>>n>>q;
	st = new node(1, n);
	while (q--){
		cin>>a;
		if (a==1){
			cin>>b>>c>>d;
			st->up(b, c, d);
		}
		else{
			cin>>b>>c;
			cout<<st->query(b, c)<<"\n";
		}
	}
}
