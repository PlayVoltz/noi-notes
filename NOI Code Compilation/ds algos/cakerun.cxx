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
#define fi first
#define se second

int32_t main(){
	int n, m, q, l, r, t=0;
	cin>>n>>m>>q;
	set<pair<int, pii> > s;
	unordered_map<int, int> temp;
	vector<pii> ans;
	s.insert(mp(LLONG_MAX/2, mp(LLONG_MAX/2, LLONG_MAX/2)));
	s.insert(mp(LLONG_MIN/2, mp(LLONG_MIN/2, LLONG_MIN/2)));
	while (m--){
		cin>>l>>r;
		auto it = s.upper_bound(mp(r, mp(LLONG_MAX/2, LLONG_MAX/2)));--it;
		vector<pair<int, pii> > vect;
		while (1){
			if (it->se.fi<l)break;
			vect.pb(*it);
			--it;
		}
		for (auto i:vect){
			s.erase(i);
			if (i.fi<l&&i.se.fi>r){
				s.insert(mp(i.fi, mp(l-1, i.se.se)));
				s.insert(mp(r+1, mp(i.se.fi, i.se.se+r+1-i.fi)));
				temp[t-i.se.se+i.fi-l]+=r-l+1;
			}
			else if (i.fi<l){
				s.insert(mp(i.fi, mp(l-1, i.se.se)));
				temp[t-i.se.se+i.fi-l]+=i.se.fi-l+1;
			}
			else if (i.se.fi>r){
				s.insert(mp(r+1, mp(i.se.fi, i.se.se+r+1-i.fi)));
				temp[t-i.se.se+i.fi-l]+=r-i.fi+1;
			}
			else temp[t-i.se.se+i.fi-l]+=i.se.fi-i.fi+1;
		}
		s.insert(mp(l, mp(r, t)));
		t+=r-l+1;
	}
	for (auto [i, j]:temp)ans.pb(mp(i, j));
	ans.pb(mp(LLONG_MAX/2, 0));
	sort(ans.begin(), ans.end());
	for (int i=ans.size()-2; i>=0; --i)ans[i].se+=ans[i+1].se;
	while (q--){
		cin>>l;
		auto it = upper_bound(ans.begin(), ans.end(), mp(l, LLONG_MAX/2));
		cout<<it->se<<" ";
	}
}
