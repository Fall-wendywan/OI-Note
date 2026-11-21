#include<bits/stdc++.h>
#define IOS ios::sync_with_stdio( 0 ), cin.tie( 0 ), cout.tie( 0 ) 
using namespace std;
const int MAXN = 1e5 + 5;
int N;
int t[MAXN], ans[MAXN];
//t[i]表示排序后第i只兔子的最终位置
struct node{
    int id, p, to;//p是初始位置，to是排序过后兔子的目标的下标
}a[MAXN];
bool cmp( node a, node b ){ return a.p < b.p; }
int main(){
    IOS;
    cin >> N;
    for( int i = 1; i <= N; i ++ ){
        cin >> a[i].p;
        a[i].id = i;
    }
    sort( a + 1, a + N + 1, cmp );
    for( int i = 1; i <= N; i ++ ){
        if( i == 1 ) a[i].to = 2;
        else if( i == N ) a[i].to = N - 1;//最左或者最右只能选这个
        else {
            if( a[i].p - a[i - 1].p <= a[i + 1].p - a[i].p ) a[i].to = i - 1;
            else a[i].to = i + 1;//预处理目标
        }
    }
    
    for( int i = 1; i < N; i ++ ){
        if( a[i].to == i + 1 && a[i + 1].to == i ){//找到双向奔赴的兔子
            int now = ( a[i].p + a[i + 1].p ) / 2;//找中间位置
            if( !t[i] ) t[i] = now;
            if( !t[i + 1] ) t[i + 1] = now;

            for( int j = i - 1; j >= 1; j -- ){
                if( t[j] || a[j].to <= j ) break;//如果已经不满足方向了
                t[j] = now;
            }
            for( int j = i + 2; j <= N; j ++ ){
                if( t[j] || a[j].to >= j ) break;
                t[j] = now;
            }//便利答案
        }
    }
    for( int i = 1; i <= N; i ++ ) ans[a[i].id] = t[i];
    for( int i = 1; i <= N; i ++ ) cout << ans[i] << " ";
    
    return 0;
}