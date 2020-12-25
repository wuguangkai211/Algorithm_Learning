#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <iostream>

const int INF = 9999999; // 模拟无限大
const int MAX_PNUM = 56; // 最大人数（工作数）

int pnum = 0;                            // 总人数
int costlib[MAX_PNUM + 2][MAX_PNUM + 2]; // 工作 i与 j个人的费用数据库

int ttx[MAX_PNUM + 2];   // 暂存解
int bestx[MAX_PNUM + 2]; // 最优解
int bestc = INF;         // 最优值
int cc = 0;              // 当前花费

// 更新最优解信息
void ReNew()
{
    bestc = cc;
    for(int i = 1; i<= pnum; i++)
    {
        bestx[i] = ttx[i];
    }
}

// 限界函数
bool Bound()
{
    if(cc >= bestc) return false;
    else return true;
}

// 递归式回溯算法
void BackTrack(int t)
{
    if (t > pnum)               // 到达叶子结点以下
        ReNew();
    else
    {
        for(int i = t; i<= pnum; i++)
        {
            std::swap(ttx[t], ttx[i]);
            cc += costlib[ttx[t]][t];
            if(Bound())                     // 若满足限界函数（即小于当前最优值）
            {
                BackTrack(t + 1);           // 进入下一层
            }
            cc -= costlib[ttx[t]][t];
            std::swap(ttx[t], ttx[i]);
        }
    }
}

// 初始化
void Init()
{
    scanf("%d", &pnum); // 第一行输入总人数（也是工作数）
    for (int i = 1; i <= pnum; i++)         // 第 i份工作
    {
        for (int j = 1; j <= pnum; j++)     // 第 j个人
        {
            scanf("%d", &costlib[i][j]);     // 费用
        }
    }                               // 输入费用矩阵
    for (int i = 1; i <= pnum; i++) // 初始化单位排列
    {
        ttx[i] = i;
    }
}

int main()
{
    Init();
    BackTrack(1);

    printf("The best value is: %d.\n", bestc);

    return 0;
}

/*
3
10 2 3
2 3 4
3 4 5
*/
