#include<bits/stdc++.h>
//参考557.cpp
//拓扑排序通常用来“排序”具有依赖关系的任务。
//任意两个任务要么具有确定的先后关系，要么是没有关系，绝对不存在互相矛盾的关系（即环路）
const int MAXN = 1e5;
using namespace std;
int N, M;
struct star{
    int nxt, to;
}edge[MAXN * 2];
int head[MAXN], cnt = 0;
void add( int u, int v ){
    edge[++ cnt].nxt = head[u];
    edge[cnt].to = v;
    head[u] = cnt;
}
int in[MAXN];//记录入度
int seq[MAXN];//存拓扑序
bool tupo(){
    priority_queue<int, vector<int>, greater<int>> q;//应该是按照从大到小
    for( int i = 1; i <= N; i++ ){
        if( ! in[i] ) q.push( i );//如果没有入度
    }
    int tot = 0;
    while( !q.empty() ){
        int top = q.top();
        seq[++ tot] = top;
        q.pop();
        for( int i = head[top]; i; i = edge[i].nxt ){
            int to = edge[i].to;
            in[to] --;
            if( !in[to] ) q.push( to );
        }
    }
    return tot == N;
}

int main(){
    cin >> N >> M;
    for( int i = 1; i <= M; i ++ ){
        int a, b;
        cin >> a >> b;
        add( a, b );
        in[b] ++;
    }
    if( tupo() ){
        for( int i = 1; i <= N; i ++ ) cout << seq[i] << endl;
    }
    else cout << "Error!";
    return 0;
}