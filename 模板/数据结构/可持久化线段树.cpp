#include<bits/stdc++.h>

using namespace std;
const int MAXN = 1e5 + 5;
int N, M;
int len, tot, a[MAXN], b[MAXN], root[MAXN];

struct Segtree{
    int ls, rs, num;//左右儿子下标 数的数量
}tr[MAXN * 23];

void build( int & p, int l, int r ){
    p = ++ tot;
    if( l == r ) return ;
    int mid = ( l + r ) / 2;
    build( tr[p].ls, l, mid );
    build( tr[p].rs, mid + 1, r );
    tr[p].num = 0;
    return;
}
void upd( int & p, int prt, int l, int r, int val ){
    p = ++ tot;
    tr[p].ls = tr[prt].ls;
    tr[p].rs = tr[prt].rs;
    tr[p].num = tr[prt].num + 1;
    if( l == r ) return;
    int mid = ( l + r ) / 2;
    if( val <= mid ) upd( tr[p].ls, tr[prt].ls, l, mid, val );
    else upd( tr[p].rs, tr[prt].rs, mid + 1, r, val );
    return;
}

int query( int x, int y, int l, int r, int k ){
    if( l == r ) return l;
    int sum = tr[tr[y].ls].num - tr[tr[x].ls].num;
    int mid = ( l + r ) / 2;
    if( k <= sum ) return query( tr[x].ls, tr[y].ls, l, mid, k );
    else return query( tr[x].rs, tr[y].rs, mid + 1, r, k - sum );
}
int main(){
    cin >> N >> M;
    for( int i = 1; i <= N; i ++ ) cin >> a[i], b[i] = a[i];

    sort( a + 1, a + N + 1 );
    len = unique( a + 1, a + N + 1 ) - ( a + 1 );
    for( int i = 1; i <= N; i ++ ){
        b[i] = lower_bound( a + 1, a + len + 1, b[i] ) - a;
    }
    build( root[0], 1, len );
    for( int i = 1; i <= N; i ++ ){
        upd( root[i], root[i - 1], 1, len, b[i] );
    }
    while( M -- ){
        int l, r, k;
        cin >> l >> r >> k;
        cout << a[query( root[l - 1], root[r], 1, len, k )] << endl;
    }
    return 0;
}