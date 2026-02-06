#include <cstdio>
#include <stdio.h>
#include <stdbool.h>
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
#include <cassert>
using namespace std;

#define int long long
#define pii pair<int, int>
#define mp make_pair
#define pb push_back
#define fi first
#define se second

const int MOD=998244353;
const int PRIM=3;
const int INVPRIM=332748118;

int expo(int a, int b){
	int res=1;
	while (b){
		if (b%2)res=(res*a)%MOD;
		a=(a*a)%MOD;
		b/=2;
	}
	return res;
}

vector<int> ntt(vector<int> a, int n){
	for (int i=1, j=0; i<n; ++i){
		int c=n/2;
		for (;j&c;c/=2)j^=c;
		j^=c;
		if (i<j)swap(a[i], a[j]);
	}
	for (int len=2; len<=n; len*=2){
		int wlen=expo(PRIM, MOD/len);
		for (int i=0; i<n; i+=len){
			int w=1;
			for (int j=0; j<len/2; ++j){
				int temp=a[i+j], temp2=a[i+j+len/2];
				a[i+j]=(temp+w*temp2)%MOD;
				a[i+j+len/2]=((temp-w*temp2)%MOD+MOD)%MOD;
				w=(w*wlen)%MOD;
			}
		}
	}
	return a;
}

vector<int> intt(vector<int> a, int n){
	for (int i=1, j=0; i<n; ++i){
		int c=n/2;
		for (;j&c;c/=2)j^=c;
		j^=c;
		if (i<j)swap(a[i], a[j]);
	}
	for (int len=2; len<=n; len*=2){
		int wlen=expo(INVPRIM, MOD/len);
		for (int i=0; i<n; i+=len){
			int w=1;
			for (int j=0; j<len/2; ++j){
				int temp=a[i+j], temp2=a[i+j+len/2];
				a[i+j]=(temp+w*temp2)%MOD;
				a[i+j+len/2]=((temp-w*temp2)%MOD+MOD)%MOD;
				w=(w*wlen)%MOD;
			}
		}
	}
	for (int i=0; i<n; ++i)a[i]=(a[i]*expo(n, MOD-2))%MOD;
	return a;
}

vector<int> fft(vector<int> a, vector<int> b){
	int n=1;
	while (n<a.size()+b.size())n*=2;
	a.resize(n, 0);
	b.resize(n, 0);
	a=ntt(a, n);
	b=ntt(b, n);
	for (int i=0; i<n; ++i)a[i]=(a[i]*b[i])%MOD;
	return intt(a, n);
}

int32_t main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n;
	cin>>n;
	vector<int> a(n), b(n);
	for (int i=0; i<n; ++i)cin>>a[i];
	for (int i=0; i<n; ++i)cin>>b[i];
	vector<int> c=fft(a, b);
	for (int i=0; i<2*n-1; ++i)cout<<c[i]<<" ";
}
