#include<bits/stdc++.h>
#define int long long

using namespace std;
const int MAXN = 2e5 + 5;
const int INF = 0x3f3f3f3f3f3f3f3f;
int N;
int d;
// int d[MAXN][2];//d[u][0/1]表示点u的最长距离以及次长距离
//================
int cnt = 0, head[MAXN];
struct star{
    int nxt, to, w;
}e[MAXN * 2];
void add( int u, int v, int w ){
    e[++ cnt].nxt = head[u];
    e[cnt].to = v;
    e[cnt].w = w;
    head[u] = cnt;
}
//===============star_edge
int dis[MAXN];
int dfs( int u, int fa, int w ){
    dis[u] = dis[fa] + w;
    int ans = u;
    for( int i = head[u];i; i = e[i].nxt ){
        int to = e[i].to;
        if( to == fa ) continue;
        int a = dfs( to, u, e[i].w );
        if( dis[ans] < dis[a] ) ans = a;
    }
    return ans;
}
//==============直径

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    // freopen( "d.in", "r", stdin );
    // freopen( "d.out", "w", stdout ); 
    cin >> N;
    for( int i = 1; i < N; i ++ ){
        int u, v, w;
        cin >> u >> v >> w;
        add( u, v, w );
        add( v, u, w );
    }
    int ccnt = N;
    for( int i = 1; i <= N; i ++ ){
        cin >> d;
        add( i, ++ ccnt, d );
    }
    
    return 0;
}