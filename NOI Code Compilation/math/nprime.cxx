#include <bits/stdc++.h>
using namespace std;

bool isPrime(int pnum){
	int i = 2;
	while (i*i<=pnum){
		if (pnum%i==0){
			return false;
		}
		i++;
	}
	return true;
}

int main(){
	int n, count = 1, pcount = 0;
	cin >> n;
	while (pcount!=n){
		count++;
		if (isPrime(count)){
			pcount++;
		}
	}
	cout<<count;
}
