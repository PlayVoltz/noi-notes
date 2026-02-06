#include <bits/stdc++.h>
using namespace std;

#define pii pair<int, bool>
#define mp make_pair

vector <pii> dsu;

pii fp(int node){
	if (dsu[node].first<0)return mp(node, 0);
	pii par=fp(dsu[node].first);
	return dsu[node]=mp(par.first, par.second^dsu[node].second);
}

void merge(int a, int b, bool c){
	pii pa=fp(a), pb=fp(b);
	if (pa.first==pb.first)return;
	dsu[pb.first]=mp(pa.first, (c^pa.second)^pb.second);
}

int main(){
	int n, q, a, b;
	char c;
	cin>>n>>q;
	dsu.resize(n, mp(-1, 0));
	while (q--){
		cin>>c>>a>>b;--a;--b;
		if (c=='Q'){
			pii pa=fp(a), pb=fp(b);
			if (pa.first!=pb.first)cout<<"?\n";
			else if (pa.second!=pb.second)cout<<"A\n";
			else cout<<"R\n";
		}
		else merge(a, b, c=='A');
	}
}
