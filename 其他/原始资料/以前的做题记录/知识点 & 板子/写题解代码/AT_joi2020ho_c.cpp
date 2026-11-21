#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN = 205;
const int inf = 0x3f3f3f3f3f3f3f3f;
int N, L;
int a[MAXN], t[MAXN];
int dp[MAXN][MAXN][MAXN][2];
signed main(){
    cin >> N >> L;
    for( int i = 1; i <= N; i ++ ) cin >> a[i];
    for( int i = 1; i <= N; i ++ ) cin >> t[i];

    a[0] = 0, a[N + 1] = L;
    memset( dp, 0x3f, sizeof dp );
    dp[0][N + 1][0][0] = 0;
    dp[0][N + 1][0][1] = 0;//初始化

    for( int l = 0; l <= N; l ++ ){
        for( int r = N + 1; r > l + 1; r -- ){//枚举区间
            for( int m = 0; m <= l + ( N + 1 - r ); m ++ ){//枚举买的个数
                int tim = dp[l][r][m][0] + ( a[l + 1] - a[l] );
                dp[l + 1][r][m + ( tim <= t[l + 1] )][0] = min( dp[l + 1][r][m + ( tim <= t[l + 1] )][0], tim );
                tim = dp[l][r][m][0] + a[l] + ( L - a[r - 1] );
                dp[l][r - 1][m + ( tim <= t[r - 1] )][1] = min( dp[l][r - 1][m + ( tim <= t[r - 1] )][1], tim );

                tim = dp[l][r][m][1] + ( a[r] - a[r - 1] );
                dp[l][r - 1][m + ( tim <= t[r - 1] )][1] = min( dp[l][r - 1][m + ( tim <= t[r - 1] )][1], tim );
                tim = dp[l][r][m][1] + a[l + 1] + ( L - a[r] );
                dp[l + 1][r][m + ( tim <= t[l + 1] )][0] = min( dp[l + 1][r][m + ( tim <= t[l + 1] )][0], tim );
            }//四种情况讨论
        }
    }
    int ans = 0;
    for( int m = 1; m <= N; m ++ ){
        for( int l = 0; l <= N; l ++ ){
            for( int r = N + 1; r >= 1; r -- ){
                if( l > r ) continue;
                if( dp[l][r][m][0] < inf || dp[l][r][m][1] < inf ){
                    ans = m;
                    break;
                }
            }
            if( ans == m ) break;
        }
        if( ans != m ) break;
    }
    cout << ans;
    return 0;
}