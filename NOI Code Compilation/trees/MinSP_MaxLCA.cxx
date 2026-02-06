#include <bits/stdc++.h>
using namespace std;

#define int long long

int n;
vector<int> dsu;
vector<vector<pair<int, int> > > graph;
vector<vector<int> > twok;
vector<int> depth;
vector <vector<int> > dist;

struct trio{
	int first;
	int second;
	int third;
};

bool customsort(trio a, trio b){
	return a.third<b.third;
}

int findRoot(int node) {
    if (dsu[node] < 0) {
        return node;
    }
    return dsu[node] = findRoot(dsu[node]);
}

bool gconnect(int a, int b) {
    int parenta = findRoot(a);
    int parentb = findRoot(b);
	if (parenta==parentb){
		return false;
	}
	if (dsu[parenta]>dsu[parentb]){
		dsu[parenta] = parentb;
		return true;
	}
	dsu[parentb] = parenta;
	return true;
}

int lca(int a, int b){
	int ans = 0;
	if (depth[a]<depth[b]){
		swap(a, b);
	}
	int diff = depth[a]-depth[b];
	while (diff){
		int lg = log2(diff);
		ans = max(ans, dist[a][lg]);
		a = twok[a][lg];
		diff-=(1<<lg);
	}
	if (a==b){
		return ans;
	}
	for (int i=19; i>=0; --i){
		if (twok[a][i]!=twok[b][i]){
			ans = max(ans, max(dist[a][i], dist[b][i]));
			a = twok[a][i];
			b = twok[b][i];
		}
	}
	ans = max(ans, max(dist[a][0], dist[b][0]));
	return ans;
}

void twokdecomp(int node, int par, int dep, int m){
	twok[node][0] = par;
	depth[node] = dep;
	dist[node][0] = m;
	for (int i=1; i<20; ++i){
		twok[node][i] = twok[twok[node][i-1]][i-1];
		dist[node][i] = max(dist[node][i-1], dist[twok[node][i-1]][i-1]);
	}
	for (auto num:graph[node]){
		if (num.first!=par){
			twokdecomp(num.first, node, dep+1, num.second);
		}
	}
}

int32_t main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int e, q, a, b;
	cin>>n>>e>>q;
	trio vect[e];
	dsu.resize(n, -1);
	graph.resize(n);
	depth.resize(n);
	dist.resize(n, vector<int>(20));
	twok.resize(n, vector<int>(20));
	for (int i=0; i<e; ++i){
		cin>>vect[i].first>>vect[i].second>>vect[i].third;
	}
	sort(vect, vect+e, customsort);
	for (auto num:vect){
		if (gconnect(num.first, num.second)){
			graph[num.first].push_back(make_pair(num.second, num.third));
			graph[num.second].push_back(make_pair(num.first, num.third));
		}
	}
	twokdecomp(0, 0, 0, 0);
	while (q--){
		cin>>a>>b;
		cout<<lca(a, b)<<"\n";
	}
}
