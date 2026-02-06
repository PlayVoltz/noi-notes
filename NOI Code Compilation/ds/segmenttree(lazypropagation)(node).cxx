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
	int s, e, m, val, lazy;
	node *l, *r;
	void propagate(){
		if (lazy==0)return;
		val+=lazy*(e-s+1);
		if (s!=e){
			l->lazy+=lazy;
			r->lazy+=lazy;
		}
		lazy=0;
	}
	node(int S, int E){
		s = S, e = E, m = (s+e)/2;
		val=0;
		lazy=0;
		if (s!=e){
			l = new node(s, m);
			r = new node(m+1, e);
		}
	}
	void up(int left, int right, int v){
		if (s==left && e==right)lazy+=v;
		else{
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
		if (right<=m)return l->query(left, right);
		else if (left>m)return r->query(left, right);
		else return l->query(left, m)+r->query(m+1, right);
	}
}*segmenttree;

int main(){
	int n;
	cin>>n;
	segmenttree = new node(0, n-1);
	segmenttree->up(3, 5, 1);
	cout<<segmenttree->query(0, n-1);
}
