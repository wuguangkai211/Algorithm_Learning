#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <iomanip>
#include <iostream>
using namespace std;

// 物品序号 i = 1 ~ n，重量 j = 0 ~ c

// 写价值矩阵 m
void Knapsack(int *v, int *w, int c, int n, int **m)
{                            // 从价值矩阵m 的最后一行（对应序号最大的物品）的最后一列开始
    int jMax = min(w[n], c); // 判断是否能装下序号最大的一个物品
    for (int j = 0; j <= jMax; j++)
    {
        m[n][j] = 0;
    }
    for (int j = w[n]; j <= c; j++)
    {
        m[n][j] = v[n];
    }

    for (int i = n - 1; i > 1; i--)
    {
        jMax = min(w[i], c);
        for (int j = 0; j <= jMax; j++)
        {
            m[i][j] = m[i + 1][j]; // 誊抄下一行
        }
        for (int j = w[i]; j <= c; j++)
        {
            m[i][j] = max(m[i + 1][j], m[i + 1][j - w[i]] + v[i]);
        }
        // m[1][c] = m[2][c]; // 矩阵第一行最后一列
        if (c >= w[1])
        {
            m[1][c] = max(m[2][c], m[2][c - w[1]] + v[1]); // 此处 m[2][c] == m[1][c]
        }
    }
}

void Traceback(int **m, int *w, int c, int n, int *x)
{
    for (int i = 1; i < n; i++) // 第一行到倒数第二行
    {
        if (m[i][c] == m[i + 1][c]) // 未装载该物品
        {
            x[i] = 0;
        }
        else // 装载了该物品
        {
            x[i] = 1;
            c -= w[i];
        }
    }
    x[n] = (m[n][c] != 0) ? 1 : 0;
}

int main()
{
    int n = 5, c = 10;

    int *w = (int *)malloc((n + 1) * sizeof(int));
    int *v = (int *)malloc((n + 1) * sizeof(int));
    w[1] = 2, w[2] = 2, w[3] = 6, w[4] = 5, w[5] = 4;
    v[1] = 6, v[2] = 3, v[3] = 5, v[4] = 4, v[5] = 6;

    // 为二级指针分配空间
    int **m = (int **)malloc((n + 1) * sizeof(int *));
    for (int i = 0; i < c + 1; i++)
    {
        m[i] = (int *)malloc((c + 1) * sizeof(int));
    }

    // 解向量
    int *x = (int *)malloc((n + 1) * sizeof(int));

    // 主要部分
    Knapsack(v, w, c, n, m);
    Traceback(m, w, c, n, x);

    // 输出解向量
    int sumv = 0;
    for (int i = 1; i <= n; i++)
    {
        sumv += x[i]* v[i];
        printf("%d ", x[i]);
    }
    

    return 0;
}
