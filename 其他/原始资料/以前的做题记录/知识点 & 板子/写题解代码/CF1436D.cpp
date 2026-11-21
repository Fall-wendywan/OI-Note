#include<bits/stdc++.h>
#define int long long
//https://codeforces.com/problemset/problem/1436/D
//https://www.luogu.com.cn/problem/CF1436D
using namespace std;
const int MAXN = 2e5 + 5;
int N;
int p, a[MAXN];
struct star{
    int nxt, to;
}edge[MAXN * 2];
int head[MAXN], cnt;
void add( int u, int v ){
    edge[++ cnt] = { head[u], v };
    head[u] = cnt;
}
int sum[MAXN];//表示以u为根的子树中，最终需要分配到其子树叶子节点的总权值
int dp[MAXN];//表示在u子树内最后权值最大的叶子节点权值最小的值
int sz[MAXN];//表示u的子树中有多少个是叶子节点
void dfs( int u, int fa ){
    bool flag = true;//记录是否到叶子
    sum[u] += a[u];//初始化自己价值
    for( int i = head[u]; i; i = edge[i].nxt ){
        int to = edge[i].to;
        if( to == fa ) continue;
        flag = false;//找到儿子，即非叶子
        dfs( to, u );
        sz[u] += sz[to], sum[u] += sum[to];//记录大小
        dp[u] = max( dp[u], dp[to] );//找到儿子中最大价值的叶子
    }
    if( flag ){
        sz[u] = 1, dp[u] = a[u], sum[u] = a[u];//如果是叶子，初始化
        return;
    }
    dp[u] = max( dp[u], ( sum[u] + sz[u] - 1 ) / sz[u] );//贪心地分配个每个叶子节点
    //这个式子等价于ceil( 1.0 * sum[u] / sz[u] )
}

signed main(){
    cin >> N;
    for( int i = 2; i <= N; i ++ ){
        cin >> p;
        add( p, i ), add( i, p );
    }
    for( int i = 1; i <= N; i ++ ) cin >> a[i];
    dfs( 1, 0 );
    cout << dp[1];
    return 0;
}