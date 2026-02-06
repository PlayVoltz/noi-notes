#include <bits/stdc++.h>
using namespace std;

vector<int> dsu;

int fp(int node){
	if (dsu[node]==-1)return node;
	return dsu[node]=fp(dsu[node]);
}

void merge(int a, int b){
	if (fp(a)!=fp(b))dsu[fp(a)]=fp(b);
}

int main(){
	int n, e, a, b, c=0;
	cin>>n>>e;
	dsu.resize(n, -1);
	while (e--){
		cin>>a>>b;
		merge(a, b);
	}
	for (int i=0; i<n; ++i)if (dsu[i]==-1)++c;
	cout<<c;
}
