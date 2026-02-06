#include <bits/stdc++.h>
using namespace std;

string s;
int dp[305][305][27];

int letterstamper(int start, int end, int top){
	if (start>end)return 0;
	if (dp[start][end][top]!=-1)return dp[start][end][top];
	if (top==s[start]-'A'+1)dp[start][end][top]=letterstamper(start+1, end, top);
	else{
		int minnum=INT_MAX;
		for (int i=start; i<=end; ++i)minnum=min(minnum, letterstamper(start, i, s[start]-'A'+1)+letterstamper(i+1, end, top)+1);
		dp[start][end][top]=minnum;
	}
	return dp[start][end][top];
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>s;
	memset(dp, -1, sizeof(dp));
	cout<<letterstamper(0, s.size()-1, 0)*2+s.size();
}
