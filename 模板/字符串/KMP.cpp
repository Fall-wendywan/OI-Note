#include<bits/stdc++.h>
using namespace std;

const int MAXN = 1e6 + 10;//似乎看到某一篇题解说要开两倍？
int nxt[MAXN];// 存储KMP的next数组（前缀表）
//正式定义：对于模式串 p 的位置 i，next[i] 表示子串 p[0..i-1] 中最长相等真前缀和真后缀的长度
//但这里的真正定义：表示子串 p[1..i] 的最长公共真前缀和真后缀的长度（包含i）
string s, p;// s:文本串，p:模式串(_pattern)
int N, M;// N:模式串长度，M:文本串长度

// 构建next数组（核心预处理）
void kmp() {
    N = p.size();//获取模式串长度
    p = ' ' + p;//下标从1开始（就是因为这里才会有不同定义）
    nxt[1] = 0;// 初始化第一个字符的next值为0
    for ( int i = 2, j = 0; i <= N; i ++ ) {// i:当前主指针，对文本串 j:已匹配前缀尾指针 对模式串
        // 当匹配失败且j未退回起点时，利用next数组回退
        while (j && p[i] != p[j + 1]) j = nxt[j];
        // 当前字符匹配成功，j向后移动
        if (p[i] == p[j + 1]) j++;
        nxt[i] = j;  // 记录当前位置的最长公共前后缀长度
    }
}

// 模式匹配过程
void solve() {
    M = s.size();// 获取文本串长度
    s = ' ' + s;// 添加哨兵位（下标从1开始）
    int cnt = 0;// 统计模式串出现次数
    for (int i = 1, j = 0; i <= M; i++) {// i:文本串指针，j:模式串指针
        // 字符不匹配时，根据next数组回退模式串指针
        while (j && s[i] != p[j + 1]) j = nxt[j];
        // 字符匹配成功，模式串指针后移
        if (s[i] == p[j + 1]) j++;
        // 完整匹配到模式串
        if (j >= N) {
            cnt++;         // 匹配次数+1
            j = nxt[j];    // 避免重复匹配（跳过已匹配部分）
        }
    }
    cout << cnt << endl;   // 输出总匹配次数
}

int main() {
    cin >> p >> s;         // 输入模式串和文本串
    kmp();                 // 构建next数组
    solve();               // 执行模式匹配
    return 0;
}
