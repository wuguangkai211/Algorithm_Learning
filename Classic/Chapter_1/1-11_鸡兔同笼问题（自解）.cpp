#include <stdio.h>



int main()
{

    int n, m;       // 鸡和兔的总数量为 n ，总腿数为 m
    int flag = 0;
    scanf("%d %d", &n, &m);
    for(int i = 0; i <= n; i++)
    {
        flag = 0;
        int j = n - i;
        if(j*4 + i*2 == m)
        {
            flag = 1;
            printf("%d %d\n", i, j);
            break;
        }
    }
    if(flag == 0)
        printf("No answer");

    return 0;
}
