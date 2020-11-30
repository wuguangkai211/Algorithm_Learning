#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iomanip>
#include <iostream>

const int MAX_SIZE = 4;

int tile = 1;                  // L 型骨牌号
int Board[MAX_SIZE][MAX_SIZE]; // 棋盘

// 当前棋盘左上角方格的行列号、特殊方格的行列号、棋盘大小
void ChessBoard(int tr, int tc, int dr, int dc, int size)
{
    if (size == 1)
        return;       // 棋盘已经化为 1* 1
    int t = tile++;   // L 型骨牌号从 1开始
    int s = size / 2; // 分割棋盘（注意这里不能设置为全局变量）

    if (dr < tr + s && dc < tc + s) // 特殊方格在划分后的左上区域
    {
        ChessBoard(tr, tc, dr, dc, s);
    }
    else // 特殊方格不在划分后的左上区域
    {
        Board[tr + s - 1][tc + s - 1] = t;             // L 型骨牌的一角覆盖此区域的右下角
        ChessBoard(tr, tc, tr + s - 1, tc + s - 1, s); // 对此区域递归执行该解决方案（子问题求解）
    }

    if (dr < tr + s && dc >= tc + s) // 特殊方格在划分后的右上区域
    {
        ChessBoard(tr, tc + s, dr, dc, s);
    }
    else // 特殊方格不在划分后的右上区域（化归思想）
    {
        Board[tr + s - 1][tc + s] = t;                 // L 型骨牌的一角覆盖此区域的左下角
        ChessBoard(tr, tc + s, tr + s - 1, tc + s, s); // 对此区域递归执行该解决方案（子问题求解）
    }

    if (dr >= tr + s && dc < tc + s) // 特殊方格在划分后的左下区域
    {
        ChessBoard(tr + s, tc, dr, dc, s);
    }
    else // 特殊方格不在划分后的左下区域
    {
        Board[tr + s][tc + s - 1] = t;                 // L 型骨牌的一角覆盖此区域的右上角
        ChessBoard(tr + s, tc, tr + s, tc + s - 1, s); // 对此区域递归执行该解决方案（子问题求解）
    }

    if (dr >= tr + s && dc >= tc + s) // 特殊方格在划分后的右下区域
    {
        ChessBoard(tr + s, tc + s, dr, dc, s);
    }
    else // 特殊方格不在划分后的右下区域
    {
        Board[tr + s][tc + s] = t;                     // L 型骨牌的一角覆盖此区域的左上角
        ChessBoard(tr + s, tc + s, tr + s, tc + s, s); // 对此区域递归执行该解决方案（子问题求解）
    }
}

int main()
{
    // 初始化参量（棋盘左上角方格的行列号、特殊方格的行列号、棋盘大小）
    int tr = 0, tc = 0;
    int dr = 0, dc = 1;
    int size = MAX_SIZE;

    // 初始化棋盘矩阵
    for (int i = 0; i < MAX_SIZE; i++)
    {
        for (int j = 0; j < MAX_SIZE; j++)
        {
            Board[i][j] = 0;
        }
    }

    // 放置 L型骨牌
    ChessBoard(tr, tc, dr, dc, size);

    // 将放置情况简单输出
    for (int i = 0; i < MAX_SIZE; i++)
    {
        for (int j = 0; j < MAX_SIZE; j++)
        {
            printf("%d ", Board[i][j]);
        }
        printf("\n");
    }

    printf("\n");
    printf("%d", tile);

    return 0;
}
