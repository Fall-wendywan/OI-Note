#include<bits/stdc++.h>
using namespace std;
const int MAXN = ( 1 << 21 );
int N;
int a[MAXN], tmp[MAXN], ans;
// 操作后数组 用于记录操作的数组
int main(){
    cin >> N;
    bool flag = 0;
    for( int i = 0; i < N; i ++ ){
        cin >> a[i];
        if( a[i] != 0 ) flag = true;//特判全为0
    }
    if( !flag ) return cout << 0, 0;
    flag = 0;
    for( int k = 20; k >= 0; k -- ){
        if( ( 1 << k ) > N ) continue;//判越界
        flag = 0;
        for( int i = 0; i < N; i ++ ){
            tmp[i] = a[i] ^ a[( i + ( 1 << k ) ) % N];//暴力转移
            if( tmp[i] != 0 ) flag = true;//判全0
        }
        if( flag ){
            for( int i = 0; i < N; i ++ ) a[i] = tmp[i];//如果不满足，就操作一下
            ans += ( 1 << k );//加上操作次数
        }
    }

    cout << ans + 1;//因为最后是找到最小的不满足的，所以+1再操作一次就是答案了
    return 0;
}