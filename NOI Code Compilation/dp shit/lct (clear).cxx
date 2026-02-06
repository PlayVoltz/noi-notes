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

vector<int> pos;

struct line{
	int m, c;
	line (): m(0), c(LLONG_MAX/2){}
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
	void clear() {
        sth = line();
        if(l!=nullptr){
            l->clear();
            r->clear();
        }
    }
	void up(line nl){
		bool left = nl(s)<sth(s), mid = nl(m)<sth(m), right = nl(e)<sth(e);
		if (mid)swap(sth, nl);
		if (e-s==1 || nl==line() || left==right)return;
		create();
		if (left!=mid)l->up(nl);
		else r->up(nl);
	}
	int query(int x){
		if (e-s==1)return sth(x);
		if (l==nullptr)return sth(x);
		if (x<m)return min(sth(x), l->query(x));
		else return min(sth(x), r->query(x));
	}
}*lct;

int32_t main(){
	int n, q, a, b;
	cin>>n>>q;
	vector<int> speed(n, 0);
	pos.resize(n);
	vector<vector<int> > dp(n, vector<int>(n, LLONG_MAX/2));
	vector<vector<pii> > ans(n);
	for (int i=0; i<n-1; ++i)cin>>pos[i]>>speed[i];
	cin>>pos[n-1];
	for (int i=0; i<n; ++i)dp[1][i]=speed[0]*(pos[i]-pos[0]);
	lct = new node(0, 1e9);
	for (int i=2; i<n; ++i){
		lct->clear();
		for (int j=1; j<n; ++j){
			dp[i][j]=lct->query(pos[j]);
			lct->up(line(speed[j], dp[i-1][j]-pos[j]*speed[j]));
		}
	}
	for (int i=1; i<n; ++i){
		ans[i].pb(mp(i, dp[i][n-1]));
		for (int j=2*i; j<n; j+=i)ans[i].pb(mp(j, min(dp[j][n-1], ans[i].back().se)));
	}
	while (q--){
		cin>>a>>b;
		if (a>=n)cout<<"-1\n";
		else{
			int low=-1, high=ans[a].size(), res=-1;
			while (low+1<high){
				int mid=(low+high)/2;
				if (ans[a][mid].se<=b)high=mid, res=ans[a][mid].fi;
				else low=mid;
			};
			cout<<res<<"\n";
		}
	}
}
