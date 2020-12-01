#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <iomanip>
#include <iostream>
using namespace std;

// 找到 x 时返回其在数组中的位置（要求传入的数组元素由小到大排列）
template <class Type>
int BinarySearch(Type a[], const Type &x, int len)
{
    int left = 0, right = len - 1; // 左右指针
    while (left <= right)
    {
        int middle = (left + right) / 2;
        if (x == a[middle])
        {
            return middle;
        }
        if (x > a[middle])
        {
            left = middle + 1;
        }
        else
        {
            right = middle - 1;
        }
    }
    return -1; // 未找到 x
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

    // 需要查找的元素
    int ele = 0;

    int location = BinarySearch(a, ele, len);
    
    if(location != -1)
    {
        printf("%d\'s Location: %d.\n", ele, location);
    }
    else
    {
        printf("Not found!\n");
    }

    return 0;
}
