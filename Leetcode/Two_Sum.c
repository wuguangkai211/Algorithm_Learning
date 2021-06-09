#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>

int *twoSum(int *nums, int numsSize, int target, int *returnSize)
{
    for (int i = 0; i < numsSize-1; ++i)
    {
        for (int j = i + 1; j < numsSize; ++j)
        {
            if (nums[i] + nums[j] == target)
            {
                *returnSize = 2;                    // returnSize 需要指定
                int *answer = (int *)malloc(sizeof(int) * 2);
                answer[0] = i;
                answer[1] = j;
                return answer;
            }
        }
    }
    *returnSize = 0;
    return NULL;
}

int main()
{
    int numsSize = 0;
    int returnSize = 0;
    scanf("%d", &numsSize);

    int *nums = (int *)malloc(sizeof(int) * numsSize);
    for (int i = 0; i < numsSize; i++)
    {
        scanf("%d", &(nums[i]));
    }

    int target = 0;
    scanf("%d", &target);

    int* answer = twoSum(nums, numsSize, target, &returnSize);

    printf("[%d,%d]", answer[returnSize-2], answer[returnSize-1]);

    free(answer);
    free(nums);

    return 0;
}
