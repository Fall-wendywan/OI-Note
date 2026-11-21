#include<bits/stdc++.h>

using namespace std;
const int MAXN = 2e5 + 5;
int N, Q, u, v;
int cnt, head[MAXN];

struct star{
    int nxt, to, w;
}edge[MAXN * 2];

void add( int u, int v ){
    edge[++ cnt].nxt = head[u];
    edge[cnt].to = v;
    edge[cnt].w = 1;
    head[u] = cnt;
}
int t;
int sz[MAXN], dep[MAXN], dfn[MAXN], top[MAXN], fa[MAXN], hson[MAXN];
void dfs1( int u, int p ){
    sz[u] = 1;
    for( int i = head[u]; i; i = edge[i].nxt ){
        int v = edge[i].to;
        if( p == v ) continue;
        dep[v] = dep[u] + 1;
        fa[v] = u;
        dfs1( v, u );
        sz[u] += sz[v];
        if( !hson[u] || sz[v] > sz[hson[u]] ) hson[u] = v; 
    }
}

void dfs2( int u, int p ){
    dfn[u] = ++ t;
    if( !hson[u] ) return;
    top[hson[u]] = top[u];
    dfs2( hson[u], u );
    for( int i = head[u]; i; i = edge[i].nxt ){
        int v = edge[i].to;
        if( v == p || v == hson[u] ) continue;
        top[v] = v;
        dfs2( v, u );
    }
}

int lca( int u, int v ) {
	if ( top[u] == top[v] ) return dep[u] < dep[v] ? u : v;
	if ( dep[top[u]] < dep[top[v]] ) return lca( u, fa[top[v]] );
	else return lca( fa[top[u]], v );
}

int main(){
    cin >> N;
    for( int i = 1; i < N; i ++ ){
        cin >> u >> v;
        add( u, v );
        add( v, u );
    }
    dfs1( 1, -1 );
    fa[1] = top[1] = 1;
    dfs2( 1, -1 );
    cin >> Q;
    while( Q -- ){
        cin >> u >> v;
        cout << lca( u, v ) << endl;
    }
    return 0;
}