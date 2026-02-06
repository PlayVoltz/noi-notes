#include <bits/stdc++.h>
using namespace std;

struct trio{
	int l, r, id;
};

int BLK;

bool customsort(trio a, trio b){
	if (a.l/BLK==b.l/BLK)return a.r<b.r;
	return a.l/BLK<b.l/BLK;
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n, q;
	cin>>n;
	BLK=sqrt(n);
	vector<int> vect(n);
	for (int i=0; i<n; ++i)cin>>vect[i];
	cin>>q;
	vector<trio> query(q);
	for (int i=0; i<q; ++i)cin>>query[i].l>>query[i].r, query[i].id=i, --query[i].r, --query[i].l;
	sort(query.begin(), query.end(), customsort);
	int count=1, l=0, r=0;
	vector<int> freq(1000005, 0);
	vector<int> ans(q);
	freq[vect[0]]=1;
	for (auto c:query){
		while (r<c.r){
			++r;
			++freq[vect[r]];
			if (freq[vect[r]]==1)++count;
		}
		while (l<c.l){
			--freq[vect[l]];
			if (freq[vect[l]]==0)--count;
			++l;
		}
		while (r>c.r){
			--freq[vect[r]];
			if (freq[vect[r]]==0)--count;
			--r;
		}
		while (l>c.l){
			--l;
			++freq[vect[l]];
			if (freq[vect[l]]==1)++count;
		}
		ans[c.id]=count;
	}
	for (auto num:ans)cout<<num<<"\n";
}
