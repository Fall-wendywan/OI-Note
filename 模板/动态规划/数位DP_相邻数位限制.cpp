#include<bits/stdc++.h>
//加强版还是太强了
//数位dp板子题
//luogu->https://www.luogu.com.cn/problem/P13085
//有双倍
//vjudge->https://vjudge.net/contest/748290#problem/B
#define int long long
using namespace std;
int a, b;
int dp[25][20];//dp[i][j]表示第i位填j的方案数
/*
从 1000 数到 9999，除了千位，后面三位都是从 000 到 999 的，
所以我们可以把这些过程合并起来，并将所产生的计数答案也都存在一个的数组里，
然后根据题目具体要求设置状态，用递推或 DP 的方式进行状态转移。
*/
int slove( int n ){//处理1->n位的答案统计
//  考虑从高位开始枚举，考虑每一位可以填哪一些数，利用上文求出的数组求出答案。
    int len = 0;
    int num[25] = { 0 };
    while( n ){//将n拆解
        num[++ len] = n % 10;
        n /= 10;
    }

    int ans = 0;
    //1.单独处理前导0->不满len位的数字的处理
    //所有位数小于len的数字必然小于原数x（例如x=1000时，三位数 123必定小于x）。此时直接累加dp[i][j]（表示i位数且最高位为j的windy数总数）。
    for( int i = 1; i < len; i ++ ){
        for( int j = 1; j <= 9; j ++ ){//从1开始避免前导零
            ans += dp[i][j];
        }
    }
    //2.位数等于 len，但最高位小于 num[len] 的 windy 数
    //位数等于len但最高位小于x最高位的数字必然小于x
    for( int i = 1; i < num[len]; i ++ ){//同理最高位不能是0
        ans += dp[len][i];
    }
    //3.处理位数等于len且前缀与x部分相同的数字
    for( int i = len - 1; i >= 1; i -- ){//逐渐枚举低位
        for( int j = 0; j < num[i]; j ++ ){//枚举去除相同前缀的剩余部分->必须小于上线的这一位
            if( abs( j - num[i + 1] ) >= 2 ){//还得满足windy数的限制
                ans += dp[i][j];
            }
        }
        if( abs( num[i] - num[i + 1] ) < 2 ) break;//如果本身这个数字就不满足->那我们也无法使用这个前缀了
    }
    return ans;
}
signed main(){
    cin >> a >> b;
    for( int i = 0; i <= 9; i ++ ){
        dp[1][i] = 1;
    }
    for( int i = 2; i <= 20; i ++ ){//从2开始防止1被覆盖
        for( int j = 0; j <= 9; j ++ ){
            for( int k = 0; k <= 9; k ++ ){
                if( abs( k - j ) >= 2 ) dp[i][j] += dp[i - 1][k];
            }
        }
    }
    // cout <<slove( b ) << " " << slove( a - 1 ) << endl;
    cout << slove( b + 1 ) - slove( a );//我一开始注意到为什么不用加上本身，后来发现我们计算的时候其实是可以不加上本身的
    //↑((r+1)-1)-(l-1)就包含了整个区间
    return 0;
}