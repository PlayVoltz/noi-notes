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
#include <iostream>
#include <unordered_map>
#include <cmath>
#include <cctype>
#include <bitset>
#include <iomanip>
#include <cstring>
#include <bits/stdc++.h>
using namespace std;
 
#define int long long
#define pii pair<int, int>
#define mp make_pair
#define pb push_back
#define fi first
#define se second

#ifdef _WIN32
#define getchar_unlocked _getchar_nolock
#define putchar_unlocked _putchar_nolock
#endif
 
using ll = long long;
 
void read(int &v) {
    v = 0;
    char ch = getchar_unlocked();
    for (; (ch < '0' || ch > '9') && ch != '-'; ch = getchar_unlocked());
    for (; '0' <= ch && ch <= '9'; ch = getchar_unlocked()) {
        v = (v << 3) + (v << 1) + (ch & 15);
    }
}
 
char os[65];
void write(ll n) {
    int i = 0;
    do os[i++] = n % 10;
    while (n /= 10);
    while (i--) {
        putchar_unlocked(os[i] + 48);
    }
}
#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
 
int32_t main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n, ans=0;
	cin>>n;
	vector<int> pre(n+2, 0);
	vector<bitset<3005> > vect(n);
	for (int i=0; i<n; ++i)cin>>vect[i], pre[i+2]=pre[i+1]+i+1;
	for (int i=0; i<n; ++i)for (int j=i+1; j<n; ++j){
		bitset<3005> temp = vect[i]&vect[j];
		ans+=pre[temp.count()];
	}
	cout<<ans;
}
