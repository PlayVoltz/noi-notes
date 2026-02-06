#include <bits/stdc++.h>
using namespace std;

//oset.find_by_order(id) finds the iterator at index id in logn time (0 indexed)
//oset.order_of_key(num) its like lower_bound but exclusive of the input number
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template<class T> using oset=tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

#define pii pair<int,int>
#define mp make_pair
#define pb push_back

bool custom(pii a, pii b){
	if (a.first==b.first)return a.second<b.second;
	return a.first>b.first;
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n, q, c, d;
	cin>>n;
	vector<int> a(n);
	vector<pii> vect(n);
	vector<vector<pii> > query(n);
	for (int i=0; i<n; ++i)cin>>a[i], vect[i].second=i, vect[i].first=a[i];
	sort(vect.begin(), vect.end(), custom);
	cin>>q;
	vector<int> ans(q);
	for (int i=0; i<q; ++i){
		cin>>c>>d;--c,--d;
		query[c].pb(mp(d, i));
	}
	oset<int>s;
	for (int i=0; i<n; ++i){
		s.insert(vect[i].second);
		for (auto num:query[i])ans[num.second]=a[*s.find_by_order(num.first)];
	}
	for (auto num:ans)cout<<num<<"\n";
}
