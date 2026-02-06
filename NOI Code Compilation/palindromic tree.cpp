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
#include <random>
using namespace std;
 
#define int long long
#define pii pair<int, int>
#define mp make_pair
#define pb push_back
#define fi first
#define se second

int counter=0, to[300005][26], sufflink[300005], len[300005], cc[300005], node=1;
string s;

void init(){
	for (int i=0; i<300005; ++i)for (int j=0; j<26; ++j)to[i][j]=-1;
	len[0]=-1;
	len[1]=0;
	sufflink[0]=sufflink[1]=0;
	counter=1;
}

void insert(int i){
	while (s[i-len[node]-1]!=s[i])node=sufflink[node];
	int child=sufflink[node];
	while (s[i-len[child]-1]!=s[i])child=sufflink[child];
	if (to[node][s[i]-'a']==-1){
		to[node][s[i]-'a']=++counter;
		len[counter]=len[node]+2;
		if (len[counter]==1)sufflink[counter]=1;
		else sufflink[counter]=to[child][s[i]-'a'];
	}
	++cc[to[node][s[i]-'a']];
	node=to[node][s[i]-'a'];
}

int32_t main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>s;
	init();
	s='#'+s;
	for (int i=1; i<s.size(); ++i)insert(i);
	int ans=0;
	for (int i=counter; i>1; --i)cc[sufflink[i]]+=cc[i], ans=max(ans, cc[i]*len[i]);
	cout<<ans;
}
