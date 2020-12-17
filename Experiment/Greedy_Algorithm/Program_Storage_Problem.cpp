#include <iostream>
#include <algorithm>
#include <cstdio>

int main()
{
    int N = 0, L = 0;               // 程序总个数、磁带长度
    scanf("%d%d", &N, &L);

    int* pro_lens = new int[L];
    for(int i = 0; i< N; i++)
    {
        scanf("%d", &(pro_lens[i]));
    }// 输入完毕

    sort(pro_lens, pro_lens+N, std::less<int>());

    int suml = 0, sumn = 0, k = 0;
    while(suml + pro_lens[k] <= L)
    {
        suml += pro_lens[k];
        ++sumn;
        ++k;
    }

    printf("%d\n", sumn);


    return 0;
}
