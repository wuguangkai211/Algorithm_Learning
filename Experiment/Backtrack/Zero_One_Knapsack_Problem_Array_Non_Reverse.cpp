#include <algorithm>
#include <cstdio>
#include <iostream>
using namespace std;

const int MAX_DIM = 7;       // 物品种类总数（解向量维度）
const double DEFAULT = -1.0; // 默认值
const int ERROR = -2;

double c = 150.0;                                                 // 背包的最大载重量
double w[] = {DEFAULT, 10.0, 30.0, 25.0, 50.0, 40.0, 60.0, 35.0}; // 按照单位价值降序排列
double p[] = {DEFAULT, 40.0, 40.0, 30.0, 50.0, 35.0, 30.0, 10.0};
int x[MAX_DIM + 1]; // 创建动态解向量（编号从 1开始）

// 最佳信息
double best_profit = DEFAULT;
int best_x[MAX_DIM + 1];

void Output()
{
    double sump = 0.0;
    printf("A solution was found: \"");
    for (int i = 1; i <= MAX_DIM; i++)
    {
        best_x[i] = x[i]; // 这个时候的最优解就是该叶子结点所代表的的解（叶子结点没有被剪掉）
        printf("%2d", x[i]);
        sump += x[i] * p[i];
    }
    best_profit = sump;
    printf(" \", its sum profit: %.2lf.\n", sump);
}

// 约束函数
bool Constraint(int t)
{
    double sumw = 0;
    for (int i = 1; i <= t; i++)
    {
        sumw += x[i] * w[i];
    }
    if (sumw > c)
        return false;
    else
        return true;
}

// 限界函数
bool Bound(int t)
{
    int tt = t;
    double sump = 0.0, sumw = 0.0;
    for (int i = 1; i <= tt; i++) // 计算现在已经装载的重量和价值
    {
        sump += p[i] * x[i];
        sumw += w[i] * x[i];
    }
    int k = tt + 1;                          // 从下一个物品开始尝试新加入背包
    while (k <= MAX_DIM && sumw + w[k] <= c) // 尽可能地多放入物品，直到不能完整装下一件物品
    {
        sumw += w[k];
        sump += p[k];
        ++k;
    }
    if (k <= MAX_DIM && sumw + w[k] > c) // 还有物品可以装，并且背包未达到最大重量
    {
        sump += ((c - sumw) / w[k]) * p[k];
    }
    if (sump > best_profit)
        return true;
    else
        return false;
}

// 返回当前节点的第 i 个可选值，左 1右 0
int getValidVal(int i)
{
    if (i == 1)
    {
        return 1;
    }
    else if (i == 2)
    {
        return 0;
    }
    else
    {
        return ERROR;
    }
}

int array[MAX_DIM + 1] = {-1, 1, 1, 1, 1, 1, 1, 1};

// 返回可选节点编号
int getValidId(int t)
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
        for (int i = getValidId(t);; i = getValidId(t)) // 最多有两种可能取值个数
        {
            int tt = getValidVal(i);
            if (tt != ERROR)
            {
                x[t] = tt;
                if (((tt == 1) && Constraint(t)) || ((tt == 0) && Bound(t)))
                {
                    if (t == MAX_DIM) // 是一个完整的可行解
                    {
                        Output();
                    }
                    else
                    {
                        ++t;
                    }
                }
            }
            else
            {
                array[t] = 1; // 还原
                break;        // 该节点搜索完毕
            }
        }
        --t; // 返回到上一层
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
    printf(" \", which profit is %.2lf.\n", best_profit);

    return 0;
}
