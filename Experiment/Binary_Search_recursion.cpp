#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <iomanip>
#include <iostream>
using namespace std;

// 找到 x 时返回其在数组中的位置（要求传入的数组元素由小到大排列）
template <class Type>
Type* BinarySearch(Type a[], const Type &x, int len)
{
    Type *left = a, *right = a + len - 1; // 左右指针
    if (left <= right)
    {
        Type *middle = left + (len / 2);
        if (x == (*middle))
        {
            return middle;        // 找到目标元素，返回指向该数组元素的指针
        }
        if (x > (*middle))
        {
            BinarySearch(middle + 1, x, right - middle);
        }
        else
        {
            BinarySearch(left, x, middle - left);
        }
    }
    else return NULL; // 未找到 x
}

// 升序运算
bool Int_Less(const int &a, const int &b)
{
    return (a < b);
}

int main()
{
    int a[] = {0, 2, 1, -8, -1, 0, 1, 3, 6, 7, 11};
    int len = sizeof(a) / sizeof(int);

    // 使用排序算法对原始数据进行排序
    sort(a, a + len, Int_Less);

    for(int i = 0; i< len; i++)
    {
        printf("%d ", a[i]);
    }
    printf("\n");

    int ele = 0;               // 需要查找的元素
    int location = -1;
    if(BinarySearch(a, ele, len))           // 返回指针不为空，表示找到了元素
    {
        location = BinarySearch(a, ele, len) - a;           // 元素下标数 == 返回指针 - 起始指针
        printf("%d\'s Location: %d.\n", ele, location);
    }
    else
    {
        printf("Not found!\n");       // 未找到
    }

    return 0;
}
