#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

const int INF = 9999999; // 无穷大
const int MAX_UNUM = 56; // 最大部件数
const int MAX_PNUM = 56; // 最大供应商数目

int n; // 部件总个数
int m; // 供应商总数
int d; // 限定价格
int bestw = INF;
int bestx[MAX_UNUM + 2];
int cost[MAX_UNUM + 2][MAX_PNUM + 2], weight[MAX_UNUM + 2][MAX_PNUM + 2];

typedef struct Node
{
    int weight, cost, level, id;
    int x[MAX_UNUM];
    Node(int weight, int cost, int level, int id) : weight(weight), cost(cost), level(level), id(id) {}
    friend bool operator>(const Node &a, const Node &b) // 重载 greater运算符
    {
        if (a.weight != b.weight)
            return (a.weight > b.weight);
        else if (a.level != b.level)
            return (a.level > b.level);
        else
            return (a.id > b.id);
    }
} Node;

priority_queue<Node, vector<Node>, greater<Node>> q; // 建立小根堆

int main()
{
    scanf("%d%d%d", &n, &m, &d);
    for (int i = 1; i <= n; i++)
    { // cost
        for (int j = 1; j <= m; j++)
        {
            scanf("%d", &(cost[i][j]));
        }
    }
    for (int i = 1; i <= n; i++)
    { // weight
        for (int j = 1; j <= m; j++)
        {
            scanf("%d", &(weight[i][j]));
        }
    }

    for (int i = 1; i <= m; i++)
    { // 将第 1层边对应的节点入优先队列
        Node temp = Node(weight[1][i], cost[1][i], 1, i);
        if (temp.cost > d) // 若价格超过限定价格，则剪枝 Constraint
            continue;      // 不入队
        else
        {
            temp.x[1] = i; // 选择供应商
            q.push(temp);  // 入队
        }
    }

    while (!q.empty())
    {
        Node temp = q.top();
        q.pop();
        if (temp.level < n)
        {
            for (int i = 1; i <= m; i++)
            {
                Node tt = Node(temp.weight + weight[temp.level + 1][i], temp.cost + cost[temp.level + 1][i], temp.level + 1, i);
                if (tt.level == n)
                {                                            // 此扩展节点是叶子节点
                    if (tt.weight > bestw || tt.cost > d)    // 剪枝（重量and价格）
                        continue;
                    else if (tt.weight < bestw)
                    {
                        bestw = tt.weight; //最小重量更新
                        for (int j = 1; j <= n - 1; j++)
                        { //最优路径更新
                            bestx[j] = temp.x[j];
                        }
                        bestx[n] = i;
                    }
                }
                else if (tt.level < n)  // 扩展结点不是叶子节点
                {
                    if (tt.cost > d)
                    { //剪枝（价格）
                        continue;
                    }
                    else
                    {
                        for (int j = 1; j <= temp.level; j++) //历史路径
                        {
                            tt.x[j] = temp.x[j];
                        }
                        tt.x[temp.level+1] = i; //路径更新
                        q.push(tt);
                    }
                }
            }
        }
    }

    printf("The best value is: %d.\n", bestw);
    printf("The best solution is: \"");
    for (int i = 1; i <= n; i++)
    {
        printf("%2d", bestx[i]);
    }
    printf(" \".\n");

    return 0;
}
