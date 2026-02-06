#include <ext/rope>
#include <bits/stdc++.h>
using namespace std;

int i=1;
__gnu_cxx::crope vect[1000005];

void Init(){}

void TypeLetter(char l){
	vect[i]=vect[i-1]+l, ++i;
}

void UndoCommands(int u){
	vect[i]=vect[i-u-1], ++i;
}

char GetLetter(int c){
	return vect[i-1][c];
}
