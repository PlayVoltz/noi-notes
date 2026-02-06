#include <bits/stdc++.h>
using namespace std;

#define int long long
#define mp make_pair
#define pb push_back
#define pii pair<int, int>

vector<vector<int> > graph;

int32_t main(){
	int n, e, a, b, c, ans=LLONG_MAX;
	cin>>n>>e;
	graph.resize(n+1, vector<int>(n+1, LLONG_MAX/1000));
	while (e--){
		cin>>a>>b>>c;
		graph[a][b]=graph[b][a]=c;
	}
	for (int k=1; k<=n; ++k)
		for (int i=1; i<=n; ++i)
			for (int j=1; j<=n; ++j)
				if (graph[i][k]+graph[k][j]<graph[i][j])
					graph[i][j]=graph[i][k]+graph[k][j];
	for (int i=1; i<=n; ++i)graph[i][i]=0;
	for (int i=1; i<=n; ++i)
		for (int j=1; j<=n; ++j){
			ans=min(ans, graph[i][j]+graph[1][i]+graph[2][i]+graph[3][j]+graph[4][j]);
			ans=min(ans, graph[i][j]+graph[1][i]+graph[2][j]+graph[3][i]+graph[4][j]);
			ans=min(ans, graph[i][j]+graph[1][i]+graph[2][j]+graph[3][j]+graph[4][i]);
		}
	cout<<ans;
}
