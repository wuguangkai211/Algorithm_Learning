#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;

const int MAX_VNUM = 56;  // 存储空间所允许的最大容量
const int INF = 99999999; // 模拟无限大
const int NOEDGE = INF;   // 无边标记

int vertex_num = 0, edge_num = 0;          // 图的顶点数、边数
int Graph_Adj[MAX_VNUM + 1][MAX_VNUM + 1]; // 图的邻接矩阵

int x[MAX_VNUM + 1];     // 当前解
int bestx[MAX_VNUM + 1]; // 存储当前的最优解
int bestc = NOEDGE;      // 存储当前的最优值
int cc = 0;              // 当前的费用

// 初始化各参数变量
void Init()
{
    scanf("%d%d", &vertex_num, &edge_num); // 输入顶点数和边数
    for (int i = 0; i <= MAX_VNUM; i++)    // 初始化无向图邻接矩阵
    {
        for (int j = 0; j <= MAX_VNUM; j++)
        {
            Graph_Adj[j][i] = NOEDGE;
        }
    }
    for (int i = 1; i <= edge_num; i++) // 填写邻接矩阵
    {
        int x = 0, y = 0, cost = 0;
        scanf("%d%d%d", &x, &y, &cost); // 输入邻接点、花费
        Graph_Adj[x][y] = Graph_Adj[y][x] = cost;
    }
    for (int i = 1; i <= vertex_num; i++) // 置 x为单位排列
    {
        x[i] = i;
    }
}

// TSP 回溯算法
void BackTrack(int t)
{
    if (t == vertex_num) // 此时在叶子的父节点
    {
        if ((Graph_Adj[x[vertex_num - 1]][x[vertex_num]] != NOEDGE) && (Graph_Adj[x[vertex_num]][1] != NOEDGE) && (cc + Graph_Adj[x[vertex_num - 1]][x[vertex_num]] + Graph_Adj[x[vertex_num]][1] < bestc || bestc == NOEDGE)) // 构成回路且更优，考虑没有解（起始点是 1）
        {
            for (int i = 1; i <= vertex_num; i++)
            {
                bestx[i] = x[i];
            }

            bestc = cc + Graph_Adj[x[vertex_num - 1]][x[vertex_num]] + Graph_Adj[x[vertex_num]][1];
        }
    }
    else
    { // printf("----------\n");
        for (int i = t; i <= vertex_num; i++)
        {
            if (Graph_Adj[x[t - 1]][x[i]] != NOEDGE && (cc + Graph_Adj[x[t - 1]][x[i]] < bestc || bestc == NOEDGE))
            {
                swap(x[t], x[i]);
                cc += Graph_Adj[x[t - 1]][x[t]];
                BackTrack(t + 1);
                cc -= Graph_Adj[x[t - 1]][x[t]];
                swap(x[t], x[i]);
            }
        }
    }
}

int main()
{
    Init();
    BackTrack(2);

    printf("The best solution is:\"");
    for(int i = 1; i<= vertex_num; i++)
    {
        printf("%2d", bestx[i]);
    }
    printf("%2d", 1);               // 回到起始节点
    printf(" \".\n");
    printf("The best min-costs is: %d.\n", bestc);

    return 0;
}

/*
3 3
1 2 4
1 3 8
2 3 2
*/

/*
4 5
1 2 4
1 3 8
2 3 2
1 4 3
4 3 1
*/
