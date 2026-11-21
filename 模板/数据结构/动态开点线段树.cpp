#include<bits/stdc++.h>
#define int long long
/*
link:
https://www.luogu.com.cn/problem/CF915E
https://codeforces.com/problemset/problem/915/E
-----------------------------------------------
动态开点板子，带懒标记。
与常规线段树的区别仅限于使用tot记录当前点编号，即点编号没有规律
遇到没开的点就开一下（在下传和修改的时候），建树没了。
其他和普通线段树差不多，注意空间大小。
*/
using namespace std;
const int MAXN = 18000000;
int N, Q;
int tot, root;
struct tree{
    int ls, rs, sum, lzyt;
    //懒标记：-1表示没有，0、1均表示区间被整体赋值为0、1，分别为工作日和非工作日
}tr[MAXN];

// void build( int & p, int l, int r ){
// 动态开点中一般用不到，因为无法确定当前在原数组中编号？
//     p = ++ tot;
//     if( l == r ){
//         return;
//     }
//     int mid = ( l + r ) >> 1;
//     build( tr[p].ls, l, mid );
//     build( tr[p].rs, mid + 1, r );
// }

void down( int p, int l, int r ){
    if( tr[p].lzyt == -1 ) return;
    if( !tr[p].ls ){
        tr[tr[p].ls = ++ tot] = { 0, 0, 0, -1 };
    }
    if( !tr[p].rs ){
        tr[tr[p].rs = ++ tot] = { 0, 0, 0, -1 };
    }
    int mid = ( l + r ) >> 1;
    tr[tr[p].ls].sum = tr[p].lzyt * ( mid - l + 1 );
    tr[tr[p].ls].lzyt = tr[p].lzyt;
    tr[tr[p].rs].sum = tr[p].lzyt * ( r - mid );//注意右区间范围,[mid + 1, r ]
    tr[tr[p].rs].lzyt = tr[p].lzyt;
    tr[p].lzyt = -1;
}

void upd( int p ){ tr[p].sum = tr[tr[p].ls].sum + tr[tr[p].rs].sum; }

void mdf( int & p, int l, int r, int x, int y, int val ){//将区间[l, r]赋值为val
    if( ! p ) tr[p = ++ tot] = { 0, 0, r - l + 1, -1 };//默认都是
    if( x <= l && r <= y ){
        if( val == 2 ) val = 0;
        tr[p].lzyt = val, tr[p].sum = val * ( r - l + 1 );
        return;
    }
    down( p, l, r );
    int mid = ( l + r ) >> 1;
    if( x <= mid ) mdf( tr[p].ls, l, mid, x, y, val );
    if( y > mid ) mdf( tr[p].rs, mid + 1, r, x, y, val );
    upd( p );
}

signed main(){
    cin >> N >> Q;
    while( Q -- ){
        int l, r, k;
        cin >> l >> r >> k;
        mdf( root, 1, N, l, r, k );
        cout << abs( N - tr[root].sum ) << endl;
    }

    return 0;
}