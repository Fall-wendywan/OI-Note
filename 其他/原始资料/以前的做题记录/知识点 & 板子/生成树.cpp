#include<bits/stdc++.h>
/*
link:
http://goj.wiki/d/junior/p/P769
https://www.luogu.com.cn/problem/P2619
--------------------------------------
二分+最小生成树

*/
using namespace std;
const int MAXN = 5e4 + 5;
int N, M, nd, ans;
struct star{
    int s, t, c, col;
}edge[MAXN * 2];

struct DSU {
    int fa[MAXN];
    void init(){
        for( int i = 1; i < MAXN; i ++ ) fa[i] = i;
    }
    void join( int x, int y ){ fa[x] = y; }//将x加入y
    int find( int x ){
        if( fa[x] == x ) return x;
        else return fa[x] = find( fa[x] );
    }
};

bool cmp( star a, star b ){ return ( a.c == b.c ) ? a.col < b.col : a.c < b.c; }
int cnt = 0, tmp = 0, sum = 0;
void kruskal(){
    sort( edge + 1, edge + M + 1, cmp );
    DSU dsu;
    dsu.init();
    cnt = 0, tmp = 0, sum = 0;
    for( int i = 1; cnt != N - 1; i ++ ){
        int x = dsu.find( edge[i].s ), y = dsu.find( edge[i].t );
        if( x != y ){
            cnt ++;
            dsu.join( x, y );
            if( edge[i].col == 0 ) tmp ++;
            sum += edge[i].c;
        }
    }
}
//这个↑是不建图的
bool cmp( notatruestar a, notatruestar b ){ return a.w > b.w; }
void kruskal(){//最大生成树
/*想起来原理了：
其实就是排一遍序，从到大小加入图并保持为一棵树（用并查集维护）*/
    sort( edge1 + 1, edge1 + M + 1, cmp );
    for( int i = 1; i <= N; i ++ ) fa[i] = i;
    for( int i = 1; i <= M; i ++ ){
        if( find( edge1[i].u ) != find( edge1[i].v ) ){//如果不在同一集合
            fa[find( edge1[i].u )] = find( edge1[i].v );
            add( edge1[i].u, edge1[i].v, edge1[i].w );
            add( edge1[i].v, edge1[i].u, edge1[i].w );
        }
    }
    return;
}
//这个是建图的
int main(){
    return 0;
}