#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

const int INF = 9999999; // 无穷大
const int MAX_PNUM = 56; // 最大人数

int N;                             // 男、女运动员各自的人数（共计：2N）
int P[MAX_PNUM + 2][MAX_PNUM + 2]; // 男运动员优势矩阵（男，女）
int Q[MAX_PNUM + 2][MAX_PNUM + 2]; // 女运动员优势矩阵（女，男）
int bestc = 0;                     // 最优值
int bestx[MAX_PNUM + 2];           // 最优解（第 i位男运动员与第 a位女运动员配对）

typedef struct Node
{
    int level;       // 第 level号男运动员（即树的层号表示第几个男运动员）
    int c;           // 竞赛优势
    int x[MAX_PNUM]; // 安排方式
    friend bool operator<(const Node &a, const Node &b)
    {
        return (a.c < b.c);
    }
} Node;

priority_queue<Node, vector<Node>, less<Node>> q; // 建立大顶堆优先队列

int main()
{
    scanf("%d", &N); // 输入人数
    for (int i = 1; i <= N; i++)
    {
        for (int j = 1; j <= N; j++)
        {
            scanf("%d", &(P[i][j]));
        }
    } // 男运动员优势数据
    for (int i = 1; i <= N; i++)
    {
        for (int j = 1; j <= N; j++)
        {
            scanf("%d", &(Q[i][j]));
        }
    } // 女运动员优势数据

    Node E; // 起始节点
    E.c = 0, E.level = 1;
    for (int i = 1; i <= N; i++)
    {
        E.x[i] = i;
    } // 初始化单位排列

    //产生当前节点的扩展节点
    while (E.level <= N + 1)
    {
        if (E.level == N + 1)           // 叶子结点
        {
            if (E.c > bestc)
            {
                bestc = E.c;
                for (int i = 1; i <= N; i++)
                {
                    bestx[i] = E.x[i];
                }
            }
        }
        else
        {
            for (int i = E.level; i <= N; i++)          // 排列树拓展儿子
            {
                std::swap(E.x[E.level], E.x[i]);
                Node tt;
                tt.c = E.c + P[E.level][E.x[E.level]]* Q[E.x[E.level]][E.level];
                tt.level = E.level + 1;         // 下一层
                for (int j = 1; j <= N; j++)
                {
                    tt.x[j] = E.x[j];
                }
                q.push(tt);
                std::swap(E.x[E.level], E.x[i]);
            }
        }
        if (q.empty()) break;
        E = q.top();
        q.pop();
    }

    printf("The best value is: %d.\n", bestc);
    printf("The best solution is: \"");
    for (int i = 1; i <= N; i++)
    {
        printf("%2d", bestx[i]);
    }
    printf(" \".\n");

    return 0;
}

/*
3
10 2 3
2 3 4
3 4 5
2 2 2
3 5 3
4 5 1
*/
