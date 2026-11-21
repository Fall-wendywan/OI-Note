#include<bits/stdc++.h>

using namespace std;
const int MAXN = 5e4 + 5;
int fa[MAXN];

void init( int n ){
	for( int i = 1; i <= n; i ++ ) fa[i] = i;
}

int fd( int x ){
    if( fa[x] == x ) return x;
    else return fa[x] = fd( fa[x] );
}

void join( int x, int y ){// y 加入 x
    int fx = fd( x );
    int fy = fd( y );
    if( fx != fy ) fa[fx] = fy;
    return;
}

int main(){
    init( N );
    return 0;
}