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
	int s, e, m, val;
	node *l, *r;
	
	node(int S, int E){
		s = S, e = E, m = (s+e)/2;
		val=0;
		if (s!=e){
			l = new node(s, m);
			r = new node(m+1, e);
		}
	}
	void up(int ind, int nv){
		if (s==e)val=nv;
		else{
			if (ind<=m)l->up(ind, nv);
			else r->up(ind, nv);
			val = min(l->val, r->val);
		}
	}
	int query(int left, int right){
		if (s==left && e==right)return val;
		if (right<=m)return l->query(left, right);
		else if (left>m)return r->query(left, right);
		else return min(l->query(left, m), r->query(m+1, right));
	}
}*st;

int main(){
	int n, q, a, b, c;
	cin>>n>>q;
	st = new node(0, n-1);
	while (q--){
		cin>>a>>b>>c;
		if (a==1){
			st->up(b, c);
		}
		else{
			cout<<st->query(b, c)<<"\n";
		}
	}
}
