#include<bits/stdc++.h>
#define itn int
//模板 字典树  注意初始化卡时间空间哈哈（首字典树）
//goj->http://goj.wiki/d/junior/p/703
//luogu->https://www.luogu.com.cn/problem/P8306
using namespace std;
const int MAXN = 3e6 + 5;
int T;
int N, q, cnt;
int tr[MAXN][81], totol[MAXN];
    //点u的81个字母节点
void init(){//初始化
    for( int i = 0; i < cnt; i ++ )
        for( itn j = 0; j < 81; j ++ )
            tr[i][j] = 0;
    for( int i = 0; i <= cnt; i ++ ) totol[i] = 0;
    cnt = 0;
}

void insert( string s ){//更新
    int root = 0;
    for( int i = 0; i < s.size(); i ++ ){
        int u = s[i] - '0';
        if( tr[root][u] == 0 ){
            tr[root][u] = ++ cnt;
        }
        root = tr[root][u];
    }
    totol[root] ++;
}

int Query( string s ){//查询
    int root = 0;
    for( int i = 0; i < s.size(); i ++ ){
        int u = s[i] - '0';
        if( tr[root][u] == 0 ){
            return 0;
        }
        root = tr[root][u];
    }
    return totol[root];
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin >> T;
    string str;
    while( T -- ){
        init();
        cin >> N >> q;
        while( N -- ){
            cin >> str;
            insert( str );
        }
        while( q -- ){
            cin >> str;
            cout << Query( str ) << endl;
        }
    }

    return 0;
}