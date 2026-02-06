#include <iostream>
using namespace std;

const int segmenttree_size = 100;
int arr[segmenttree_size], segmenttree[4*segmenttree_size];

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
	if (low>=left && high<=right){
		return segmenttree[index];
	}
	if (high<left || low>right){
		return 0;
	}
	int mid = (low+high)/2;
	int l = query(2*index+1, low, mid, left, right);
	int r = query(2*index+2, mid+1, high, left, right);
	return l + r;
}

void update(int index, int low, int high, int indexinp, int addition){
	if (low == high){
		segmenttree[index] += addition;
	}
	else{
		int mid = (low+high)/2;
		if (low<=indexinp && indexinp<=mid){
			update(2*index+1, low, mid, indexinp, addition);
		}
		else{
			update(2*index+2, mid+1, high, indexinp, addition);
		}
		segmenttree[index] = segmenttree[2*index+1] + segmenttree[2*index+2];
	}
}

int main(){
	int n, a;
	cin>>n;
	for (int i=0; i<n; ++i){
		cin>>a;
		arr[i]=a;
	}
	build(0, 0, n-1);
	update(0, 0, n-1, 3, 5);
	for (int i=0; i<400; i++){
		cout<<segmenttree[i]<<endl;
	}
}
