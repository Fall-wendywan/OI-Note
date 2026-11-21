#include<bits/stdc++.h>
/*
https://www.luogu.com.cn/problem/P10959
https://vjudge.net/contest/836529#problem/G
数位dp。
状态定义时存 从高位到低位填到多少位 现在的数位和 填好的数值 对mod取模（我们枚举的最后的数字和）
然后记忆化搜索，用dp记录答案。
对于这个题目，就是求 1 -> l - 1 和 1 -> r 的（前缀）答案，就可以了。
*/
using namespace std;
int L, R;
int a[11], dp[15][95][95][95];
//从高位到低位填到多少位 现在的数位和
//填好的数值，对mod取模 当前是否顶到上界（0 -> 9最大能填什么）
int dfs( int dep, int sum, int num, int mod, bool lim ){
    // cout << dep << " " << sum << " " << mod << " " << num << endl;
    if( dep == 0 ){
        // cerr << sum << " " << mod << " " << num << endl;
        return ( sum == mod && num == 0 );}
    if( !lim && dp[dep][sum][num][mod] != -1 ){
        return dp[dep][sum][num][mod];
    }
    int res = 0;
    for( int i = 0; i <= ( lim ? a[dep] : 9); i ++ ){
        if( i + sum <= mod ){
            res += dfs( dep - 1, sum + i, ( num * 10 + i ) % mod, mod, lim && ( i == a[dep] ) );
            // cout << res << endl;
        }
    }
    if( !lim )
        dp[dep][sum][num][mod] = res;
    return res;
}

//算 1 -> n 的月之数个数
int slove( int n ){
    // cout << n << " ";
    if( n == 0 ) return 0;
    int cnt = 0;
    while( n ){
        a[++ cnt] = n % 10;
        n /= 10;
    }
    // cerr << cnt << endl;
    int res = 0;
    for( int i = 1; i <= 9 * cnt; i ++ ){//枚举到最大数位和
        res += dfs( cnt, 0, 0, i, 1 );
        // cerr << res << " ";
    }
    return res;
}

int main(){
    memset( dp, -1, sizeof dp );
    while( cin >> L >> R ){
        cout << slove( R ) - slove( L - 1 ) << endl;
    }
    return 0;
}