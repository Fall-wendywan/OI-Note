const int MAXN = 4005;
const int MOD = 998244353;
int N, K;
int fac[MAXN], inv[MAXN];
void pre(){//预处理阶乘逆元
    fac[0] = fac[1] = inv[0] = inv[1] = 1;
    for( int i = 2; i < MAXN; i ++ ){
        fac[i] = ( fac[i - 1] * i ) % MOD;
        inv[i] = ( MOD - MOD / i ) * inv[MOD % i] % MOD;
    }
    for( int i = 1; i < MAXN; i ++ ) inv[i] = inv[i - 1] * inv[i] % MOD;
}

int C( int n, int m ){//组合数计算
    if( m < 0 || m > n ) return 0;
    return fac[n] * inv[m] % MOD * inv[n - m] % MOD;
}
signed main(){
    cin >> K >> N;
    pre();
    for( int i = 2; i <= 2 * K; i ++ ){
        int l = max( 1LL, i - K ), r = ( i - 1 ) / 2;//找到a的上界下界
        int a = ( l <= r ) ? ( r - l + 1 ) : 0, b = 0;
        if( i % 2 == 0 && i / 2 >= 1 && i / 2 <= K ) b = 1;
        
        int s = a + b, t = K - a - b;
        int ans = 0;
        for( int j = 0; j <= min( N, s ); j ++ ){
            ans += C( s, j ) % MOD * C( t + N - j - 1, N - j ) % MOD;
            ans %= MOD;
        }
        cout << ans << endl;
    }
    return 0;
}