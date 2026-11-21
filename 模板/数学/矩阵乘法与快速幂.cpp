#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN = 105;
const int MOD = 1e9 + 7;
/*
这是封装过后的
C 的 (i, j) 元素 = A 的第 i 行 与 B 的第 j 列 的点积 
*/
int N, k;
struct matrix{
    int a[MAXN][MAXN];

    void init(){
        for( int i = 1; i <= N; i ++ )
            for( int j = 1; j <= N; j ++ )
                a[i][j] = ( i == j );
    }

    matrix operator * ( const matrix & b ) const {
        matrix ans;
        for( int i = 1; i <= N; i ++ )
            for( int j = 1; j <= N; j ++ ){
                ans.a[i][j] = 0;
                for( int r = 1; r <= N; r ++ )
                    ans.a[i][j] = ( (long long) a[i][r] * b.a[r][j] % MOD + ans.a[i][j] % MOD ) % MOD;
            }
        return ans;
    }
    matrix qmpow( int x ){
        matrix ans, base;
        ans.init();
        base = *this;
        while( x ){
            if( x & 1 ) ans = ans * base;
            base = base * base;
            x >>= 1;
        }
        return ans;
    }
}a;
signed main(){
    cin >> N >> k;
    for( int i = 1; i <= N; i ++ )
        for( int j = 1; j <= N; j ++ )
            cin >> a.a[i][j];
    if( k == 0 ){
        for( int i = 1; i <= N; i ++ ){
            for( int j = 1; j <= N;j ++ )
                cout << ( i == j ) << " ";
            cout << endl;
        }
        return 0;
    }
    matrix m = a.qmpow( k );
    for( int i = 1; i <= N; i ++ ){
        for( int j = 1; j <= N; j ++ ){
            cout << m.a[i][j] << " ";
        }
        cout << endl;
    }
    return 0;
}