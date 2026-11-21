#include<bits/stdc++.h>
#define akioi return 0
// #define int long long
using namespace std;

const int maxx = 200000;
struct segtreex{
    int ls, rs;
    long long sum;//处理前缀和
} tr[2][4200001];//开两棵，一棵维护x轴，一个y轴
struct node{
    int x, y, z;
} q1[200001], q2[200001];//将盒子离线下来
int n, Q, lst1, lst2, cnt[2], frx[200001], fry[200001];
//下面时板子，不加赘述
void pushup(int u, int tp){
    tr[tp][u].sum = tr[tp][tr[tp][u].ls].sum + tr[tp][tr[tp][u].rs].sum;
}
void build(int u, int l, int r){
    if (l == r) return;
    else{
        int mid = (l + r) / 2;
        tr[0][u].ls = ++cnt[0], tr[1][u].ls = ++cnt[1];
        build(tr[0][u].ls, l, mid);
        tr[0][u].rs = ++cnt[0], tr[1][u].rs = ++cnt[1];
        build(tr[0][u].rs, mid + 1, r);
    }
}
void modify(int u, int lst, int pl, int z, int tp, int ll, int rr){
    if (ll == rr)
        tr[tp][u].sum = tr[tp][lst].sum + z;
    else{
        int mid = (ll + rr) / 2;
        if (pl <= mid){
            if (tr[tp][u].ls == 0)
                tr[tp][u].ls = ++cnt[tp];
            tr[tp][u].rs = tr[tp][lst].rs;
            //			cout<<"U:"<<u<<" LST:"<<lst<<" "<<tr[tp][u].ls<<" "<<tr[tp][u].rs<<" "<<"\n";
            modify(tr[tp][u].ls, tr[tp][lst].ls, pl, z, tp, ll, mid);
        }
        else{
            if (tr[tp][u].rs == 0)
                tr[tp][u].rs = ++cnt[tp];
            tr[tp][u].ls = tr[tp][lst].ls;
            modify(tr[tp][u].rs, tr[tp][lst].rs, pl, z, tp, mid + 1, rr);
        }
        pushup(u, tp);
    }
}
long long query(int u, int lst, int l, int r, int tp, int ll, int rr){
    long long sum = 0;
    if (ll >= l && rr <= r){
        return tr[tp][u].sum - tr[tp][lst].sum;
    }
    else{
        int mid = (ll + rr) / 2;
        if (l <= mid){
            sum += query(tr[tp][u].ls, tr[tp][lst].ls, l, r, tp, ll, mid);
        }
        if (r > mid){
            sum += query(tr[tp][u].rs, tr[tp][lst].rs, l, r, tp, mid + 1, rr);
        }
    }
    return sum;
}
bool cmp1(node x, node y){ return x.x < y.x; }
bool cmp2(node x, node y){ return x.y < y.y; }

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    //	freopen("get.in","r",stdin);
    //	freopen("get.out","w",stdout);
    //	freopen("data.in","r",stdin);
    cin >> n >> Q;
    for (int i = 1; i <= n; i++){
        int x, y, w;
        cin >> x >> y >> w;
        q1[i] = {x, y, w}, q2[i] = {x, y, w};
    }
    sort(q1 + 1, q1 + n + 1, cmp1);
    sort(q2 + 1, q2 + n + 1, cmp2);//离线排序
    for (int i = 1; i <= maxx; i++){
        frx[i] = frx[i - 1];
        fry[i] = fry[i - 1];//建树
        while (lst1 < n && q1[lst1 + 1].x == i){
            node t = q1[lst1 + 1];
            lst1++;
            int lst = frx[i];
            frx[i] = ++cnt[0];
            //			cout<<i<<"OK\n";
            modify(frx[i], lst, t.y, t.z, 0, 1, maxx);
        }
        while (lst2 < n && q2[lst2 + 1].y == i){
            node t = q2[lst2 + 1];
            lst2++;
            int lst = fry[i];
            fry[i] = ++cnt[1];
            modify(fry[i], lst, t.x, t.z, 1, 1, maxx);
        }//分别插入当前位置
    }
    int nx = 1, ny = 1;
    long long ans = 0;
    for (int i = 1; i <= Q; i++){//模拟+查询
        int d, v;
        cin >> d >> v;
        int onx = nx, ony = ny;
        if (d == 0) nx += v;
        else if (d == 1) ny += v;
        else if (d == 2) nx -= v;
        else ny -= v;
        if (d == 0)
            ans += query(fry[ny], fry[ny - 1], onx + 1, nx, 1, 1, maxx);
        else if (d == 2)
            ans += query(fry[ny], fry[ny - 1], nx, onx - 1, 1, 1, maxx);
        else if (d == 1)
            ans += query(frx[nx], frx[nx - 1], ony + 1, ny, 0, 1, maxx);
        else
            ans += query(frx[nx], frx[nx - 1], ny, ony - 1, 0, 1, maxx);
    }
    cout << ans;
    akioi;
}