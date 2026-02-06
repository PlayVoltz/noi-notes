#include <bits/stdc++.h>
using namespace std;

#define int long long
#define pb push_back

struct node{
	int s, e, m, val, lazyset, lazyadd;
	node *l, *r;
	void create(){
		if (l==nullptr){
			l = new node(s, m);
			r = new node(m+1, e);
		}
	}
	void propagate(){
		if (lazyset!=-1)val=lazyset*(e-s+1);
		val+=lazyadd*(e-s+1);
		if (s!=e){
			create();
			if (lazyset!=-1){
				l->lazyset=lazyset;
				r->lazyset=lazyset;
				l->lazyadd=r->lazyadd=0;
			}
			if (lazyadd){
				l->lazyadd+=lazyadd;
				r->lazyadd+=lazyadd;
			}
		}
		lazyset=-1;
		lazyadd=0;
	}
	node(int S, int E){
		s = S, e = E, m = (s+e)/2;
		val=lazyadd=0;
		lazyset=-1;
		l=r=nullptr;
	}
	void upset(int left, int right, int v){
		propagate();
		if (s==left && e==right)lazyadd=0, lazyset=v;
		else{
			create();
			if (right<=m)l->upset(left, right, v);
			else if (left>m)r->upset(left, right, v);
			else l->upset(left, m, v), r->upset(m+1, right, v);
			r->propagate(), l->propagate();
			val=l->val+r->val;
		}
	}
	void upadd(int left, int right, int v){
		propagate();
		if (s==left && e==right)lazyadd+=v;
		else{
			create();
			if (right<=m)l->upadd(left, right, v);
			else if (left>m)r->upadd(left, right, v);
			else l->upadd(left, m, v), r->upadd(m+1, right, v);
			r->propagate(), l->propagate();
			val=l->val+r->val;
		}
	}
	int query(int left, int right){
		propagate();
		if (s==left && e==right)return val;
		create();
		if (right<=m)return l->query(left, right);
		else if (left>m)return r->query(left, right);
		else return l->query(left, m)+r->query(m+1, right);
	}
}*st;

int counter=0;
vector<vector<int> > graph, twok;
vector<int> subtree, par, depth, in, out, head;

int dfs(int node, int p, int d){
	depth[node]=d;
	par[node]=p;
	if (graph[node].size()>1&&graph[node][0]==p)swap(graph[node][0], graph[node][1]);
	for (auto &num:graph[node]){
		if (num==p)continue;
		subtree[node]+=dfs(num, node, d+1);
		if (subtree[num]>subtree[graph[node][0]])swap(num, graph[node][0]);
	}
	return subtree[node];
}

void twokdecomp(int node, int p){
	twok[node][0]=p;
	for (int i=1; i<20; ++i)twok[node][i]=twok[twok[node][i-1]][i-1];
	for (auto num:graph[node])if (num!=p)twokdecomp(num, node);
}

int kthparent(int node, int k){
	for (int i=0; i<20; ++i)if (k&(1<<i))node=twok[node][k];
	return node;
}

int lca(int a, int b){
	if (depth[a]<depth[b])swap(a, b);
	a=kthparent(a, depth[a]-depth[b]);
	if (a==b)return a;
	for (int i=19; i>=0; --i)if (twok[a][i]!=twok[b][i])a=twok[a][i], b=twok[b][i];
	return twok[a][0];
}

void hld(int node, int p){
	in[node]=++counter;
	for (auto num:graph[node]){
		if (num==p)continue;
		if (num==graph[node][0])head[num]=head[node];
		else head[num]=num;
		hld(num, node);
	}
	out[node]=counter;
}

void upaddhld(int a, int b, int val){
	while (head[a]!=head[b]){
		if (depth[head[a]]<depth[head[b]])swap(a, b);
		st->upadd(in[head[a]], in[a], val);
		a=par[head[a]];
	}
	if (in[a]>in[b])swap(a, b);
	st->upadd(in[a], in[b], val);
}

int32_t main(){
	int n, q, a, b, c, d;
	cin>>n>>q;
	graph.resize(n);
	twok.resize(n, vector<int>(20));
	subtree.resize(n, 1);
	depth.resize(n);
	par.resize(n);
	in.resize(n);
	out.resize(n);
	head.resize(n);
	st = new node(1, n);
	for (int i=1; i<n; ++i){
		cin>>a>>b;
		graph[a].pb(b);
		graph[b].pb(a);
	}
	dfs(0, -1, 0);
	twokdecomp(0, 0);
	hld(0, -1);
	while (q--){
		cin>>a>>b;
		if (a==1){
			cin>>c>>d;
			upaddhld(b, c, d);
		}
		else if (a==2){
			cin>>c;
			st->upset(in[b], out[b], c);
		}
		else cout<<st->query(in[b], in[b])<<"\n";
	}
}
