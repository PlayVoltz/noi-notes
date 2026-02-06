#include <bits/stdc++.h>
using namespace std;

int n, counts;
vector <int> vect;

void merge(int left, int mid, int right){
	int n1 = mid-left+1, n2 = right-mid;
	vector <int> l(n1);
	vector <int> r(n2);
	for (int i=0; i<n1; ++i){
		l[i] = vect[i+left];
	}
	for (int i=0; i<n2; ++i){
		r[i] = vect[i+mid+1];
	}
	int p1 = 0, p2 = 0, k = left;
	while (p1<n1 && p2<n2){
		if (l[p1]>r[p2]){
			counts+=n1-p1;
			vect[k] = r[p2];
			++p2;
		}
		else{
			vect[k] = l[p1];
			++p1;
		}
		++k;
	}
	while (p1<n1){
		vect[k] = l[p1];
		++p1;
		++k;
	}
	while (p2<n2){
		vect[k] = r[p2];
		++p2;
		++k;
	}
}

void mergesort(int left, int right){
	if (left>=right){
		return;
	}
	int mid = (left+right)/2;
	mergesort(left, mid);
	mergesort(mid+1, right);
	merge(left, mid, right);
}

int main(){
	int t;
	cin>>t;
	while (t--){
		cin>>n;
		vect.resize(n);
		for (int i=0; i<n; ++i){
			cin>>vect[i];
		}
		counts = 0;
		mergesort(0, n-1);
		cout<<counts<<"\n";
	}
}
