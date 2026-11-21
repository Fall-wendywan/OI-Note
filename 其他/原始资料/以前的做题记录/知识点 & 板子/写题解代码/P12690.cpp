#include<bits/stdc++.h>
using namespace std;
int ans, cnt, tot;
string str;
int main(){
    cin >> str;
    for( int i = 0; i < str.size(); i ++ ){//正着扫
        if( str[i] == 'A' ) cnt ++;//统计前面有多少个待匹配的a
        if( str[i] == 'B' && cnt ) cnt --, ans ++;//有b可以用于匹配
        if( str[i] == 'B' ) tot ++;//统计b的个数 -> 最后判断个数是否够
    }
    cnt = 0;
    for( int i = str.size() - 1; i >= 0; i -- ){//反着扫
        if( str[i] == 'C' ) cnt ++;//同理
        if( str[i] == 'B' && cnt ) cnt --, ans ++;
    }

    cout << min( ans, tot );//取min防止b的个数不够
    return 0;
}