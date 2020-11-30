#include <stdio.h>



int main()
{

    printf("%.1f\n", 8.0 / 5.0);
    printf("%.2f\n", 8.0 / 5.0);
    printf("%.1f\n", 8 / 5);        // WRONG
    printf("%d\n", 8.0 / 5.0);      // WRONG

    return 0;
}

// 整数值用 %d 输出， 实数用 %f 输出
// 整数 / 整数 == 整数， 浮点数 / 浮点数 == 浮点数
