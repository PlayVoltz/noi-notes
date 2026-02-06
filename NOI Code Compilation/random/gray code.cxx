#include <bits/stdc++.h>
#include "battleship.h"
using namespace std;

bitset<192> temp;
vector<bitset<192> > vect(1<<19);

void dnc(int l, int r, int id, int level){
	if (l>=r)return;
	int mid=(l+r)/2;
	vect[mid][id]=1;
	for (int i=l; i<mid; ++i)vect[i]|=(bitset<192>(((i-l+1)^((i-l+1)>>1)^(i-l)^((i-l)>>1)))<<(id+1));
	dnc(l, mid-1, id+level, level-1);
	dnc(mid+1, r, id+level, level-1);
}

int calc(int l, int r, int id, int level){
	if (l==r)return l;
	int mid=(l+r)/2;
	if (temp[id])return mid;
	for (int i=id+1; i<id+level; ++i)if (temp[i])return calc(l, mid-1, id+level, level-1);
	return calc(mid+1, r, id+level, level-1);
}

vector<bitset<192> > init(){
	dnc(0, (1<<19)-1, 0, 19);
	return vect;
}

int answer(bitset<192> a){
	temp=a;
	return calc(0, (1<<19)-1, 0, 19);
}
