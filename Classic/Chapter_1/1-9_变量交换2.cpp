#include<stdio.h>



int main()
{
    // 只有定义了加减法的数据类型才能采用此方法
    int a, b;
    scanf("%d%d", &a, &b);
    a = a + b;
    b = a - b;
    a = a - b;
    printf("%d %d\n", a, b);
    
    return 0;
}
