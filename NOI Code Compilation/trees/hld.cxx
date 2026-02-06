#include <bits/stdc++.h>
using namespace std;

#define int long long
#define pb push_back

struct node{
	int s, e, m, val, lazy;
	node *l, *r;
	void create(){
		if (l==nullptr){
			l = new node(s, m);
			r = new node(m+1, e);
		}
	}
	void propagate(){
		val+=lazy*(e-s+1);
		if (s!=e){
			create();
			l->lazy+=lazy;
			r->lazy+=lazy;
		}
		lazy=0;
	}
	node(int S, int E){
		s = S, e = E, m = (s+e)/2;
		val=lazy=0;
		l=r=nullptr;
	}
	void up(int left, int right, int v){
		propagate();
		if (s==left && e==right)lazy+=v;
		else{
			create();
			if (right<=m)l->up(left, right, v);
			else if (left>m)r->up(left, right, v);
			else l->up(left, m, v), r->up(m+1, right, v);
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

int counter=0, root=1;
vector<vector<int> > graph, twok;
vector <int> weight, depth, subtree, par, head, in, out;

void dfs(int node, int p){
	if (graph[node].size()>=2 && graph[node][0]==p)swap(graph[node][0], graph[node][1]);
	subtree[node] = 1;
	par[node] = p;
	for (auto &num:graph[node]){
		if (num!=p){
			depth[num] = depth[node]+1;
			dfs(num, node);
			subtree[node]+=subtree[num];
			if (subtree[num]>subtree[graph[node][0]])swap(graph[node][0], num);
		}
	}
}

void hld(int node, int p){
	in[node]=++counter;
	st->up(in[node], in[node], weight[node]);
	for (auto num:graph[node]){
		if (num!=p){
			if (num==graph[node][0])head[num]=head[node];
			else head[num]=num;
			hld(num, node);
		}
	}
	out[node] = counter;
}

void twokdecomp(int node, int par){
	twok[node][0] = par;
	for (int i=1; i<20; ++i){
		if (twok[node][i-1]==-1){
			twok[node][i] = -1;
			continue;
		}
		twok[node][i] = twok[twok[node][i-1]][i-1];
	}
	for (auto num:graph[node]){
		if (num!=par){
			twokdecomp(num, node);
		}
	}
}

int kthparent(int node, int k){
	for (int i=0; i<20; ++i){
		if (k&(1<<i)){
			node = twok[node][i];
		}
	}
	return node;
}

int lca(int a, int b){
	if (depth[a]<depth[b]){
		swap(a, b);
	}
	a = kthparent(a, depth[a]-depth[b]);
	if (a==b){
		return a;
	}
	for (int i=19; i>=0; --i){
		if (twok[a][i]!=twok[b][i]){
			a = twok[a][i];
			b = twok[b][i];
		}
	}
	return twok[a][0];
}

int hldquerypath(int a, int b){
	int sum=0;
	while (head[a]!=head[b]){
		if (depth[head[a]]<depth[head[b]])swap(a, b);
		sum+=st->query(in[head[a]], in[a]);
		a=par[head[a]];
	}
	if (in[a]>in[b])swap(a, b);
	sum+=st->query(in[a], in[b]);
	return sum;
}

void hldupdatepath(int a, int b, int val){
	while (head[a]!=head[b]){
		if (depth[head[a]]<depth[head[b]])swap(a, b);
		st->up(in[head[a]], in[a], val);
		a=par[head[a]];
	}
	if (in[a]>in[b])swap(a, b);
	st->up(in[a], in[b], val);
}

int32_t main(){
	int n, q, a, b, c;
	cin>>n;
	st = new node(1, n);
	twok.resize(n+1, vector<int>(20));
	weight.resize(n+1);
	graph.resize(n+1);
	depth.resize(n+1);
	subtree.resize(n+1);
	par.resize(n+1);
	head.resize(n+1);
	in.resize(n+1);
	out.resize(n+1);
	for (int i=1; i<=n; ++i){
		cin>>weight[i];
	}
	for (int i=2; i<=n; ++i){
		cin>>a;
		graph[a].pb(i);
		graph[i].pb(a);
	}
	dfs(1, -1);
	twokdecomp(1, -1);
	head[1]= 1;
	hld(1, -1);
	cin>>q;
	while (q--){
		cin>>a;
		if (a==1){
			cin>>a;
			root = a;
		}
		else if (a==2){
			cin>>a>>b>>c;
			hldupdatepath(a, b, c);
		}
		else if (a==3){
			cin>>a>>b;
			if (root==a)st->up(1, n, b);
			else if (in[root]>=in[a] && in[root]<=out[a]){
				st->up(1, n, b);
				int enode = kthparent(root, depth[root]-depth[a]-1);
				st->up(in[enode], out[enode], -b);
			}
			else st->up(in[a], out[a], b);
		}
		else if (a==4){
			cin>>a>>b;
			cout<<hldquerypath(a, b)<<"\n";
		}
		else{
			cin>>a;
			if (root==a)cout<<st->query(1, n)<<"\n";
			else if (in[root]>=in[a] && in[root]<=out[a]){
				int enode = kthparent(root, depth[root]-depth[a]-1);
				cout<<st->query(1, n)-st->query(in[enode], out[enode])<<"\n";
			}
			else cout<<st->query(in[a], out[a])<<"\n";
		}
	}
}
