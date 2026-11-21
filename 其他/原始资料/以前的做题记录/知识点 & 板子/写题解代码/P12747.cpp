#include<bits/stdc++.h>

using namespace std;
const int MAXN = 2e5 + 5;
struct star{
    int nxt, to;
}edge[MAXN * 2];
int head[MAXN], cnt;
void add( int u, int v ){
    edge[++ cnt] = { head[u], v };
    head[u] = cnt;
}

int N, in[MAXN], ans = -1e9, u, v;
int dp[MAXN];//dp[u]表示在u的子树中，从u出发向下的最大in路径和
void dfs( int u, int fa ){
    vector<int> ch;//->child 儿子的dp值
    for( int i = head[u]; i; i = edge[i].nxt ){
        int v = edge[i].to;
        if( v == fa ) continue;
        dfs( v, u );
        ch.emplace_back( dp[v] );//丢进来
    }
    dp[u] = in[u];//初始化 
    if( ch.empty() ) return;
    sort( ch.begin(), ch.end(), greater<int>() );
    ans = max( ans, in[u] + ch[0] );
    //第一个：u + 一个子节点
    if( ch.size() >= 2 ) ans = max( ans, in[u] + ch[0] + ch[1] );
    //第二个：子链1 + u + 子链2
    dp[u] = in[u] + max( 0, ch[0] );
    //更新 即返回从u向下的最大链和
}

int main(){
	// freopen( "parade.in", "r", stdin );
	// freopen( "parade.out", "w", stdout ); 
    cin >> N;
    for( int i = 1; i < N; i ++ ){
        cin >> u >> v;
        add( u, v ), add( v, u );
        in[u] ++, in[v] ++;
    }
    for( int i = 1; i <= N; i ++ ) in[i] -= 2;
    //预处理
    dfs( 1, 0 );
    cout << ans + 2;
    return 0;
}
