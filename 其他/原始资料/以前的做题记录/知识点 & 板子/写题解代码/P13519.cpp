#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN = 505;
const int inf = 0x3f3f3f3f3f3f3f3f;
int N, M; 
struct node { int u, v; }mem[MAXN * MAXN];
int dis[MAXN][MAXN], ans[MAXN * MAXN];
void floyd( int N ){//预处理
    for( int k = 1; k <= N; k ++ )
        for( int i = 1; i <= N; i ++ ){
            if( dis[i][k] == inf ) continue;
            for( int j = 1; j <= N; j ++ )
                dis[i][j] = min( dis[i][j], dis[i][k] + dis[k][j] );
        }
}
signed main(){
    freopen( "fee.in", "r", stdin );
    freopen( "fee.out", "w", stdout );
    cin >> N >> M;
    for( int i = 1; i <= N; i ++ ){
        for( int j = 1; j <= N; j ++ )
            dis[i][j] = dis[j][i] = inf;
        dis[i][i] = 0;
    }//初始化
    for( int i = 1; i <= M; i ++ ){
        int u, v;
        cin >> u >> v;
        mem[i] = { u, v };
        dis[u][v] = 1;
        dis[v][u] = 1;//输入->建最终图
    }
    floyd( N );//预处理最终的全源最短路
    for( int i = 1; i <= N; i ++ )
        for( int j = 1; j <= N; j ++ )
            ans[M] += dis[i][j];//算最终答案

    for( int i = M; i >= 1; i -- ){
        int u = mem[i].u, v = mem[i].v;
        int lst = dis[u][v];
        dis[u][v] = dis[v][u] = 0;
        if( lst > 0 ){//特判一下
            for( int j = 1; j <= N; j ++ )
                for( int k = 1; k <= N; k ++ )
                    dis[j][k] = min({ dis[j][k], dis[j][u] + dis[v][k], dis[j][v] + dis[u][k] });
            for( int j = 1; j <= N; j ++ )
                for( int k = 1; k <= N; k ++ )
                    ans[i - 1] += dis[j][k];
        } else ans[i - 1] = ans[i];
    }
    for( int i = 1; i <= M; i ++ ){
        cout << ans[i] << endl;
    }
    return 0;
}