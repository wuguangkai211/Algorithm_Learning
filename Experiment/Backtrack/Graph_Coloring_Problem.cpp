#include <cmath>
#include <cstdio>
#include <cstring>
using namespace std;

const int MAX_VNUM = 106;
const int DEFAULT = 0;

int sums = 0; // 总的填色可行方案数
int vertex_num = 0, edge_num = 0, m = 0;

int x[MAX_VNUM] = {
    0,
}; // 存放当前的着色序列
int G_Adj[MAX_VNUM][MAX_VNUM] = {
    0,
}; // 图的邻接矩阵

// 判断给点t着色为x[t]是否可行
bool Legal(int t)
{
    for (int i = 1; i < t; i++)
    {
        if ((G_Adj[i][t] == 1) && (x[i] == x[t]))
        {
            return false;               // 与当前节点相邻的节点不能与之同色
        }
    }
    return true; // 所有与之相邻的节点都不与之同色，则合法
}

void BackTrack(int t)
{
    if (t > vertex_num) // 找到了一个可行的涂色方案
    {
        ++sums;
        printf("A solution is found: \"");
        for (int i = 1; i <= vertex_num; i++)
        {
            printf("%2d", x[i]);
        }
        printf(" \".\n");
        return;
    }
    else //还没有到叶子节点，需要给当前节点可行的涂色
    {
        for (int i = 1; i <= m; i++) // 子树是一个 m叉树
        {
            x[t] = i;     // 尝试给第 i个顶点着第 k种颜色
            if (Legal(t)) // 着色合法
                BackTrack(t + 1);
            else // 如果顶点着第 k种颜色不可行，不涂色，便于后续涂色
            {
                x[t] = DEFAULT;
            }
        }
        return; //如果当前节点所有颜色都不可行，结束对子树的遍历，返回
    }
}

int main()
{
    scanf("%d%d%d", &vertex_num, &edge_num, &m);
    for (int i = 1; i <= edge_num; i++) // 载入节点邻接关系
    {
        int x, y;
        scanf("%d%d", &x, &y);
        G_Adj[x][y] = G_Adj[y][x] = 1; // 填写图的邻接矩阵
    }
    BackTrack(1); // 执行回溯算法
    printf("The number of solutions: %d.\n", sums);

    return 0;
}

/*
7 11 3
1 6
1 7
1 2
6 7
7 2
5 6
6 4
7 3
3 2
5 4
4 3
*/
