#include<stdio.h>
#include<math.h>

int main()
{

    const double pi = acos(-1.0);   // 获取 π 值（尽量用 const 关键字声明常数）
    double r, h, s1, s2, s;
    scanf("%lf%lf", &r, &h);        // 输入采用了 `%lf`
    s1 = pi *r *r;
    s2 = 2 *pi *r *h;
    s = s1 *2.0 + s2;
    printf("Area = %.3f\n", s);

    return 0;
}