#include <bits/stdc++.h>
using namespace std;

#define int long long

struct line{
	int m, c;
	line (): m(0), c(LLONG_MIN){}//for min change LLONG_MIN to LLONG_MAX
	line (int m, int c): m(m), c(c){}
	int operator()(int x){return m*x+c;}
	bool operator==(line y){return m==y.m&&c==y.c;}
};

struct node{
	int s, e, m;
	line sth;
	node *l, *r;
	node(int s, int e): s(s), e(e), m((s+e)/2), l(nullptr), r(nullptr){}
	void create(){
		if (l!=nullptr)return;
		l = new node(s, m);
		r = new node(m, e);
	}
	void up(line nl){
		bool left = nl(s)>sth(s), mid = nl(m)>sth(m), right = nl(e)>sth(e);//for min change all > to <
		if (mid)swap(sth, nl);
		if (e-s==1 || nl==line() || left==right)return;
		create();
		if (left!=mid)l->up(nl);
		else r->up(nl);
	}
	int query(int x){
		if (e-s==1)return sth(x);
		if (l==nullptr)return sth(x);
		if (x<m)return max(sth(x), l->query(x));//for min change max to min
		else return max(sth(x), r->query(x));//for min change max to min
	}
}*lct;

int32_t main(){
	int q, a, b, c;
	cin>>q;
	lct = new node(INT_MIN, INT_MAX);
	while (q--){
		cin>>a;
		if (a==1){
			cin>>b>>c;
			lct->up(line(b, c));
		}
		else{
			cin>>b;
			cout<<lct->query(b)<<"\n";
		}
	}
}
