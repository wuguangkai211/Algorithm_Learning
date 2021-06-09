#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

void swap(int *a, int *b)
{
    //printf("Swap\n");
    int tt = *a;
    *a = *b;
    *b = tt;
}

// 数组分段实现
int partition(int a[], int pivot, int r)
{
    //printf("Partition\n");
    int i = pivot, j = r + 1; // 这里默认的 pivot 元素是最左边的元素
    int x = a[pivot];         // 将 pivot 处的元素挖出来
    while (1)
    {
        while (a[++i] < x && i < r)
            ; // 保证 i 与 j 不会越界
        while (a[--j] > x)
            ;
        if (i >= j)
            break; // i 与 j 发生交叉，找到了基准元素应在的位置
        else
            swap(&(a[i]), &(a[j])); // 未发生交叉，则应当交换这两个元素，使
    }
    a[pivot] = a[j]; // 将占有 pivot 应当存放的位置上的元素挖出来，并填到现在 pivot 元素的位置
    a[j] = x;        // 将之前挖出来的 pivot 元素填到上一步挖出来的坑上

    return j; // 返回此时 pivot 元素的下标
}

// 串行快速排序实现
void quickSort_Sequential(int a[], int l, int r)
{
    //printf("Sequential\n");
    if (l < r) // 保证符合实际意义，不符合时 “什么也不做 ”（相当于 return）
    {
        int q = partition(a, l, r);
        quickSort_Sequential(a, l, q - 1);
        quickSort_Sequential(a, q + 1, r);
    }
}

int main()
{

    int length = 15;
    int nArray[15] = {3, 1, 4, 2, 1, 5, 7, 18, 9, 8, 9, 111, 89, 0, -3}; // 导入待排序数据
    int pivot = 0, r = length - 1;
    clock_t startTime, endTime;
    startTime = clock();
    quickSort_Sequential(nArray, pivot, r);
    endTime = clock();
    printf("%.10lfs\n", (double)(endTime - startTime));// / CLOCKS_PER_SEC
    

    return 0;
}
