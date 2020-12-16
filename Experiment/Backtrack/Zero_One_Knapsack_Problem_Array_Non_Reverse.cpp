#include <algorithm>
#include <cstdio>
#include <iostream>
using namespace std;

const int MAX_DIM = 3;  // 物品种类总数（解向量维度）为 3
const int DEFAULT = -1; // 默认值
const int ERROR = -2;

int c = 30; // 背包的最大载重量为 30
int w[] = {DEFAULT, 16, 15, 15};
int p[] = {DEFAULT, 45, 25, 25};
int x[MAX_DIM + 1]; // 创建动态解向量（编号从 1开始）

// 最佳信息
int best_profit = DEFAULT;
int best_x[MAX_DIM + 1];

void Output()
{
    int sump = 0;
    printf("A solution was found: \"");
    for (int i = 1; i <= MAX_DIM; i++)
    {
        printf("%2d", x[i]);
        sump += x[i] * p[i];
    }
    printf(" \", its sum profit: %d.\n", sump);
    if (sump > best_profit) // 更新最优信息
    {
        best_profit = sump;
        for (int i = 1; i <= MAX_DIM; i++)
        {
            best_x[i] = x[i];
        }
    }
}

// 是否超载
bool Legal(int t)
{
    int sumw = 0;
    for (int i = 1; i <= t; i++)
    {
        sumw += x[i] * w[i];
    }
    if (sumw > c)
        return false;
    else
        return true;
}

// 返回当前节点的第 i 个可选值
int H(int i)
{
    if (i == 1)
    {
        return 0;
    }
    else if (i == 2)
    {
        return 1;
    }
    else
    {
        return ERROR;
    }
}

int array[MAX_DIM + 1] = {DEFAULT, 1, 1, 1};

// 返回可选节点编号
int F(int t)
{
    int node = array[t];
    ++(array[t]);
    return node;
}

// 模拟子集树回溯（非递归写法）
void IterativeBackTrack()
{
    int t = 1;
    while (t > 0)
    {
        for (int i = F(t); ; i = F(t)) // 最多有两种可能取值个数
        {
            int tt = H(i);
            if(tt != ERROR)
            {
                x[t] = tt;
            }
            else
            {
                array[t] = 1;       // 还原
                break;              // 该节点搜索完毕
            }
            if (Legal(t))
            {
                if (t == MAX_DIM) // 是一个完整的可行解
                    Output();
                else
                {
                    ++t;
                }
            }
        }
        --t;
    }
}

int main()
{
    printf("Begin!\n");
    IterativeBackTrack();
    printf("END!\n");
    printf("The best solution is: \"");
    for (int i = 1; i <= MAX_DIM; i++)
    {
        printf("%2d", best_x[i]);
    }
    printf(" \", which profit is %d.\n", best_profit);

    return 0;
}
