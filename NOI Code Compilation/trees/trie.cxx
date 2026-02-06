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

const int MOD = 1e9+7;

int counter=0, trie[1000005][26];
bool eend[1000005];

void insert(string s){
	int node=0;
	for (auto c:s){
		if (!trie[node][c-'a'])trie[node][c-'a']=++counter;
		node=trie[node][c-'a'];
	}
	eend[node]=1;
}

int32_t main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	string s, a;
	int n;
	cin>>s>>n;
	while (n--){
		cin>>a;
		insert(a);
	}
	vector<int> dp(s.size()+1, 0);
	dp[s.size()]=1;
	for (int i=s.size()-1; i>=0; --i){
		int node=0;
		for (int j=i; j<s.size(); ++j){
			if (!trie[node][s[j]-'a'])break;
			node=trie[node][s[j]-'a'];
			if (eend[node])dp[i]=(dp[i]+dp[j+1])%MOD;
		}
	}
	cout<<dp[0];
}
