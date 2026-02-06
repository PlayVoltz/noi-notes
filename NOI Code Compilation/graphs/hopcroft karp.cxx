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
using namespace std;
 
#define int long long
#define pb push_back
#define mp make_pair
#define pii pair<int, int>
#define fi first
#define se second

struct trio{
	int x, y, s;
};

int n;
vector<bool> visited;
vector<int> ml, mr, layer;
vector<vector<int> > graph;

void bfs(){
	queue<int> q;
	for (int i=0; i<n; ++i)if (ml[i]==-1)q.push(i), layer[i]=0;
	while (!q.empty()){
		int cnode=q.front();
		q.pop();
		for (auto num:graph[cnode])if (mr[num]!=-1&&layer[mr[num]]==-1)layer[mr[num]]=layer[cnode]+1, q.push(mr[num]);
	}
}

bool dfs(int node){
	if (visited[node])return 0;
	visited[node]=1;
	for (auto num:graph[node])if (mr[num]==-1||(layer[mr[num]]>layer[node]&&dfs(mr[num]))){ml[node]=num, mr[num]=node;return 1;}
	return 0;
}

int32_t main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int res=0;
	cin>>n;
	vector<trio> vect(n);
	vector<vector<bool> > can(n, vector<bool>(n, 0));
	graph.resize(n);
	ml.resize(n, -1);
	mr.resize(n, -1);
	for (int i=0; i<n; ++i)cin>>vect[i].x>>vect[i].y>>vect[i].s;
	for (int i=0; i<n; ++i)for (int j=0; j<n; ++j)if (i!=j&&vect[i].y<vect[j].y&&max(abs(vect[i].x-vect[j].x), abs(vect[i].y-vect[j].y))<=max(vect[i].s, vect[j].s))can[i][j]=1;
	for (int i=0; i<n; ++i)for (int j=0; j<n; ++j)for (int k=0; k<n; ++k)if (can[i][k]&&can[k][j])can[i][j]=1;
	for (int i=0; i<n; ++i)for (int j=0; j<n; ++j)if (can[i][j])graph[i].pb(j);
	bool loop=1;
	while (loop){
		layer.assign(n, -1), bfs(), loop=0;
		visited.assign(n, 0);
		for (int i=0; i<n; ++i)if (ml[i]==-1&&dfs(i))++res, loop=1, visited.assign(n, 0);
	}
	cout<<(res?n-res+1:-1);
}
