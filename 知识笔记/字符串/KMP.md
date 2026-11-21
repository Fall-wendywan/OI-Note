# KMP 算法

> 合并自详细笔记与洛谷模板稿；两种代码实现均保留。

## 详细笔记

## 1.内容

可以参考这个[KMP算法详解（超级详细）-CSDN博客](https://blog.csdn.net/qq_45806146/article/details/104911112?spm=1001.2101.3001.6650.14&utm_medium=distribute.pc_relevant.none-task-blog-2%7Edefault%7Ebaidujs_baidulandingword%7ECtr-14-104911112-blog-128003067.235%5Ev43%5Epc_blog_bottom_relevance_base6&depth_1-utm_source=distribute.pc_relevant.none-task-blog-2%7Edefault%7Ebaidujs_baidulandingword%7ECtr-14-104911112-blog-128003067.235%5Ev43%5Epc_blog_bottom_relevance_base6&utm_relevant_index=22)]

先放个图

![kmp](https://i-blog.csdnimg.cn/blog_migrate/03bd2136b181e20817eee3ee6357812d.gif)



暴力：一个一个位置扫，每次比对整个字符串

我理解的kmp：加了优化->next数组 使得每次不用重新扫

此时复杂度：$ O ( N + M )$

> 为什么？
> 
> 考虑代码中while循环总共加起来只会循环约 $M \to 2 \times M$  次（尽管很不严谨）
> 
> 我们可以大致认为是这样的

这样我们先要处理 $next$ 数组，再去做 $kmp$ 的 $solve$ 操作。

$next$  的定义：$ 1 \to i - 1$ 中前后缀的数量。

<mark><u>***注意***</u> </mark>：在此处，我们的代码中是 $1  \to i$ 的！ 不信自己理解看。

因为从0开始太(bu)过(hui)繁(shi)琐(xian)，所以我们会在后面的操作中进行$ +1 $之类的操作。

但是在诸多题解中皆为0开始的，包括对$next$数组的解释。

因为麻(bu)烦(hui)，我们不多赘述。

$以上是大致的内容$

## 2.$Code$

```kmp代码
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
```

  下面是没有注释的可食用板子

```kmp板子
#include<bits/stdc++.h>

using namespace std;
const int MAXN = 1e6 + 10;
int nxt[MAXN];
string s, p;//p是模式串_pattern s是文本串
int N, M;
void kmp(){
    N = p.size();
    p = ' ' + p;
    nxt[1] = 0;
    for( int i = 2, j = 0; i <= N; i ++ ){
        while( j && p[i] != p[j + 1] ) j = nxt[j];
        if( p[i] == p[j + 1] ) j ++;
        nxt[i] = j;
    }
}

void solve(){
    M = s.size();
    s = ' ' + s;
    int cnt = 0;
    for( int i = 1, j = 0; i <= M; i ++ ){
        while( j && s[i] != p[j + 1] ) j = nxt[j];
        if( s[i] == p[j + 1] ) j ++;
        if( j >= N ){
            cnt ++;
            j = nxt[j];
        }
    }
    cout << cnt << endl;
}
int main(){
    cin >> p >> s;
    kmp();
    solve();
    return 0;
}
```

## 3.练习(欠的)与链接

这里是对于另一种——经典版的板子 [KMP 学习笔记 - 洛谷专栏](https://www.luogu.com.cn/article/25lwjx5p)

[P3375 【模板】KMP - 洛谷](https://www.luogu.com.cn/problem/P3375)

这好像是二分但是不能证？ [SZA-Template - 题目详情 - Genisis Online Judge](http://goj.wiki/d/junior/p/P3771)

## 4.最后

这里是对next起始坐标的一点解释

### 两种实现的本质联系

| 特性          | 哨兵版（原代码）   | 经典版（无哨兵）    |
| ----------- | ---------- | ----------- |
| **起始索引**    | 1          | 0           |
| **next[0]** | 未使用        | -1（特殊标记）    |
| **子串范围**    | p[1…i]     | p[0…i-1]    |
| **初始化**     | `nxt[1]=0` | `nxt[0]=-1` |
| **循环变量**    | i=2 to N   | i=0 to n-1  |
| **核心逻辑**    | 相同         | 相同          |

> (来自ai)这就是花了大量时间解释的next数组

## 洛谷版模板补充

KMP 算法

**注意，`fail` 数组要开二倍空间！**

查找子串：

```cpp
const int N=1e5+5;
int fail[N];
void KMP(string s1,string s2){
	string s=" "+s1+"#"+s2;
	int n=s.size()-1;
	for(int i=2,j=0;i<=n;i++){
		while(j!=0&&s[j+1]!=s[i]) j=fail[j];
		fail[i]=(j+=s[j+1]==s[i]);
	}
//	for(int i=s1.size()+1;i<=n;i++)
//		if(fail[i]==s1.size())
//  			printf("%d\n",i-s1.size()-s1.size());
}
```

对单个串 KMP：

```cpp
const int N=1e6+5;
int fail[N];
void KMP(string s){
	int n=s.size();
	s=" "+s;
	for(int i=2,j=0;i<=n;i++){
		while(j!=0&&s[i]!=s[j+1]) j=fail[j];
		fail[i]=(j+=s[i]==s[j+1]);
	}
}
```
