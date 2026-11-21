#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN = 3e6 + 5;
const int MOD = 998244353;
int N, M, ans = 0;

int fac[MAXN], inv[MAXN];

void pre(){
    fac[0] = fac[1] = inv[0] = inv[1] = 1;
    for( int i = 2; i < MAXN; i ++ ){
        fac[i] = fac[i - 1] * i % MOD;
        inv[i] = ( MOD - MOD / i ) * inv[MOD % i] % MOD;
    }
    for( int i = 1; i < MAXN; i ++ ) inv[i] = inv[i] * inv[i - 1] % MOD;
}

int C( int a, int b ){
    return fac[a] * inv[b] % MOD * inv[a - b] % MOD;
}

signed main(){
    cin >> N >> M;
    pre();
    
    int st = min( M, N );
    if( st % 2 != M % 2 ) st --;//特判超过 & 奇偶性不相同情况

    for( int i = st; i >= 0; i -= 2 ){
        ans += C( N, i ) % MOD * C( ( 3 * M - i ) / 2 + N - 1, N - 1 ) % MOD;
        ans %= MOD;
    }   
    ans = ( ans - N * C( M + N - 2, N - 1 ) % MOD + MOD ) % MOD;//减去非法情况
    cout << ans;
    return 0;
}