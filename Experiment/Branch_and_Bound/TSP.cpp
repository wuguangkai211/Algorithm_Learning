#include <algorithm>
#include <cstdio>
#include <iostream>
#include <queue>
using namespace std;

const int INF = 99999999; // 无穷大
const int MAX_VNUM = 56;
const int NoEdge = INF; // 图 G的无边标志

// TSP 问题类型
class Traveling
{
public:
    int vertex_num;            // 图 G的顶点数
    int edge_num;              // 图 G的边数
    int a[MAX_VNUM+4][MAX_VNUM+4]; // 图 G的邻接矩阵
    int cc;                    // 当前费用
    int bestc;                 // 当前最小费用

public:
    // TSP 的分支限界式解决算法
    int Solve(int bestx[]);
};

// 优先队列小顶堆节点
typedef struct MinHeapNode
{
    int lcost; // 子树费用的下界
    int cc;    // 当前费用
    int rcost; // RestCost: x[s:vertex_num]中顶点最小出边费用和
    int s;     // 根节点到当前节点的路径为 x[1:s]
    int *x;    // 需要进一步搜索的顶点是 x[s+1:vertex_num]
    // 重载：Greater运算符
    friend bool operator>(const MinHeapNode &x, const MinHeapNode &y)
    {
        return (x.cc > y.cc);
    }
} MinHeapNode;

// TSP 的分支限界式解决算法
int Traveling::Solve(int bestx[])
{
    priority_queue< MinHeapNode, vector<MinHeapNode>, greater<MinHeapNode> > H; // 建立小顶堆

    // 求最小出边费用和，计算下界时用
    int *MinOut = new int[MAX_VNUM+4];     // MinOut[i] = 顶点 i的最小费用
    int MinSum = 0; // 最小出边费用和
    for (int i = 1; i <= vertex_num; i++)
    {
        int Min = INF;          // 寻找该节点的最小出边
        for (int j = 1; j <= vertex_num; j++)
        {
            if (a[i][j] < Min)
            {
                Min = a[i][j];
            }
        }
        if (Min == INF) // 该节点是一个孤立点，则问题无解（整个图中不存在连接所有顶点的一条回路）
        {
            return INF;         // 无解时的花费定义为无穷大
        }
        MinOut[i] = Min;                // 该点的最小出边费用为：Min
        MinSum += Min;              // 计入最小出边费用和
    }

    // 初始化
    MinHeapNode E;  // 待扩展结点，一开始是根节点
    E.x = new int[MAX_VNUM+2];
    for (int i = 1; i <= vertex_num; i++)           // 生成初始排列
    {
        E.x[i] = i;
    }
    E.s = 1;
    E.cc = 0;
    E.lcost = 0;
    E.rcost = MinSum;
    bestc = NoEdge;         // 尚无最优值

    // 搜索排列空间树
    while (E.s < vertex_num) // 当是叶结点出队时，代表算法应当结束
    {
        if (E.s == vertex_num - 1) // 当前扩展结点是叶结点的父节点
        {
            // 再加两条边构成回路，所构成的回路书否优于当前最优解
            if (a[E.x[vertex_num - 1]][E.x[vertex_num]] != NoEdge && a[E.x[vertex_num]][1] != NoEdge && (E.cc + a[E.x[vertex_num - 1]][E.x[vertex_num]] + a[E.x[vertex_num]][1] < bestc || bestc == NoEdge))
            {
                // 费用更小的回路
                bestc = E.cc + a[E.x[vertex_num - 1]][E.x[vertex_num]] + a[E.x[vertex_num]][1];
                E.cc = bestc;
                E.lcost = bestc;
                ++E.s;
                H.push(E);
            }
            else
            {
                delete[] E.x; // 舍弃扩展结点
            }
        }
        else
        {
            for (int i = E.s + 1; i <= vertex_num; i++)
            {
                if (a[E.x[E.s]][E.x[i]] != NoEdge)          // 可达
                {
                    int cc = E.cc + a[E.x[E.s]][E.x[i]]; // 可行儿子节点
                    int rcost = E.rcost - MinOut[E.x[E.s]];
                    int b = cc + rcost;               // 下界
                    if (b < bestc || bestc == NoEdge) // 小于，说明子树可能含有最优解，结点插入最小堆
                    {
                        std::swap(E.x[E.s + 1], E.x[i]);        // 交换，形成新排列
                        MinHeapNode N;
                        N.x = new int[vertex_num];
                        for (int j = 1; j <= vertex_num; j++)
                        {
                            N.x[j] = E.x[j];
                        } // 复制历史记录
                        N.cc = cc;
                        N.s = E.s + 1;
                        N.lcost = b;
                        N.rcost = rcost;
                        H.push(N);
                        std::swap(E.x[E.s + 1], E.x[i]);
                    }
                }
            }
            delete[] E.x; // 完成节点拓展，释放空间
        }
        if (!H.empty())
        {
            E = H.top();
            H.pop();
        }
        else
        {
            break;
        }
    }
    if (bestc == NoEdge)
        return NoEdge; // 无回路
    for (int i = 1; i <= vertex_num; i++)
    {
        bestx[i] = E.x[i];
    }   // 返回最优解
    while (1) // 释放剩余空间
    {
        delete[] E.x;
        if (!H.empty())
        {
            E = H.top();
            H.pop();
        }
        else
        {
            break;
        }
    }
    return bestc;               // 返回最优值
}

void InitGraph(Traveling &tl)
{
    scanf("%d%d", &(tl.vertex_num), &(tl.edge_num)); // 输入顶点数和边数
    for (int i = 0; i <= MAX_VNUM; i++)              // 初始化无向图邻接矩阵
    {
        for (int j = 0; j <= MAX_VNUM; j++)
        {
            tl.a[j][i] = NoEdge;
        }
    }
    for (int i = 0; i < tl.edge_num; i++) // 填写邻接矩阵
    {
        int x = 0, y = 0, cost = 0;
        scanf("%d%d%d", &x, &y, &cost); // 输入邻接点、花费
        tl.a[x][y] = tl.a[y][x] = cost;
    }
}

int main()
{
    int bestx[MAX_VNUM+4];
    Traveling tl;
    InitGraph(tl);
    tl.Solve(bestx);
    printf("The best solution is:\"");
    for(int i = 1; i<= tl.vertex_num; i++)
    {
        printf("%2d", bestx[i]);
    }
    printf("%2d", 1);               // 回到起始节点
    printf(" \".\n");
    printf("Best value is: %d", tl.bestc);

    return 0;
}
