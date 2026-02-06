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

#define int long long
#define pii pair<int, int>
#define mp make_pair
#define pb push_back

deque <pii> cht;

int eval(pii line, int x){
	return line.first*x+line.second;
}

int query(int x){
	while (cht.size()>1){
		if (eval(cht[0], x)<eval(cht[1], x))cht.pop_front();//for min change the less than to more than
		else break;
	}
	return eval(cht[0], x);
}

long double intersect(pii a, pii b){
	return (long double)(b.second-a.second)/(a.first-b.first);
}

void insert(int m, int c){
	pii line = mp(m, c);
	while (!cht.empty()&&cht.back().first==m){
		if (cht.back().second<c)cht.pop_back();//for min change the less than to more than
		else return;
	}
	while (cht.size()>1){
		int s = cht.size();
		if (intersect(cht[s-1], line)<=intersect(cht[s-2], line))cht.pop_back();
		else break;
	}
	cht.push_back(line);
}

int32_t main(){
	int n, m;
	cin>>n>>m;
	vector <string> vect(m);
	vector <vector<int> > dp(n, vector<int>(m, LLONG_MAX/2));
	for (int i=0; i<m; ++i)cin>>vect[i];
	for (int i=0; i<m; ++i){
		if (vect[i][0]=='1')insert(2*i, -i*i);
	}
	for (int i=1; i<n; ++i){
		vector <pii> next;
		for (int j=0; j<m; ++j){
			if (vect[j][i]!='1')continue;
			dp[i][j] = j*j-query(j);
			next.pb(mp(2*j, -j*j-dp[i][j]));
		}
		while (!convexhull.empty()){
			convexhull.pop_back();
		}
		for (auto num:next){
			insert(num.first, num.second);
		}
	}
	int minnum = LLONG_MAX;
	for (int i=0; i<m; ++i){
		minnum = min(minnum, dp[n-1][i]);
	}
	cout<<minnum;
}
