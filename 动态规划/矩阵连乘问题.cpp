#include <iostream>
#include <cstdio>

#define maxn 200


int m[maxn][maxn];
int s[maxn][maxn];
int p[] = {50, 10, 40, 30, 5};

// 矩阵链计算
// 参数：矩阵尺寸参数表  矩阵个数  矩阵最小乘法计算次数  矩阵最简计算顺序划分位置
void MatrixChain(int n)
{
    // 初始化：只有一个矩阵参与计算时（矩阵链长度为 1），共进行 0次算术乘法
    for(int i = 1; i<= n; i++)
    {
        m[i][i] = 0;
    }

    // 矩阵链从 2开始增长，一直到与矩阵总个数 n相同（r表示矩阵链长度）
    for(int r = 2; r<= n; r++)
    {
        // from Ai to Aj
        for(int i = 1; i<= n-r+1; i++)      // WRONG: i = 2
        {
            int j = i+r-1;          
            // 总计算次数 == 左边单独的算数乘次数 + 右边单独的算数乘次数 + 左右结果矩阵相乘的算数乘次数
            m[i][j] = m[i][i] + m[i+1][j] + p[i-1]* p[i]* p[j];    
            s[i][j] = i;            // 记录初始最优分割点为：i
            for(int k = i+1; k< j; k++)
            {
                int t = m[i][k] + m[k+1][j] + p[i-1]* p[k]* p[j];
                if(t < m[i][j])     // 找到更好的分割点（使整体计算次数减小）
                {
                    m[i][j] = t;
                    s[i][j] = k;
                }
            }
        }
    }
}

void Traceback(int i, int j)
{
    if(i == j) return;
    Traceback(i, s[i][j]);
    Traceback(s[i][j]+1, j);
    std::cout << "Multiply A " << i << ", " << s[i][j];
    std::cout << " and A " << (s[i][j]+1) << ", " << j << std::endl;
}


int main()
{
    MatrixChain(4);
    Traceback(1, 4);



    return 0;
}
