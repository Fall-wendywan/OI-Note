#include<bits/stdc++.h>
#define int long long
#define IOS ios::sync_with_stdio(false);cin.tie(0);cout.tie(0)
using namespace std;
const int MAXN = 3e5 + 5;
int N, ans, c[MAXN * 2 + 3], pos, now;
signed main(){
    IOS;
    cin >> N;
    for( int i = 1; i <= N; i ++ ){
        cin >> c[i];
        c[i + N] = c[i], ans += c[i];//破换成链 + 统计有小房间的答案
        if( !pos ) pos = ( c[i] ? i : 0 );//寻找到第一块的开头（其实是防止一块跨头尾）
    }
    if( ans == 0 ) return cout << N / 2, 0;//特判 -> 一个环
    for( int i = pos + 1; i <= N + pos; i ++ ){
        if( c[i] ) ans += ( now + 1 ) / 2, now = 0;//如果到一块结束了
        else now ++;//继续累加块大小
    }
    cout << ans;
    return 0;
}
