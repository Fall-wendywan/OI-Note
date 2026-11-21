#include<bits/stdc++.h>
//vjudge->https://vjudge.net/contest/748290#problem/D
//luogu->https://www.luogu.com.cn/problem/P1776
//tij->https://www.luogu.com.cn/article/wrzsfyhc

//多重背包二进制拆分优化
using namespace std;
const int MAXN = 1e5 + 5;
int N, W;
// int v, w, m;
int a, b, c;
// struct node{
    int v[MAXN], w[MAXN];
    //价值 重量 件数
// }thi[MAXN];
int dp[MAXN];//dp[i][j]表示前i件物品 花费j的重量（代价）所得到的最大价值 i可以滚动
//本来是将所有物品拆分成类似01背包的东西 
//但是我们发现这样会超时
//考虑二进制拆分
int main(){
    cin >> N >> W;
    int cnt = 0;
    for( int i = 1; i <= N; i ++ ){
        // cin >> thi[i].v >> thi[i].w >> thi[i].m;
        cin >> a >> b >> c;
        for( int j = 1; j <= c; j <<= 1 ){//很容易的二进制拆分
            v[++ cnt] = a * j;
            w[cnt] = b * j;
            c -= j;
        }
        if( c ){//如果多出来的取差值
            v[++ cnt] = a * c;
            w[cnt] = b * c;
        }
    }


    for( int i = 1; i <= cnt; i ++ ){
        for( int j = W; j >= w[i]; j -- ){
            dp[j] = max(dp[j], dp[j - w[i]] + v[i]);//十分显然的转移
        }
    }

    cout << dp[W];
    return 0;
}