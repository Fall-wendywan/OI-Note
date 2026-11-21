#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5 + 5;
int N, cnt;
int a[MAXN];
int tr[MAXN * 32][2];

void insert( int x ){
    int root = 0;
    for( int i = 31; i >= 0; i -- ){
        int u = ( x >> i ) & 1;
        if( tr[root][u] == 0 ) tr[root][u] = ++ cnt;
        root = tr[root][u];
    }
}

int Query( int x ){
    int root = 0;
    int res = 0;
    for( int i = 31; i >= 0; i -- ){
        int u = ( x >> i ) & 1;
        int newroad = u ^  1;//相反路径
        if( tr[root][newroad] ){
            res += ( 1 << i );//当前位置可以为1 更新尽量最大
            root = tr[root][newroad];
        }
        else{
            root = tr[root][u];
        }
    }
    return res;
}
int main(){
    cin >> N;
    for( int i = 1; i <= N; i ++ ){
        cin >> a[i];
        insert( a[i] );
    }
    
    int ans = 0;
    for( int i = 1; i <= N; i ++ ){
        ans = max( ans, Query( a[i] ) );
    }
    
    cout << ans << endl;
    return 0;
}