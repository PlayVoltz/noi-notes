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

int n;
int dy[4]={1, -1, 0, 0};
int dx[4]={0, 0, -1, 1};
vector<string> graph;

vector<vector<int> > bfs(int sy, int sx){
	vector<vector<int> > dj(n, vector<int>(n, LLONG_MAX/2));
	queue<pii> q;
	dj[sy][sx]=0;
	q.push(mp(sy, sx));
	while (!q.empty()){
		pii c=q.front();
		q.pop();
		for (int i=0; i<4; ++i){
			int y=c.fi+dy[i], x=c.se+dx[i];
			if (y<0||x<0||x>=n||y>=n||graph[y][x]=='X'||dj[y][x]!=LLONG_MAX/2)continue;
			dj[y][x]=dj[c.fi][c.se]+1;
			q.push(mp(y, x));
		}
	}
	return dj;
}

int32_t main(){
	int s, e;
	cin>>n;
	graph.resize(n);
	vector<pii> vect;
	for (int i=0; i<n; ++i){
		cin>>graph[i];
		for (int j=0; j<n; ++j){
			if (graph[i][j]=='S')s=vect.size(), vect.pb(mp(i, j));
			else if (graph[i][j]=='B')e=vect.size(), vect.pb(mp(i, j));
			else if (graph[i][j]=='F')vect.pb(mp(i, j));
		}
	}
	vector<vector<vector<int> > > dist(vect.size(), vector<vector<int> >(n, vector<int>(n)));
	for (int i=0; i<vect.size(); ++i)dist[i]=bfs(vect[i].fi, vect[i].se);
	vector<vector<int> > dj(vect.size(), vector<int>((1<<vect.size()), LLONG_MAX/2));
	priority_queue<pair<int, pii>, vector<pair<int, pii> >, greater<pair<int, pii> > > pq;
	vector<vector<bool> > visited(vect.size(), vector<bool>((1<<vect.size()), 0));
	dj[s][1<<s]=0;
	pq.push(mp(0, mp(s, (1<<s))));
	while (!pq.empty()){
		int cnode=pq.top().se.fi, mask=pq.top().se.se;
		pq.pop();
		if (visited[cnode][mask])continue;
		visited[cnode][mask]=1;
		for (int i=0; i<vect.size(); ++i){
			if (!visited[i][mask|(1<<i)]&&dj[cnode][mask]+dist[cnode][vect[i].fi][vect[i].se]<dj[i][mask|(1<<i)]){
				dj[i][mask|(1<<i)]=dj[cnode][mask]+dist[cnode][vect[i].fi][vect[i].se];
				pq.push(mp(dj[i][mask|(1<<i)], mp(i, mask|(1<<i))));
			}
		}
	}
	cout<<(dj[e][(1<<vect.size())-1]==LLONG_MAX/2?-1:dj[e][(1<<vect.size())-1]);
}
