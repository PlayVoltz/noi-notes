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

int vect[(1<<20)+5];

struct node{
	int s, e, m, val, lazy, layer;
	node *l, *r;
	
	void propagate(){
		if (lazy==-1)return;
		val=lazy*(e-s+1);
		if (s!=e){
			l->lazy=lazy;
			r->lazy=lazy;
		}
		lazy=-1;
	}
	node(int S, int E){
		s = S, e = E, m = (s+e)/2;
		lazy=-1;
		if (s!=e){
			l = new node(s, m);
			r = new node(m+1, e);
			val=l->val+r->val;
			layer=l->layer+1;
		}
		else val=vect[s], layer=-1;
	}
	void up(int left, int right, int k, int v){
		propagate();
		if (s==left && e==right)lazy=v;
		else{
			if (k&(1<<layer)){
				if (right<=m)r->up(m+1+(left-s), m+1+(right-s), k, v);
				else if (left>m)l->up(s+left-m-1, s+right-m-1, k, v);
				else l->up(s, s+right-m-1, k, v), r->up(m+1+(left-s), e, k, v);
			}
			else{
				if (right<=m)l->up(left, right, k, v);
				else if (left>m)r->up(left, right, k, v);
				else l->up(left, m, k, v), r->up(m+1, right, k, v);
			}
			r->propagate(), l->propagate();
			val=l->val+r->val;
		}
		
	}
	int query(int left, int right, int k){
		propagate();
		if (s==left && e==right)return val;
		if (k&(1<<layer)){
			if (right<=m)return r->query(m+1+(left-s), m+1+(right-s), k);
			else if (left>m)return l->query(s+left-m-1, s+right-m-1, k);
			return l->query(s, s+right-m-1, k)+r->query(m+1+(left-s), e, k);
		}
		else{
			if (right<=m)return l->query(left, right, k);
			else if (left>m)return r->query(left, right, k);
			return l->query(left, m, k)+r->query(m+1, right, k);
		}
	}
}*st;

int32_t main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n, q, t, l, r, k, v;
	cin>>n;
	for (int i=0; i<(1<<n); ++i)cin>>vect[i];
	st = new node(0, (1<<n)-1);
	cin>>q;
	while (q--){
		cin>>t;
		if (t==1)cin>>l>>r>>k>>v, st->up(l, r, k, v);
		else cin>>l>>r>>k, cout<<st->query(l, r, k)<<"\n";
	}
}
