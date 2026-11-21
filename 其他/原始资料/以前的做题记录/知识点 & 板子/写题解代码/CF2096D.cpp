#include<bits/stdc++.h>
//https://www.luogu.com.cn/problem/CF2096D
//https://codeforces.com/problemset/problem/2096/D
using namespace std;
const int MAXN = 2e5 + 5;
int T, N;
int x, y;
set<int> col, dia;//表示行与斜线
int main(){
    cin >> T;
while( T -- ){
    col.clear(), dia.clear();
    cin >> N;
    for( int i = 1; i <= N; i ++ ){
        cin >> x >> y;
        if( col.find( x ) != col.end() ) col.erase( x );
        else col.insert( x );
        if( dia.find( x + y ) != dia.end() ) dia.erase( x + y );
        else dia.insert( x + y );
        //如果已经有一次了那么异或操作之后就是0
        //在这里map是直接去除掉这个元素表示其异或值为0
    }
    cout << *col.begin() << " " << *dia.begin() - *col.begin() << endl;//输出交点
}
    return 0;
}