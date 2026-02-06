#include <iostream>
using namespace std;

const int segmenttree_size = 100;
int arr[segmenttree_size], segmenttree[4*segmenttree_size], lazytree[4*segmenttree_size];

void build(int index, int low, int high){
	if (low==high){
		segmenttree[index] = arr[low];
		return;
	}
	int mid = (low+high)/2;
	build(2*index+1, low, mid);
	build(2*index+2, mid+1, high);
	segmenttree[index] = segmenttree[2*index+1] + segmenttree[2*index+2];
}

int query(int index, int low, int high, int left, int right){
	if (lazytree[index]!=0){
		segmenttree[index]+=(high - low + 1) * lazytree[index];
		if (low!=high){
			lazytree[2*index+1]+=lazytree[index];
			lazytree[2*index+2]+=lazytree[index];
		}
		lazytree[index] = 0;
	}
	if (high<left || low>right){
		return 0;
	}
	
	if (low>=left && high<=right){
		return segmenttree[index];
	}
	int mid = (low+high)/2;
	int l = query(2*index+1, low, mid, left, right);
	int r = query(2*index+2, mid+1, high, left, right);
	return l + r;
}

void rangeupdate(int index, int low, int high, int left, int right, int updatenum){
	if (lazytree[index]!=0){
		segmenttree[index]+=(high - low + 1) * lazytree[index];
		if (low!=high){
			lazytree[2*index+1]+=lazytree[index];
			lazytree[2*index+2]+=lazytree[index];
		}
		lazytree[index] = 0;
	}
	
	if (left>high || right<low){
		return;
	}
	
	if (left<=low && right>=high){
		segmenttree[index]+=(high - low + 1) * updatenum;
		if (low!=high){
			lazytree[2*index+1]+=updatenum;
			lazytree[2*index+2]+=updatenum;
		}
		return;
	}
	
	int mid = (low+high)/2;
	rangeupdate(2*index+1, low, mid, left, right, updatenum);
	rangeupdate(2*index+2, mid+1, high, left, right, updatenum);
	segmenttree[index]= segmenttree[2*index+1] + segmenttree[2*index+2];
}


int main(){
	int n, q, t, l, r, k;
	cin>>n>>q;
	while (q--){
		cin>>t;
		if (t==1){
			cin>>l>>r>>k;
			rangeupdate(0, 0, n-1, l-1, r-1, k);
		}
		else{
			cin>>l>>r;
			cout<<query(0, 0, n-1, l-1, r-1)<<"\n";
		}
	}
}
