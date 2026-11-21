#include<bits/stdc++.h>

using namespace std;
const int MAXN = 2e5 + 5;
int N, K;
struct star{
    int nxt, to;
}edge[MAXN * 2];
int head[MAXN], cnt;
void add( int u, int v ){
    edge[++ cnt] = { head[u], v };
    head[u] = cnt;
}
int dp[MAXN];//dp[u]表示u需要最少多少加油站
int now[MAXN];
//now[u]表示u的子树中最深节点的深度，用与计算从u出发向上能找到多长的未覆盖的路径
int dep[MAXN];//dep[u]表示以1为根树上u的深度
void dfs( int u, int fa ){
    int max1 = 0, max2 = 0;//记录出最大的两个未覆盖的路径
    //此处用于判断u是否需要设置加油站
    now[u] = dep[u];//u自己可能是一个最深点 -> 初始化
    for( int i = head[u]; i; i = edge[i].nxt ){
        int to = edge[i].to;
        if( to == fa ) continue;
        dep[to] = dep[u] + 1;//处理深度
        dfs( to, u );
        dp[u] += dp[to];//累加儿子的加油站总数
        if( now[to] > max1 ) max2 = max1, max1 = now[to];
        else max2 = max( max2, now[to] );//更新最大以及次大值
        now[u] = max( now[u], now[to] );//取出最大深度
    }
    int x = max( max1 - dep[u], 0 ), y = max( max2 - dep[u], 0 );
    //注意：此处我们计算的是从根到此处最大的两个值，所以要-dep
    if( x + y >= K ){//如果大于 -> 这个点需要放加油站
        dp[u] ++;//建站
        now[u] = dep[u] - 1;//表示当前不能再选了。
    }
}

int main(){
    cin >> N >> K;
    for( int i = 1; i < N; i ++ ){
        int x, y;
        cin >> x >> y;
        add( x, y );
        add( y, x );
    }
    dep[1] = 1;//初始化深度
    dfs( 1, 0 );
    cout << dp[1];
    return 0;
}
