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
#define pii pair<int, int>
#define mp make_pair
#define pb push_back
#define fi first
#define se second

const int MOD = 1e9+7;

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
}*stmin;

struct node2{
	int s, e, m;
	pii val;
	node2 *l, *r;
	
	node2(int S, int E){
		s = S, e = E, m = (s+e)/2;
		val=mp(0, 0);
		if (s!=e){
			l = new node2(s, m);
			r = new node2(m+1, e);
		}
	}
	void up(int ind, int nv, int id){
		if (s==e)val=mp(nv, id);
		else{
			if (ind<=m)l->up(ind, nv, id);
			else r->up(ind, nv, id);
			val = max(l->val, r->val);
		}
	}
	pii query(int left, int right){
		if (s==left && e==right)return val;
		if (right<=m)return l->query(left, right);
		else if (left>m)return r->query(left, right);
		else return max(l->query(left, m), r->query(m+1, right));
	}
}*stmax;

struct node3{
	int s, e, m, val;
	node3 *l, *r;
	
	node3(int S, int E){
		s = S, e = E, m = (s+e)/2;
		val=0;
		if (s!=e){
			l = new node3(s, m);
			r = new node3(m+1, e);
		}
	}
	void up(int ind, int nv){
		if (s==e)val=nv;
		else{
			if (ind<=m)l->up(ind, nv);
			else r->up(ind, nv);
			val = l->val+r->val;
		}
	}
	int query(int left, int right){
		if (s==left && e==right)return val;
		if (right<=m)return l->query(left, right);
		else if (left>m)return r->query(left, right);
		else return l->query(left, m)+r->query(m+1, right);
	}
}*st;

int n, k;
vector<int> fact, vect;
unordered_map<int, vector<int> > arr;

int inv(int num){
	int p=MOD, res=1, y=0;
	while (num>1){
		int q=num/p, t=p;
		p=num%p, num=t, t=y, y=res-q*y, res=t;
	}
	if (res<0)res+=MOD;
	return res;
}

int ncr(int n, int r){
	return (fact[n]*inv(fact[r]*fact[n-r])%MOD)%MOD;
}

int f(int l, int r){
	if (l>=r)return 1;
	int mn=stmin->query(l, r);
	pii mx=stmax->query(l, r);
	if (mn==LLONG_MAX/2)return 1;
	if (mn+mx.fi<=k){
		int c=0, a=st->query(l, r);
		vector<int> temp=arr[mn];
		for (int i=(lower_bound(temp.begin(), temp.end(), l)-temp.begin()); i<(upper_bound(temp.begin(), temp.end(), r)-temp.begin()); ++i)++c, stmin->up(temp[i], LLONG_MAX/2), st->up(temp[i], 0);
		return (f(l, r)*ncr(a, c))%MOD;
	}
	return (f(l, mx.se-1)*f(mx.se+1, r))%MOD;
}

int32_t main(){
	cin>>n>>k;
	vect.resize(n);
	fact.resize(n+1, 1);
	stmin = new node(0, n-1);
	stmax = new node2(0, n-1);
	st = new node3(0, n-1);
	for (int i=0; i<n; ++i)cin>>vect[i], fact[i+1]=(fact[i]*(i+1))%MOD, stmin->up(i, vect[i]), stmax->up(i, vect[i], i), st->up(i, 1), arr[vect[i]].pb(i);
	cout<<f(0, n-1);
}
