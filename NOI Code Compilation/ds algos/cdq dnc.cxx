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
#include <cstring>
using namespace std;

#define int long long
#define pii pair<int, int>
#define mp make_pair
#define pb push_back

struct trio{
	int id, c, val;
};

struct quad{
	int l, r, c, t;
};

bool custom(quad a, quad b){
	return a.t<b.t;
}

bool custom2(quad a, quad b){
	return a.c<b.c;
}

bool custom3(trio a, trio b){
	return a.c<b.c;
}

int n;
vector<vector<trio> > update;
vector<vector<quad> > query;
vector<int> ans, ft;
vector<quad> tempq;
vector<trio> tempu;

int ftsum(int index){
	int sum = 0;
	while (index>0){
		sum+=ft[index];
		index-= index & (-index);
	}
	return sum;
}

void up(int index, int val){
	while (index<=n){
		ft[index]+=val;
		index+=index&(-index);
	}
}

void dnc(int l, int r){
	if (l==r)return;
	int m=(l+r)/2;
	dnc(l, m);
	dnc(m+1, r);
	vector<quad> &lq=query[l], &rq=query[m+1];
	vector<trio> &lu=update[l], &ru=update[m+1];
	int p=0;
	vector<pii> undo;
	for (auto c:rq){
		while (p<lu.size()&&lu[p].c<=c.c)up(lu[p].id, lu[p].val), undo.pb(mp(lu[p].id, -lu[p].val)), ++p;
		ans[c.t]+=ftsum(c.r)-ftsum(c.l-1);
	}
	for (auto a:undo)up(a.first, a.second);
	merge(lq.begin(), lq.end(), rq.begin(), rq.end(), back_inserter(tempq), custom2);
	merge(lu.begin(), lu.end(), ru.begin(), ru.end(), back_inserter(tempu), custom3);
	swap(lq, tempq);
	swap(lu, tempu);
	tempq.clear();
	tempu.clear();
}

int32_t main(){
	int q, a, b, c, d;
	cin>>n>>q;
	ft.resize(n+1, 0);
	vector<int> vect(n+1);
	ans.resize(q+1, 0);
	update.resize(q+1);
	query.resize(q+1);
	for (int i=1; i<=n; ++i){
		cin>>vect[i];
		update[0].pb({i, vect[i], 1});
	}
	sort(update[0].begin(), update[0].end(), custom3);
	for (int i=1; i<=q; ++i){
		cin>>a;
		if (a==1){
			cin>>b>>c>>d;
			query[i].pb({b, c, d, i});
		}
		else{
			cin>>b>>c;
			update[i].pb({b, vect[b], -1});
			update[i].pb({b, c, 1});
			sort(update[i].begin(), update[i].end(), custom3);
			vect[b]=c;
		}
	}
	dnc(0, q);
	sort(query[0].begin(), query[0].end(), custom);
	for (auto a:query[0])cout<<ans[a.t]<<"\n";
}
