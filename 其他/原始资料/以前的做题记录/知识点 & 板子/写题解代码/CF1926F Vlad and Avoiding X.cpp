#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN = 10;
int N = 7, T;
bool mp[MAXN][MAXN];
bool chk( bool mp[][MAXN], int col ){//判断整个棋盘是否合法
    for( int i = 2; i < N; i ++ ){
        for( int j = 2; j < N; j ++ ){
            if( ( i + j ) % 2 != col ) continue;
            if( mp[i][j] && mp[i + 1][j + 1] && mp[i - 1][j - 1] && mp[i + 1][j - 1] && mp[i - 1][j + 1] )
                return false;
        }
    }
    return true;
}
int ans = 8;
bool dfs( bool a[][MAXN], vector<pair<int, int>> & grp, int idx, int nowans, int col ){
    //idx表示当前正在考虑grp[idx]这个点（dfs深度） nowans表示还剩几步 col表示当前是第几类
    if( nowans < 0 ) return false;//如果没次数了
    if( grp.size() - idx < nowans ) return false;
    if( idx == grp.size() ) return chk( a, col );
    if( dfs( a, grp, idx + 1, nowans, col ) ) return true;//根本就不用改这个点也能合法
    int x = grp[idx].first, y = grp[idx].second;
    a[x][y] = !a[x][y];
    if( dfs( a, grp, idx + 1, nowans - 1, col ) ){
        a[x][y] = !a[x][y];//这步和后面第30行都是回溯
        return true;  
    }
    a[x][y] = !a[x][y];
    return false;  
}
signed main(){
    cin >> T;
    while( T -- ){
        for( int i = 1; i <= N; i ++ ){
            for( int j = 1; j <= N; j ++ ){
                char ch;
                cin >> ch;
                mp[i][j] = ( ch == 'B' );
            }
        }
        vector<pair<int, int>> grp[3];//存储两个类
        for( int i = 1; i <= N; i ++ ){
            for( int j = 1; j <= N; j ++ ){
                grp[( i + j ) % 2].push_back({ i, j });
            }
        }
        int ans = 0;
        for( int col = 0; col <= 1; col ++ ){//棋盘染色后的两种
            int cnt = 5;
            for( int i = 0; i <= 4; i ++ ){//枚举最小操作次数
                if( dfs( mp, grp[col], 0, i, col ) ){
                    cnt = i;
                    break;
                }
            }
            ans += cnt;
        }
        cout << ans << endl;
    }
    return 0;
}