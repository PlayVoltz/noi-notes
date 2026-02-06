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
#include <bitset>
#include <iomanip>
using namespace std;

#define pii pair<int, int>
#define pb push_back

int main(){
	int n, t;
	cin>>n>>t;
	vector<pii> graph(n);
	for (int i=0; i<n; ++i)cin>>graph[i].first>>graph[i].second;
	vector<deque<int> > dial(t+1);
	vector<bool> visited(2*t+1, 0);
	vector<int> cost(2*t+1, t+1), par(2*t+1, -1);
	int id = 0;
	dial[0].pb(0);
	cost[0]=0;
	while (true){
		while (dial[id].empty() && id<t)++id;
		if (dial[id].empty())break;
		int cnode = dial[id][0];
		dial[id].pop_front();
		if (visited[cnode])continue;
		visited[cnode]=1;
		for (int i=0; i<n; ++i){
			int nc=cost[cnode]+graph[i].second, nn=cnode+graph[i].first;
			if (nn<=2*t && nn>=0 && nc<cost[nn]){
				cost[nn]=nc;
				dial[nc].pb(nn);
				par[nn]=i;
			}
		}
	}
	vector<int> ans;
	int c=t;
	while (par[c]!=-1){
		ans.pb(par[c]);
		c-=graph[par[c]].first;
	}
	cout<<ans.size()<<"\n";
	for (auto num:ans)cout<<num+1<<" ";
}
