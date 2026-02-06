#include <iostream>
#include <vector>
using namespace std;

int n, arr[100001], m, a, b, c, q;
vector <int> ft;

int ftsum(int index){
	int sum = 0;
	while (index>0){
		sum+=ft[index];
		index-= index & (-index);
	}
	return sum;
}

void change(int index, int val){
	while (index<=n){
		ft[index]+=val;
		index+=index&(-index);
	}
}

void update(int l, int r, int val){
	change(l, val);
	change(r+1, -val);
}

void build(){
	for (int i=1; i<=n; ++i){
		update(i, arr[i]);
	}
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>n;
	ft.resize(n+1, 0);
	for (int i=1; i<=n; ++i){
		cin>>arr[i];
	}
	cin>>m;
	build();
	while (m--){
		cin>>q;
		if (q){
			cin>>a>>b>>c;
			for (int i=a; i<=b; ++i){
				update(i, c);
			}
		}
		else{
			cin>>a>>b;
			cout<<ftsum(b+1)-ftsum(a)<<"\n";
		}
	}
}
