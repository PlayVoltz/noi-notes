#include <bits/stdc++.h>
using namespace std;

#define int long long
#define pii pair<int, int>
#define mp make_pair
#define pb push_back
#define fi first
#define se second

int n;
vector<vector<pii> > graph;

int dijk(int start, int end){
	vector<bool> visited(n+1, 0);
	vector<int> dj(n+1, LLONG_MAX/2);
	priority_queue<pii, vector<pii>, greater<pii> > pq;
	dj[start]=0;
	pq.push(mp(0, start));
	while (!pq.empty()){
		int cnode=pq.top().se;
		pq.pop();
		if (visited[cnode])continue;
		visited[cnode]=1;
		for (auto num:graph[cnode]){
			if (!visited[num.fi]&&dj[cnode]+num.se<dj[num.fi]){
				dj[num.fi]=dj[cnode]+num.se;
				pq.push(mp(dj[num.fi], num.fi));
			}
		}
	}
	return dj[end];
}

int32_t main(){
	int e, a, b, c;
	cin>>n>>e;
	graph.resize(n+1);
	while (e--){
		cin>>a>>b>>c;
		graph[a].pb(mp(b, c));
		graph[b].pb(mp(a, c));
	}
	cout<<dijk(1, n);
}
