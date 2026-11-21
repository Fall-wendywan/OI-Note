#include<bits/stdc++.h>
#define IOS ios::sync_with_stdio(false);cin.tie(0);cout.tie(0)
using namespace std;
const int MAXN = 15;
int N;
int a[10][MAXN][MAXN], b[10][MAXN][MAXN];
void read(){
    cin >> N;
    for( int i = 1; i <= N; i ++ )
        for( int j = 1; j <= i; j ++ )
            cin >> a[1][i][j];
    for( int i = 1; i <= N; i ++ )
        for( int j = 1; j <= i; j ++ )
            cin >> b[1][i][j];
}

void rot(){//旋转：rotation
    for( int i = 1; i <= N; i ++ ){
        int ii2 = N - i + 1;
        int jj1 = i;
        int jj2 = N - i + 1;
        for( int j = 1; j <= i; j ++, jj1 --, ii2 ++ ){
            int ii1 = N - j + 1;
            a[2][ii1][jj1] = a[1][i][j];
            b[2][ii1][jj1] = b[1][i][j];
            a[3][ii2][jj2] = a[1][i][j];
            b[3][ii2][jj2] = b[1][i][j];
        }
    }
}
void sym(){//对称：symmetry
    for( int i = 1; i <= N; i ++ )
        for( int j = 1; j <= i; j ++ ){
            a[4][i][i - j + 1] = a[1][i][j];
            a[5][i][i - j + 1] = a[2][i][j];
            a[6][i][i - j + 1] = a[3][i][j];
        
            b[4][i][i - j + 1] = b[1][i][j];
            b[5][i][i - j + 1] = b[2][i][j];
            b[6][i][i - j + 1] = b[3][i][j];
        }
}

int solve(){
    long long tot = 0, ans = 0x3f3f3f3f3f3f3f3f;
    for( int t1 = 1; t1 <= 6; t1 ++ )
        for( int t2 = 1; t2 <= 6; t2 ++ ){
            for( int i = 1; i <= N; i ++ )
                for( int j = 1; j <= i; j ++ )
                    tot += ( a[t1][i][j] != b[t2][i][j] );
            ans = min( ans, tot ), tot = 0;
        }
    return ans;
}
int main(){
    freopen( "tri.in", "r", stdin );
    freopen( "tri.out", "w", stdout );
    IOS;
    read();
    rot();
    sym();
    cout << solve();
    return 0;
}