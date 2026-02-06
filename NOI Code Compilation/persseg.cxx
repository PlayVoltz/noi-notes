#include "rarwall.h"
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
	node (int S, int E){
		s = S, e = E, m = (s+e)/2;
		val=lazy=0;
		l=r=nullptr;
	}
	node * copy(){
		node * res = new node(s, e);
		res->l=l;
		res->r=r;
		res->val=val;
		res->lazy=lazy;
		return res;
	}
	node * up(int left, int right, int v){
		if (s==left && e==right){
			node * res=copy();
			res->lazy+=v;
			return res;
		}
		create();
		node * res=copy();
		if (right<=m)res->l=l->up(left, right, v);
		else if (left>m)res->r=r->up(left, right, v);
		else{
			res->l=l->up(left, m, v);
			res->r=r->up(m+1, right, v);
		}
		res->val=max(res->l->val+res->l->lazy, res->r->val+res->r->lazy);
		return res;
	}
	int query(int left, int right){
		if (s==left&&e==right)return val+lazy;
		if (right<=m)return (l==nullptr?0:l->query(left, right))+lazy;
		else if (left>m)return (r==nullptr?0:r->query(left, right))+lazy;
		return max((l==nullptr?0:l->query(left, m)), (r==nullptr?0:r->query(m+1, right)))+lazy;
	}
}*st[100005];

void init(signed n, signed m, signed q){
	st[0]=new node(0, n-1);
}

void proposal(signed i, signed p, signed a, signed b, signed c){
	st[i]=st[p]->up(a, b, c);
}

long long max_height(signed i, signed a, signed b){
	return st[i]->query(a, b);
}
