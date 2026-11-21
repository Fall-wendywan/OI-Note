#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN = 5e5 + 5;
const int MOD = 998244353;
const int base = 249;
int N, M;
int a[MAXN], poww[MAXN], root[MAXN], b[MAXN];
void init(){//预处理哈希+编号
    poww[0] = 1;
    for( int i = 1; i < MAXN; i ++ )
        poww[i] = ( poww[i - 1] * base ) % MOD;
    for( int i = 1; i <= M; i ++ )
        b[i] = i;
}

struct Prestree{
    int ls, rs, x, hsh;//记录左右儿子编号 序列的值 哈希值
}tr[MAXN * 40];

int tot = 0;
void upd( int p ){
    tr[p].hsh = ( tr[tr[p].ls].hsh + tr[tr[p].rs].hsh ) % MOD;
}//我们这里哈希能直接加主要是因为值与区间权重无关

void build( int &p, int l, int r ){
    p = ++ tot;
    if( l == r ){
        tr[p].x = a[l];
        tr[p].hsh = ( a[l] * poww[N - l] ) % MOD;//赋值当前哈希位置
        return;
    }
    int mid = ( l + r ) >> 1;
    build( tr[p].ls, l, mid );
    build( tr[p].rs, mid + 1, r );
    upd( p );
    tr[p].x = 0;//只有到叶子才有值
}
//在pre的基础上将pos改为val，计入p中
void mdf( int & p, int pre, int l, int r, int pos, int x ){
    p = ++ tot;
    tr[p] = tr[pre];
    if( l == r ){
        tr[p].x = x;
        tr[p].hsh = ( x * poww[N - l] ) % MOD;
        return;
    }

    int mid = ( l + r ) >> 1;
    if( pos <= mid )
        mdf( tr[p].ls, tr[pre].ls, l, mid, pos, x );
    else 
        mdf( tr[p].rs, tr[pre].rs, mid + 1, r, pos, x );
    upd( p );
}

//比较两个序列的字典序（其根为 rt1 rt2）
//当返回0为相同，1为小于（顺序）关系，-1为大于（逆序）关系
int query( int rt1, int rt2, int l, int r ){
    if( l == r ){
        if( tr[rt1].x == tr[rt2].x ) return 0;
        else return ( tr[rt1].x < tr[rt2].x ? 1 : -1 );
    }
    int mid = ( l + r ) >> 1;
    //这里竟然有二分？？？
    //就是说，这两个序列的被劈开了左右两部分
    //其中，由于左边字典序更高一些，就先查左边，利用hash快速判断是否相同
    //否则跑到右边去找不同
    //好巧妙啊
    if( tr[tr[rt1].ls].hsh != tr[tr[rt2].ls].hsh )
        return query( tr[rt1].ls, tr[rt2].ls, l, mid );
    else
        return query( tr[rt1].rs, tr[rt2].rs, mid + 1, r );
}

bool cmp( int u, int v ){
    int now = query( root[u], root[v], 1, N );
    return ( !now ? u < v : now == 1 );//sort的判断
}

signed main(){
    // freopen( "sort.in", "r", stdin );
    // freopen( "sort.out", "w", stdout );
    cin >> N >> M;
    for( int i = 1; i <= N; i ++ ){
        cin >> a[i];
    }
	init(); 
    build( root[1], 1, N );//初始化建树
    //为什么：因为此处初始数组不是0
    //而为什么像第k小数这种题不用建树 -> 因为那是每一次都插入，初始其实还是0
    
    for( int i = 2; i <= M; i ++ ){
        int x, y;
        cin >> x >> y;
        mdf( root[i], root[i - 1], 1, N, x, y );//每次插入新版本
    }
    sort( b + 1, b + M + 1, cmp );//进行排序
    for( int i = 1; i <= M; i ++ ){
        cout << b[i] << " ";//输出
    }
    return 0;
}
