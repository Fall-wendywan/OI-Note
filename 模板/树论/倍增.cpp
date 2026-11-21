#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN = 2e5 + 5;
int N, K;//N个城镇 K次传送
int dp[MAXN][65], now = 1, t;
//倍增数组 i, j表示在i点跳2^j次方的点  计算二的方

void solve(){
    for( int j = 1; j <= 60; j ++ ){
        for( int i = 1; i <= N; i ++ ){
            dp[i][j] = dp[dp[i][j - 1]][j - 1];
            // cout<< dp[i][j] << " \n .sfsf \n";
        }
    }
}
signed main(){
    cin >> N >> K;
    for( int i = 1; i <= N; i ++ ) cin >> dp[i][0];
    return 0;
}