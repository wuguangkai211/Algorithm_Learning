#include <cstdio>
#include <vector>
using std::vector;

int main()
{
    int K = 0;        // 路途加油站总数
    int M = 0;        // 汽车一次加油可以行驶的最大距离（单位：千米）
    int dist[K + 1];  // 记录各相邻加油站（包括起始点、目的地）之间的距离
    vector<int> pass; // 记录经过的加油站编号

    // 载入加油站总数、汽车信息
    scanf("%d%d", &K, &M);

    for (int i = 0; i < K + 1; i++)
    {
        scanf("%d", &(dist[i]));
    } // 载入距离信息，输入结束

    for (int i = 0; i < K + 1;) // 遍历距离数组
    {
        int sumt = 0, j = i;          // 计算最远距离
        while (sumt < M && j < K + 1) // 寻找距离最近且不可到达的加油站
        {
            sumt += dist[j++];       // j: start from i to K
        }                            // j 为最近的且不能到达的加油站编号
        if (j == K + 1 && sumt <= M) // 从该点可以直达终点（到终点可以没有油）
            break;                   // 已经到达终点
        else
        {
            i = j - 1;         // 下一次出发的地点
            pass.push_back(i); // 记录该加油站的编号
        }
    }

    // 输出加油次数
    int rnum = pass.size();
    printf("Number of refueling: %d.\n", rnum);

    // 输出加油点
    printf("Refueling point(s): ");
    for (int i = 0; i < rnum; i++)
    {
        if (i == 0)
            printf("%d", pass[i]);
        else
            printf(" %d", pass[i]);
    }
    printf("\n");

    return 0;
}

// 思路：汽车总是在加满油的情况下，试图在既定的旅途中一次行走更长的距离。
// 但是这段距离不能太长，以致汽车在不是加油点的地方没有油可用（抛锚）。
// 所以当汽车满油行驶距离小于当前汽车位置（一定是某个加油站）到最近的且无法到达的加油站的距离时，选择它的前一个加油点及时加油。
// 直到到达第 K+1个加油点（终点）。

// 目标：计算最小加油次数。

/* Input:
7 7
1 2 3 4 5 1 6 6
*/

// Output:
// 4
