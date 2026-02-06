#include <bits/stdc++.h>
using namespace std;

#define ll long

ll n;
vector<ll> dsu;
vector <vector<pair<ll, ll> > > graph;
vector <ll> sightseeing;

struct trio{
	ll first;
	ll second;
	ll third;
};

bool customsort(trio a, trio b){
	return a.third>b.third;
}

ll findRoot(ll node) {
    if (dsu[node] < 0) {
        return node;
    }
    return dsu[node] = findRoot(dsu[node]);
}

bool gconnect(ll a, ll b) {
    ll parenta = findRoot(a);
    ll parentb = findRoot(b);
	if (parenta==parentb){
		return false;
	}
	if (dsu[parenta]>dsu[parentb]){
		dsu[parentb]+=dsu[parenta];
		dsu[parenta] = parentb;
		return true;
	}
	dsu[parenta]+=dsu[parentb];
	dsu[parentb] = parenta;
	return true;
}

void precalc(){
	queue<ll> q;
	sightseeing[1] = INT_MAX;
	q.push(1);
	while (!q.empty()){
		for (auto num:graph[q.front()]){
			if (sightseeing[num.first]==-1){
				sightseeing[num.first] = min(num.second, sightseeing[q.front()]);
				q.push(num.first);
			}
		}
		q.pop();
	}
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	ll e, q, a;
	cin>>n>>e>>q;
	vector<trio> vect(e);
	dsu.resize(n+1, -1);
	graph.resize(n+1);
	sightseeing.resize(n+1, -1);
	for (int i=0; i<e; ++i){
		cin>>vect[i].first>>vect[i].second>>vect[i].third;
	}
	sort(vect.begin(), vect.end(), customsort);
	for (auto num:vect){
		if (gconnect(num.first, num.second)){
			graph[num.first].push_back(make_pair(num.second, num.third));
			graph[num.second].push_back(make_pair(num.first, num.third));
		}
	}
	precalc();
	while (q--){
		cin>>a;
		cout<<sightseeing[a]<<"\n";
	}
}

