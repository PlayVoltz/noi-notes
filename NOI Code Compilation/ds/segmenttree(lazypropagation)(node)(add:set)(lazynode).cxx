#include <iostream>
#include <map>
#include <vector>
#include <climits>
#include <stack>
#include <string>
#include <queue>
#include <algorithm>
#include <set>
#include <unordered_map>
#include <cmath>
#include <cctype>
#include <unordered_set>
using namespace std;

struct node{
	int s, e, m, val, lazyset, lazyadd;
	node *l, *r;
	void create(){
		if (l==nullptr){
			l = new node(s, m);
			r = new node(m+1, e);
		}
	}
	void propagate(){
		if (lazyset!=-1)val=lazyset*(e-s+1);
		val+=lazyadd*(e-s+1);
		if (s!=e){
			create();
			if (lazyset!=-1){
				l->lazyset=lazyset;
				r->lazyset=lazyset;
				l->lazyadd=r->lazyadd=0;
			}
			if (lazyadd){
				l->lazyadd+=lazyadd;
				r->lazyadd+=lazyadd;
			}
		}
		lazyset=-1;
		lazyadd=0;
	}
	node(int S, int E){
		s = S, e = E, m = (s+e)/2;
		val=lazyadd=0;
		lazyset=-1;
		l=r=nullptr;
	}
	void upset(int left, int right, int v){
		propagate();
		if (s==left && e==right)lazyadd=0, lazyset=v;
		else{
			create();
			if (right<=m)l->upset(left, right, v);
			else if (left>m)r->upset(left, right, v);
			else l->upset(left, m, v), r->upset(m+1, right, v);
			r->propagate(), l->propagate();
			val=l->val+r->val;
		}
	}
	void upadd(int left, int right, int v){
		propagate();
		if (s==left && e==right)lazyadd+=v;
		else{
			create();
			if (right<=m)l->upadd(left, right, v);
			else if (left>m)r->upadd(left, right, v);
			else l->upadd(left, m, v), r->upadd(m+1, right, v);
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

int main(){
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
