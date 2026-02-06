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

#define pb push_back
#define mp make_pair
#define pii pair<int, int>
#define fi first
#define se second

inline void read(long long& x) {
    x = 0;
    char ch = getchar_unlocked();
    while (ch < '0' || ch > '9') ch = getchar_unlocked();
    while (ch >= '0' && ch <= '9' ) {
        x = (x << 3) + (x << 1) + (ch & 15);
        ch = getchar_unlocked();
    }
}

long long n, h, lazy[1048576+5];//set lazy as -1 for set
long long st[2097152+5];

void apply(long long i, long long val){
	st[i]+=val*(1ll<<(h+__builtin_clzll(i)-63));//change to just equal for set
	if (i<n)lazy[i]+=val;//change to just equal for set
}

void build(long long i, long long k){
	for (i=(((i+n)^k)>>1); i>0; i>>=1)if (!lazy[i])st[i]=st[i<<1]+st[i<<1|1];
}

void push(long long i, long long k){
	i=(i+n)^k;
	for (long long b=h; b>0; --b){
		long long j=(i>>b);
		if (lazy[j]){
			apply(j<<1, lazy[j]);
			apply(j<<1|1, lazy[j]);
			lazy[j]=0;
		}
	}
}

void up(long long l0, long long r0, long long k, long long val){
	push(l0, k);
	push(r0, k);
	for (long long l=l0+n, r=r0+n+1, layer=0; l<r; l>>=1, r>>=1, ++layer){
		if (l&1)apply(l^(k>>layer), val), ++l;
		if (r&1)--r, apply(r^(k>>layer), val);
	}
	build(l0, k);
	build(r0, k);
}

long long query(long long l, long long r, long long k){
	push(l, k);
	push(r, k);
	long long res=0;
	long long layer=0;
	for (l+=n, r+=n+1; l<r; l>>=1, r>>=1, ++layer){
		if (l&1)res+=st[l^(k>>layer)], ++l;
		if (r&1)--r, res+=st[r^(k>>layer)];
	}
	return res;
}

int32_t main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	long long q, t, l, r, k, v;
	read(h), read(q);
	n=(1<<h);
	//for (int i=n; i<2*n; ++i)cin>>st[i];
	//for (int i=n-1; i>0; --i)st[i]=st[i<<1]+st[i<<1|1];//, lazy[i]=-1;
	while (q--){
		read(t);
		if (t==1)read(l), read(r), read(v), read(k), up(l, r, k, v);
		else read(l), read(r), read(k), cout<<query(l, r, k)<<"\n";
	}
}
