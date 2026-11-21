#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

const int MAXN = 1e5 + 5;  // 最大顶点数
const int MAXM = 2e5 + 5;  // 最大边数

// 链式前向星结构
struct Edge {
    int to;     // 边的终点
    int next;   // 下一条边的索引
} edges[MAXM];

int head[MAXN]; // 顶点表头指针
int edge_cnt;   // 边计数器
int in_degree[MAXN]; // 入度数组

// 初始化前向星
void init() {
    memset(head, -1, sizeof(head)); // 初始化为-1表示空指针
    edge_cnt = 0;
}

// 添加有向边
void add_edge(int u, int v) {
    edges[edge_cnt].to = v;
    edges[edge_cnt].next = head[u]; // 头插法
    head[u] = edge_cnt++;           // 更新头指针
}

// 拓扑排序函数
vector<int> topological_sort(int n) {
    vector<int> result;
    int q[MAXN], front = 0, rear = 0; // 数组模拟队列

    // 初始化入度
    memset(in_degree, 0, sizeof(in_degree));
    for (int u = 1; u <= n; ++u) {
        for (int i = head[u]; ~i; i = edges[i].next) {
            int v = edges[i].to;
            ++in_degree[v];
        }
    }

    // 将入度为0的顶点加入队列
    for (int u = 1; u <= n; ++u) {
        if (in_degree[u] == 0) {
            q[rear++] = u;
        }
    }

    // BFS处理
    while (front < rear) {
        int u = q[front++];
        result.push_back(u);

        // 遍历所有出边
        for (int i = head[u]; ~i; i = edges[i].next) {
            int v = edges[i].to;
            if (--in_degree[v] == 0) {
                q[rear++] = v;
            }
        }
    }

    // 检查是否有环
    if (result.size() != n) {
        return vector<int>(); // 返回空vector表示有环
    }
    return result;
}

int main() {
    init();
    
    /* 测试用例1：正常DAG */
    // 1 -> 2 -> 5
    //  ↘ 3 ↗ 4
    add_edge(1, 2);
    add_edge(1, 3);
    add_edge(2, 5);
    add_edge(3, 4);
    add_edge(4, 5);

    vector<int> res = topological_sort(5);
    if (res.empty()) {
        cout << "图中有环！" << endl;
    } else {
        cout << "拓扑排序结果：";
        for (int u : res) cout << u << " ";
        // 输出：1 2 3 4 5 或 1 3 4 2 5 等合法排序
    }

    /* 测试用例2：含环图 */
    // init();
    // add_edge(1, 2);
    // add_edge(2, 3);
    // add_edge(3, 1); // 形成环
    // res = topological_sort(3);
    // 输出：图中有环！
    
    return 0;
}
