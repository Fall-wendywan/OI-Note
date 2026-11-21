#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN = 1e5 + 3;
const int inf = 1e8;
int N, K, ans;
int a, t[MAXN], maxx, sum[MAXN], sum1[MAXN];
signed main(){
    // freopen( "weight.in", "r", stdin );
    // freopen( "weight.out", "w", stdout );
    ios::sync_with_stdio( 0 );
    cin.tie( 0 ), cout.tie( 0 );
    cin >> N >> K;
    for( int i = 1; i <= N; i ++ )
        cin >> a, t[a] ++, maxx = max( maxx, a );
    for( int i = 1; i <= maxx; i ++ )//sum1是方便找到断点后计算的
        sum[i] = sum[i - 1] + t[i] * ( i + 2 ), sum1[i] = sum1[i - 1] + t[i];
    for( int T = 1; T <= K; T ++ ){
        int pos = inf;
        for( int i = 0; i <= maxx; i += T ){
            int ed = min( maxx, i + T - 1 );
            if( ( ed / T ) * ( ed + 2 ) > inf ){
                int l = i, r = ed, anss = ed;
                while( l <= r ){
                    int mid = ( l + r ) >> 1;
                    if( ( mid / T ) * ( mid + 2 ) > inf ) r = mid - 1, anss = mid;
                    else l = mid + 1;
                }
                pos = anss - 1;//最后一位<1e8的
                ans += ( sum[pos] - sum[i - 1] ) * ( i / T );
                break;
            }
            ans += ( sum[ed] - sum[i - 1] ) * ( i / T );
        }
        if( pos != inf )
            ans += ( sum1[maxx] - sum1[pos] ) * inf;
    }
    cout << ans;
    return 0;
}