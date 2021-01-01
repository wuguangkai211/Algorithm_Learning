#include "conio.h"
#include "malloc.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

const int MAX_STEPS = 20; // 定义20个台阶的楼梯
int Steps[MAX_STEPS];    // Steps[i]等于1或者等于2，记录第i步登上的台阶数
int cnt = 0;             // 记录上楼梯的方案的数目

// footstep:当前要登的台阶数、sums：已经走过的阶数、step:走过的步数
void Upstairs(int footstep, int sums, int t)
{
    if (sums + footstep == MAX_STEPS) //得到一种上楼梯方案
    {
        Steps[t] = footstep;
        ++cnt; //方案数+1
/*         for (int i = 0; i <= t; i++)
        {
            printf("%d ", Steps[i]);
        } //打印出方案
        printf("\n"); */
        return; //返回到该节点的父结点，不必再向下搜索
    }
    else if (sums + footstep > MAX_STEPS)
    {
        return; // 超过了楼梯的阶数，不必再向下搜索，返回到父结点
    }
    else // sums + footstep < MAX_STEPS
    {
        Steps[t++] = footstep; // 记录当前上楼梯的台阶数，步数+1
        sums += footstep;         // 记录目前已经走过的台阶数
        // 递归探索后续的分支
        Upstairs(1, sums, t); // 走1步的分支
        Upstairs(2, sums, t); // 走2步的分支
    }
}

int main()
{
    for (int i = 1; i <= 2; i++)
    {
        Upstairs(i, 0, 0);
    }
    printf("%d\n", cnt);
    // _getche();
    return 0;
}
