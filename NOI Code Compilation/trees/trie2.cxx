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

int counter=0, trie[1000005][26];
bool got[1000005], mx[1000005];
vector<char> ans;

void insert(string s){
	int node=0;
	for (auto c:s){
		if (!trie[node][c-'a'])trie[node][c-'a']=++counter;
		node=trie[node][c-'a'];
	}
	got[node]=1;
}

void insertmx(string s){
	int node=0;
	for (auto c:s){
		if (!trie[node][c-'a'])trie[node][c-'a']=++counter;
		node=trie[node][c-'a'];
		mx[node]=1;
	}
	got[node]=1;
}

void dfs(int node){
	if (got[node])ans.pb('P');
	int last=-1;
	for (int i=0; i<26; ++i)if (trie[node][i]){
		if (mx[trie[node][i]]){
			last=i;
			continue;
		}
		ans.pb('a'+i);
		dfs(trie[node][i]);
		ans.pb('-');
	}
	if (last!=-1){
		ans.pb('a'+last);
		dfs(trie[node][last]);
		ans.pb('-');
	}
}

bool custom(string a, string b){
	return a.size()>b.size();
}

int32_t main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n;
	cin>>n;
	vector<string> vect(n);
	for (int i=0; i<n; ++i)cin>>vect[i];
	sort(vect.begin(), vect.end(), custom);
	insertmx(vect[0]);
	for (int i=1; i<n; ++i)insert(vect[i]);
	dfs(0);
	while (ans.back()=='-')ans.pop_back();
	cout<<ans.size()<<"\n";
	for (auto a:ans)cout<<a<<"\n";
}
