#include<bits/stdc++.h>
#define IOS \
ios::sync_with_stdio(false);\
cin.tie(0);\
cout.tie(0);
#define int long long
/*
link:
https://vjudge.net/contest/773492#problem/A
https://www.luogu.com.cn/problem/AT_arc206_b 
https://atcoder.jp/contests/arc206/tasks/arc206_b
-------------------------------------------------

*/
using namespace std;
const int MAXN = 2e5 + 5;
int N;
int p[MAXN], c[MAXN];
struct TREE{
    int xx[MAXN << 2] = { 0 };//维护区间最大值

    void upd( int p ){ xx[p] = max( xx[p << 1], xx[p << 1 | 1] ); }

    void build( int p, int l, int r ){
        if( l == r ){
            xx[p] = 0;
            return;
        }
        if( xx[p] == 0 ) return;//减枝
        int mid = ( l + r ) >> 1;
        build( p << 1, l, mid );
        build( p << 1 | 1, mid + 1, r );
        upd( p );
    }

    int query( int p, int l, int r, int x, int y ){
        if( x <= l && r <= y ) return xx[p];
        int mid = ( l + r ) >> 1, res = 0;
        if( x <= mid ) res = max( res, query( p << 1, l, mid, x, y ) );
        if( y > mid ) res = max( res, query( p << 1 | 1, mid + 1, r, x, y ) );
        return res;
    }

    void mdf( int p, int l, int r, int x, int y ){
        if( l == r ){
            xx[p] = y;
            return;
        }
        int mid = ( l + r ) >> 1;
        if( x <= mid ) mdf( p << 1, l, mid, x, y );
        else mdf( p << 1 | 1, mid + 1, r, x, y );
        upd( p );
    }
}tr;
vector<int> col[MAXN];

int solve( vector<int> & now ){
    tr.build( 1, 1, N );
    int ans = 0;
    for( int x : now ){
        int a = ( x == 1 ) ? 0 : tr.query( 1, 1, N, 1, x - 1 );
        tr.mdf( 1, 1, N, x, a + 1 );
        ans = max( ans, a + 1 );//维护lis
    }
    return ans;
}
signed main(){
    IOS;
    cin >> N;
    for( int i = 1; i <= N; i ++ ){
        cin >> p[i];
    }
    int sumc = 0;
    for( int i = 1; i <= N; i ++ ){
        cin >> c[i];
        sumc += c[i];//计算总和 
        col[c[i]].push_back( p[i] );
    }
    int ans = 0;
    for( int i = 1; i <= N; i ++ ){
        if( col[i].empty() ) continue;
        ans += i * solve( col[i] );//此处代价还要乘上先前颜色
    }
    cout << sumc - ans;//减去
    return 0;
}