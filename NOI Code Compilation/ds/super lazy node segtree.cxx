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
using namespace std;

#define int long long
#define pb push_back

struct trio{
	int x, y, z, id;
	trio(){}
	trio(int x, int y, int z, int id):x(x), y(y), z(z), id(id){}
};

struct node{
	int s, e, m, val;
	node *l, *r;
	void createl(){
		if (l==nullptr){
			l = new node(s, m);
		}
	}
	void creater(){
		if (r==nullptr){
			r = new node(m+1, e);
		}
	}
	node(int S, int E){
		s = S, e = E, m = (s+e)/2;
		val=0;
		l=r=nullptr;
	}
	void up(int id, int v){
		if (s==e)val+=v;
		else{
			if (id<=m)createl(), l->up(id, v);
			else if (id>m)creater(), r->up(id, v);
			if (r==nullptr)val=l->val;
			else if (l==nullptr)val=r->val;
			else val=l->val+r->val;
		}
		
	}
	int query(int left, int right){
		if (s==left && e==right)return val;
		if (right<=m){
			if (l==nullptr)return 0;
            return l->query(left, right);
		}
		else if (left>m){
			if (r==nullptr)return 0;
            return r->query(left, right);
		}
		else if (l!=nullptr&&r!=nullptr)return l->query(left, m)+r->query(m+1, right);
		else if (r!=nullptr)return r->query(m+1, right);
		else if (l!=nullptr)return l->query(left, m);
		return 0;
	}
}*sta, *stb;

bool custom (trio a, trio b){
	return a.z>b.z;
}

int32_t main(){
	int n, q;
	cin>>n>>q;
	sta = new node(0, 1000000000);
	stb = new node(0, 1000000000);
	vector<trio> st(n), query(q);
	vector<int> ans(q);
	for (int i=0; i<n; ++i)cin>>st[i].x>>st[i].y, st[i].z=st[i].x+st[i].y, st[i].id=i;
	for (int i=0; i<q; ++i)cin>>query[i].x>>query[i].y>>query[i].z, query[i].z=max(query[i].z, query[i].x+query[i].y), query[i].id=i;
	sort(st.begin(), st.end(), custom);
	sort(query.begin(), query.end(), custom);
	int p=0, c=0;
	for (int i=0; i<q; ++i){
		while (p!=n && st[p].z>=query[i].z){
			sta->up(st[p].x, 1);
			stb->up(st[p].y, 1);
			++c, ++p;
		}
		ans[query[i].id]=c-sta->query(0, query[i].x-1)-stb->query(0, query[i].y-1);
	}
	for (auto a:ans)cout<<a<<"\n";
}
