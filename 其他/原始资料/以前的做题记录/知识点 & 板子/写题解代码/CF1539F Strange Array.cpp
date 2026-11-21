#include<bits/stdc++.h>
/*
2026.4.3
https://www.luogu.com.cn/problem/CF1539F
https://codeforces.com/problemset/problem/1539/F
数据结构题，涉及到维护包含x位置数的最大和区间的计算。
*/
using namespace std;
const int MAXN = 2e5 + 5;
int N, ans[MAXN];
struct node1{
    int x, id;
}a[MAXN];

bool cmp( node1 a, node1 b ){ return a.x < b.x; }

struct node{
    int sum, ls, rs;//ls：以x为结尾的最大后缀和 rs:以x为开头的最大前缀和。
}tr[MAXN << 2];

struct Segtree{

    void pushup( int p ){
        tr[p].sum = tr[p << 1].sum + tr[p << 1 | 1].sum;
        tr[p].ls = max( tr[p << 1].ls, tr[p << 1].sum + tr[p << 1 | 1].ls );
        tr[p].rs = max( tr[p << 1 | 1].rs, tr[p << 1].rs + tr[p << 1 | 1].sum );
    }

    void build( int p, int l, int r ){
        if( l == r ){
            tr[p].sum = tr[p].ls = tr[p].rs = -1;
            return;
        }
        int mid = ( l + r ) >> 1;
        build( p << 1, l, mid ), build( p << 1 | 1, mid + 1, r );
        pushup( p );
    }

    void mdf( int p, int l, int r, int x, int y ){//每次改变 a_x 的时候修改
        if( l == r ){
            tr[p].sum = tr[p].ls = tr[p].rs = y;
            return;
        }
        int mid = ( l + r ) >> 1;
        if( mid >= x ) mdf( p << 1, l, mid, x, y );
        else mdf( p << 1 | 1, mid + 1, r, x, y );
        pushup( p );
    }

    node qry( int p, int l, int r, int x, int y ){//查询包含 x 的区间中的最大和
        if( l > y || r < x ) return { 0, 0, 0 };
        if( x <= l && r <= y )  return tr[p];
        int mid = ( l + r ) >> 1;
        node L = qry( p << 1, l, mid, x, y ), R = qry( p << 1 | 1, mid + 1, r, x, y );
        return { L.sum + R.sum, max( L.ls, L.sum + R.ls ), max( R.rs, L.rs + R.sum ) };
    }
}t;
int main(){
    cin >> N;
    for( int i = 1; i <= N; i ++ ){
        cin >> a[i].x;
        a[i].id = i;
    }
    t.build( 1, 1, N );
    sort( a + 1, a + N + 1, cmp );
    for( int i = 1; i <= N; i ++ ){
        int j = i;
        while( j <= N && a[j].x == a[i].x ) j ++;j --;//找到一段相等的区间
        for( int k = i; k <= j; k ++ ) t.mdf( 1, 1, N, a[k].id, 1 );
        for( int k = i; k <= j; k ++ ){
            node L = t.qry( 1, 1, N, 1, a[k].id ), R = t.qry( 1, 1, N, a[k].id, N );
            ans[a[k].id] = max( ans[a[k].id], L.rs + R.ls - 2 );//按照推出的式子统计答案
        }
        i = j;
    }

    for( int i = 1; i <= N; i ++ ) a[i].x = -a[i].x;//反转一遍
    for( int i = 1; i <= N / 2; i ++ )
        swap( a[i], a[N - i + 1] );
    t.build( 1, 1, N );
    sort( a + 1, a + N + 1, cmp );
    
    for( int i = 1; i <= N; i ++ ){//反转后的操作同理
        int j = i;
        while( a[j].x == a[i].x && j <= N ) j ++;j --;
        for( int k = i; k <= j; k ++ ) t.mdf( 1, 1, N, a[k].id, 1 );
        for( int k = i; k <= j; k ++ ){
            node L = t.qry( 1, 1, N, 1, a[k].id ), R = t.qry( 1, 1, N, a[k].id, N );
            ans[a[k].id] = max( ans[a[k].id], L.rs + R.ls - 1 );
        }
        i = j;
    }
    for( int i = 1; i <= N; i ++ )
        cout << ans[i] / 2 << " ";
    return 0;
}