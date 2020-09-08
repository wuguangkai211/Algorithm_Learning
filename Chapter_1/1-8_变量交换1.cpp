#include<stdio.h>



int main()
{
    // 交换两个变量的三变量法适用范围广， 推荐使用
    int a, b, t;
    scanf("%d%d", &a, &b);
    t = a;
    a = b;
    b = t;
    printf("%d %d\n", a, b);
    
    return 0;
}