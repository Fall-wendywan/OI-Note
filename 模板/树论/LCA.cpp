lca
```
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e5 + 5;
int N;
//================
int cnt = 0, head[MAXN];
struct star{
    int nxt, to, w;
}edge[MAXN * 2];

void add( int u, int v, int w ){
    edge[++ cnt].nxt = head[u];
    edge[cnt].to = v;
    edge[cnt].w = w;
    head[u] = cnt;
}
//================star_edge
int f[MAXN][21], dep[MAXN];
void dfs( int u, int fa ){
    dep[u] = dep[fa] + 1;
    f[u][0] = fa;
    for( int i = 1; i <= 20; i ++ ){
        f[u][i] = f[f[u][i - 1]][i - 1];//初始化倍增数组
    }
    for( int i = head[u]; i; i = edge[i].nxt ){
        int to = edge[i].to;
        if( to != fa ) dfs( to, u );
    }
}

int lca( int x, int y ){
    if( dep[x] < dep[y] ) swap( x, y );
    for( int i = 20; i >= 1; i -- ){
        if( dep[f[x][i]] > dep[y] ) x = f[x][i];
    }
    if( x == y ) return x;
    for( int i = 20; i >= 1; i -- ){
        if( f[x][i] != f[y][i] ) x = f[x][i], y = f[y][i];
    }
    return f[x][0];
}
int main(){
    cin >> N;
    for( int i = 1; i <= N; i ++ ){
        int u, v, w;
        cin >> u >> v >> w;
        add( u, v, w );
        add( v, u, w );
    }

    return 0;
}
```