#include <cstdio>

#define MAX_SIZE 55
#define inf 0x3f3f3f3f

int a[MAX_SIZE], b[MAX_SIZE];
int dp[MAX_SIZE][MAX_SIZE];
int x[MAX_SIZE];

// 填写动态规划表 dp
void Schedule(int N, int sum)
{
    for (int i = 1; i <= N; i++)
    {
        for (int j = 0; j <= sum; j++)
        {
            if (j < a[i]) // 该任务不能交给 a来做，只能交给 b来做
            {
                dp[i][j] = dp[i - 1][j] + b[i];
            }
            else
            {
                if (dp[i - 1][j - a[i]] > dp[i - 1][j] + b[i])
                {
                    dp[i][j] = dp[i - 1][j] + b[i];
                }
                else
                {
                    dp[i][j] = dp[i - 1][j - a[i]];
                }
            }
        }
    }
}

// 回溯 dp表，找到最优调度解
void TraceBack(int N, int at)
{
    int sumt_a = at, sumt_b = dp[N][at]; // 最有调度情况下 A、B机器的完工时间
    for (int i = N; i >= 1; i--)
    {
        // 首先假设该工件在 A上加工。如果不加工这个工件时 B消耗的时间与加工该工件时 B消耗的时间相等，说明假设成立，即最后一个工件一定是在 A机器上加工的
        if (dp[i - 1][sumt_a - a[i]] == dp[i][at]) 
        {
            x[i] = 1;
            sumt_a -= a[i];
            at = sumt_a;
        }
        else // 这说明最后一个工件一定是在 B机器上加工的（不是在 A上就是在 B上）
        {
            x[i] = 2;
            sumt_b -= b[i];
        }
    }
}

int main()
{
    int N; // 总工件数
    scanf("%d", &N);

    int sum = 0; // A机器最大加工时间
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
    Schedule(N, sum);

    // 输出 dp矩阵
    for (int i = 1; i <= N; i++)
    {
        for (int j = 0; j <= sum; j++)
        {
            printf("%3d", dp[i][j]);
        }
        printf("\n");
    }

    // 输出最优时间
    int ans = inf, at = 0;
    for (int j = 0; j <= sum; j++)
    {
        int temp = (dp[N][j] > j) ? dp[N][j] : j; // max{ j, dp[N][j] }，即 A机器和 B机器 ·都·停止 的时刻
        if (temp < ans)                           // min{ max{j, dp[N][j]} }，最短处理时间，取最小值
        {
            ans = temp;
            at = j; // 记录答案的列位置
        }
    }
    printf("Optimal time: %d.\n", ans);

    // TraceBack
    TraceBack(N, at);

    // 输出任务安排情况
    for (int i = 1; i <= N; i++)
    {
        if (x[i] == 1)
            printf("A ");
        else if (x[i] == 2)
            printf("B ");
    }
    printf("\n");

    return 0;
}

/*
 独立任务最优调度
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

/*
 思路：dp[i][j]表示在做 ·前· i个作业 A机器消耗 j时间时，B机器消耗的最小时间
 当 A在时间 j小于 A[i]时，任务 i只能给 A来做
 当 A在时间 j大于 A[i]时，
 给 A处理，A花费时间：dp[i - 1][j-a[i - 1]]
 给 B处理，B花费时间：dp[i - 1][j] + b[i - 1]
 选择花费时间小的方式。
 在回溯寻找最优解时，从找到最优时间的位置开始，先判断最后一个工件（未判断过的）是否在 A机器上加工。如果不是，则一定在 B机器上加工。
*/

/*
6
2 5 7 10 5 2
3 8 4 11 3 4
*/
