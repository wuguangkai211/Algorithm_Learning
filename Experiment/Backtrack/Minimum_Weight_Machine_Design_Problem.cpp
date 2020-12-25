#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <iostream>

const int INF = 9999999; // 无穷大
const int MAX_UNUM = 56; // 最大部件数
const int MAX_PNUM = 56; // 最大供应商数目

int n; // 部件总个数
int m; // 供应商总数
int d; // 限定价格
int cost[MAX_UNUM + 2][MAX_PNUM + 2], weight[MAX_UNUM + 2][MAX_PNUM + 2];
int cw = 0, cc = 0;
int bestc = INF, bestw = INF;
int ttx[MAX_UNUM + 2], bestx[MAX_UNUM + 2];

// 更新最优信息
void ReNew();

// 约束函数
bool Constraint()
{
    if (cc <= d)
        return true; // 若未超过限定价格，则不剪枝
    else
        return false;
}

// 限界函数
bool Bound()
{
    if (cw >= bestw)
        return false; // 若现有重量大于等于最优重量，则剪枝
    else
        return true;
}

// 递归式回溯算法
void BackTrack(int t)
{
    if (t > n)
        ReNew();
    else
    {
        for (int i = 1; i <= m; i++)
        {
            cw += weight[t][i];
            cc += cost[t][i];
            ttx[t] = i;
            if (Constraint() && Bound())
            {
                BackTrack(t + 1); // 进入下一层
            }
            cw -= weight[t][i]; // 退回原状态
            cc -= cost[t][i];
        }
    }
}

// 初始化
void Init();

int main()
{
    Init();
    printf("START!\n");
    BackTrack(1);
    printf("END!\n");

    printf("The best weight value is: %d.\n", bestw);
    printf("The best cost value is: %d.\n", bestc);
    printf("The best solution is: \"");
    for (int i = 1; i <= n; i++)
    {
        printf("%2d", bestx[i]);
    }
    printf(" \".\n");

    return 0;
}

// 初始化
void Init()
{
    scanf("%d%d%d", &n, &m, &d);
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            scanf("%d", &cost[i][j]);
        }
    } // 输入各部件的供货商价格信息
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            scanf("%d", &weight[i][j]);
        }
    } // 输入各部件的供货商重量信息
}

// 更新最优信息
void ReNew()
{
    bestc = cc, bestw = cw;
    for (int i = 1; i <= n; i++)
    {
        bestx[i] = ttx[i];
    }
}

/*
3 3 4
1 2 3
3 2 1
2 2 2
1 2 3
3 2 1
2 2 2
*/
