#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN = 200020;
int N, Q, x, y, w;
int a[MAXN][4];
vector<pair<int, int>> row[MAXN], col[MAXN];//row[y] = {(x, w)}  col[x] = {(y, w)}
struct node{
    vector<int> p, sum;//坐标（方便二分） 前缀和
}srow[MAXN], scol[MAXN];

//预处理前缀和 a：存储前缀和数组 t：原数组
void pre( node & a, const vector<pair<int, int>> & t ){
    vector<pair<int, int>> tmp = t;
    sort( tmp.begin(), tmp.end() );//防止更改当前数组
    int n = tmp.size();
    a.p.resize( n ), a.sum.resize( n );//赋大小
    for( int i = 0; i < n; i ++ )//赋值（排序过后的）
        a.p[i] = tmp[i].first, a.sum[i] = tmp[i].second;
    for( int i = 1; i < n; i ++ )
        a.sum[i] += a.sum[i - 1];//处理前缀和
}

int solve( const node & p, int l, int r ){
    auto itl = lower_bound( p.p.begin(), p.p.end(), l );
    auto itr = upper_bound( p.p.begin(), p.p.end(), r );
    //二分当前区间开头和结尾
    if( itl >= itr ) return 0;
    int suml = ( itl- p.p.begin() ) > 0 ? p.sum[itl- p.p.begin() - 1] : 0;//找到区间头的值
    int sumr = p.sum[itr - p.p.begin() - 1];//尾的值
    return sumr - suml;
}
signed main(){
    freopen( "get.in", "r", stdin );
    freopen( "get.out", "w", stdout );
    cin >> N >> Q;
    for( int i = 1; i <= N; i ++ ){
        cin >> x >> y >> w;
        col[x].emplace_back( y, w ), row[y].emplace_back( x, w );
        //和push_back差不多，只是快一点~
    }

    for( int i = 1; i < MAXN; i ++ )
        pre( scol[i], col[i] ), pre( srow[i], row[i] );//预处理
    
    int x = 1, y = 1, tot = 0;//x和y表示当前坐标 tot记录答案
    while( Q -- ){
        int d, v;
        cin >> d >> v;
        if( d == 0 )
            tot += solve( srow[y], x + 1, x + v ), x += v;
        else if( d == 1 )
            tot += solve( scol[x], y + 1, y + v ), y += v;
        else if( d == 2 )
            tot += solve( srow[y], x - v, x - 1 ), x -= v;
        else if( d == 3 )
            tot += solve( scol[x], y - v, y - 1 ), y -= v;
        //分类查找答案即可，并且记得更新当前坐标
    }
    cout << tot;
    return 0;
}