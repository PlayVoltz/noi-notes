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


int k1, k2;
vector<int> path, vect, parent;
vector<vector<int> > graph;

int dfs(int node, int par, int skip){
	vector<int> temp;
	for (auto num:graph[node])if (num!=par&&num!=skip)temp.pb(dfs(num, node, skip));
	int res=0;
	sort(temp.begin(), temp.end(), greater<int>());
	for (int i=0; i<temp.size(); ++i)res=max(res, temp[i]+i+1);
	return res;
}

bool findpath(int node, int par, int find){
	parent[node]=par;
	if (node==find){path.pb(node);return 1;}
	for (auto num:graph[node])if (num!=par&&findpath(num, node, find)){path.pb(node);return 1;}
	return 0;
}

int calc(int skip){
	if (vect[skip]!=-1)return vect[skip];
	return vect[skip]=max(dfs(k1, -1, skip), dfs(k2, -1, parent[skip]));
}

int32_t main(){
	int n, k, a, b;
	cin>>n>>k>>k1;
	graph.resize(n+1);
	vect.resize(n+1, -1);
	parent.resize(n+1);
	if (k==2)cin>>k2;
	for (int i=1; i<n; ++i){
		cin>>a>>b;
		graph[a].pb(b);
		graph[b].pb(a);
	}
	if (k==1)cout<<dfs(k1, -1, -1);
	else{
		findpath(k1, -1, k2);
		int low=0, high=path.size()-1;
		while (low+1<high){
			int mid=(low+high)/2, l=calc(path[mid-1]), m=calc(path[mid]), r=calc(path[mid+1]);
			if (m<=l&&m<=r||m==l||m==r){
				cout<<m;
				return 0;
			}
			if (m<l)low=mid;
			else high=mid;
		}
		cout<<calc(low);
	}
}
