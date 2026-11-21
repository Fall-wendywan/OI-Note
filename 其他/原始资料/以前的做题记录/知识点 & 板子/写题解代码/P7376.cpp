#include<bits/stdc++.h>
#define int long long
#define IOS ios::sync_with_stdio(false);cin.tie(0);cout.tie(0)
using namespace std;
const int MAXN = 505;
int base = 249;
const int MOD = 998244353;
int N, K;
char mp[MAXN][MAXN];
int t[105];
long long nownum[MAXN], outhash[MAXN];//记录每行在窗口外的哈希值
signed main(){
    IOS;
	freopen( "ispit.in", "r", stdin ); 
	freopen( "ispit.out", "w", stdout ); 
    cin >> N >> K;
    for( int i = 1; i <= N; i ++ ){
        for( int j = 1; j <= N; j ++ ){
            cin >> mp[i][j];
        }
    }
    for( int i = 1; i <= N - K + 1; i ++ ){//枚举起始列
        int r = i + K - 1;
        memset( outhash, 0, sizeof outhash );
        memset( nownum, 0, sizeof nownum );//初始化
        
        for( int j = 1; j <= N; j ++ ){//行
            memset( t, 0, sizeof t );
            for( int k = i; k <= i + K - 1; k ++ ){
                t[mp[j][k] - 'a' + 1] ++;//使用桶计算字母出现个数
            }
            for( int k = 1; k <= 26; k ++ )
                nownum[j] = ( ( nownum[j] * base ) % MOD + t[k]) % MOD;
            //使用哈希方便比较
            for( int k = 1; k < i; k ++ )
                outhash[j] = ( outhash[j] * base + ( mp[j][k] - 'a' + 1 ) ) % MOD;
            for( int k = i + K; k <= N; k ++ )//k:i+K-1 +1记得不要从区间开始
                outhash[j] = ( outhash[j] * base + ( mp[j][k] - 'a' + 1 ) ) % MOD;
            //处理出区间外的哈希
        }
        for( int j = 1; j <= N; j ++ ){
            for( int k = 1; k < j; k ++ ){
                if( outhash[k] == outhash[j] && nownum[k] == nownum[j] )
                    return cout << "DA", 0;//判断
            }
        }
    }
    cout << "NE";
    return 0;
}
