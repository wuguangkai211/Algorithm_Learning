#include <cstdio>

#define MAX_SIZE 55
#define inf 0x3f3f3f3f

int a[MAX_SIZE], b[MAX_SIZE];
int dp[MAX_SIZE][MAX_SIZE];

int main()
{
    int N;
    scanf("%d", &N);

    int sum = 0;
    for (int i = 1; i <= N; i++)
    {
        scanf("%d", &a[i]);
        sum += a[i];
    }
    for (int i = 1; i <= N; i++)
    {
        scanf("%d", &b[i]);
    }
    printf("Sum == %d.\n", sum);

    // 核心
    for (int i = 1; i <= N; i++)
    {
        for (int j = 0; j <= sum; j++)
        {
            if (j < a[i])       // 该任务不能交给 a来做，只能交给 b来做
            {
                dp[i][j] = dp[i - 1][j] + b[i];
            }
            else
            {
                dp[i][j] = (dp[i - 1][j - a[i]] > dp[i - 1][j] + b[i]) ? (dp[i - 1][j] + b[i]) : (dp[i - 1][j - a[i]]);         // 取两种情况的最小值
            }
        }
    }

    // 输出矩阵
    for (int i = 1; i <= N; i++)
    {
        for (int j = 0; j <= sum; j++)
        {
            printf("%3d", dp[i][j]);
        }
        printf("\n");
    }

    // 输出最优时间
    int ans = inf;
    for (int j = 0; j <= sum; j++)
    {
        int temp = (dp[N][j] > j) ? dp[N][j] : j;
        if (temp < ans)
        {
            ans = temp;
        }
    }
    printf("Optimal time: %d.\n", ans);

    return 0;
}

/**
 * 独立任务最优调度
用两台处理机A和B处理n个作业。设第i个作业交给A处理需要时间ai，交给B处理需要时间bi。
由于各作业的特点和机器的性能关系，ai和bi之间没有明确的大小关系。
既不有将一个作业分开由2台机器处理，也没有一台机器能同时处理2个作业。
设计一个动态规划算法，使得这两台机器处理完这n个作业的时间最短。
测试用例：
6（任务数目）
2 5 7 10 5 2（机器A处理这些任务的时间）
3 8 4 11 3 4（机器B处理这些任务的时间）
输出：15
请用动态规划算法实现
 */

/**
 * 思路：dp[i][j]表示在做第 i个作业a使用不小于 j时间时，b使用的时间
 * 当a在时间 j小于a[i]时，任务 i只能给 b来做
 * 当a在时间 j大于a[i]时，
 * 给a处理，a花费时间dp[i - 1][j-a[i - 1]]
 * 给b处理，b花费时间dp[i - 1][j] + b[i - 1]
 * 选择花费时间小的方式
 */

/* 6
2 5 7 10 5 2
3 8 4 11 3 4 */
