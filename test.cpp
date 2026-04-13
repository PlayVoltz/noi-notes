#include <cstdio>
#include <stdio.h>
#include <stdbool.h>
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
#include <cassert>
#include <random>
#include <chrono>
#include <fstream> 
using namespace std;

#define int long long
#define mp make_pair
#define pii pair<int, int>
#define fi first
#define se second
#define pb push_back

int32_t main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n, p=0;
	cin>>n;
	int ans=n;
	vector<int> a(n), b(n);
	vector<pii> ord;
	for (int i=0; i<n; ++i)cin>>a[i];
	for (int i=0; i<n; ++i)cin>>b[i];
	priority_queue<int> got, vect;
	priority_queue<int, vector<int>, greater<int> > pq;
	for (int i=0; i<n; ++i){
		if (a[i]>b[i])ord.pb(mp(a[i], b[i]));
		else if (a[i]<b[i])--ans, vect.push(b[i]), got.push(a[i]);
	}
	sort(ord.begin(), ord.end(), greater<pii>());
	while (vect.size()){
		int c=vect.top();
		vect.pop();
		while (p<ord.size()&&ord[p].fi>=c)pq.push(ord[p].se), ++p;
		if (got.top()>=c)got.pop();
		else{
			--ans;
			if (pq.size()){
				vect.push(pq.top());
				pq.pop();
			}
			else{
				cout<<-1;
				return 0;
			}
		}
	}
	cout<<ans;
}
