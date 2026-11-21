#include<bits/stdc++.h>
//st表
using namespace std;
const int MAXN = 50005;
int N, Q;
int a, stmx[MAXN][32], stmn[MAXN][32];
void init( int n ){
    for( int t = 1; ( 1 << t ) <= n; t ++ ){
        for( int i = 1; i + ( 1 << t ) - 1 <= N; i ++ ){//枚举起点
            stmx[i][t] = max( stmx[i][t - 1], stmx[i + ( 1 << ( t - 1 ) )][t - 1] );
            stmn[i][t] = min( stmn[i][t - 1], stmn[i + ( 1 << ( t - 1 ) )][t - 1] );
        }
    }
}
int main(){
    cin >> N >> Q;
    // memset( stmx, -1, sizeof stmx );
    // memset( stmn, 0x3f, sizeof stmn );
    for( int i = 1; i <= N; i ++ ){
        // cin >> a[i];
        cin >> a;
        stmx[i][0] = a;
        stmn[i][0] = a;
    }
    init( N );
    while( Q -- ){
        int a, b;
        cin >> a >> b;
        int k = log2( b - a + 1 );
        cout << max( stmx[a][k], stmx[b - ( 1 << k ) + 1][k] ) - min( stmn[a][k], stmn[b - ( 1 << k ) + 1][k] ) << endl;
    }
    return 0;
}