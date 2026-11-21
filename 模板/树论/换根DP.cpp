#include<bits/stdc++.h>
#define int long long
//https://www.luogu.com.cn/problem/P3478
using namespace std;
const int MAXN = 1e6+5;
int N;
int vis[MAXN], siz[MAXN], dep[MAXN], dp[MAXN], head[MAXN], cnt;
//siz[i]:以1为根节点时节点i的子树大小
//dep[i]:以1为根节点时节点i的深度大小
//dp[i]:以i为根节点时深度之和的大小
//第一个dfs求以1为根节点的深度之和 
struct edge{
	int nxt, to, num;
}e[MAXN * 2];
void add( int u, int v ){
	e[++ cnt].nxt = head[u];
	e[cnt].to = v;
	head[u] = cnt;
} 
void dfs1( int x ){
	siz[x] = 1;
	vis[x] = 1;
	for( int i = head[x]; i; i = e[i].nxt ){
		int v = e[i].to;
		if( !vis[v] ){
			dep[v] = dep[x] + 1;
			dfs1(v);
			siz[x] += siz[v];
		}
	}
} 
//第二次dfs换根
void dfs2( int x ){
	vis[x] = 1;
	for( int i = head[x]; i; i = e[i].nxt ){
		int v = e[i].to;
		if( !vis[v] ){
			dp[v] = dp[x] + siz[1] - 2 * siz[v];//转移 
			dfs2(v);
		}
	}
} 
signed main(){
	cin >> N;
	for( int i = 1; i < N; i ++ ){
		int u, v;
		cin >> u >> v;
		add( u, v );
		add( v, u ); 
	}
	dfs1(1);
	for( int i = 1; i <= N; i ++ ) dp[1] += dep[i];
	memset( vis, 0, sizeof(vis) );
	dfs2(1);
	int ans = -1, id;
	for( int i = 1; i <= N; i ++ ){
		if( ans < dp[i] ) ans = dp[i], id = i;
	}
	cout << id;
    return 0;
}