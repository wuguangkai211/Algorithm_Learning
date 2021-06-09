#include <math.h>
#include <stdio.h>
#include <stdlib.h>

// Definition for a binary tree node.
struct TreeNode
{
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

int allSize = 0;
int curptr = 0;

void inner(struct TreeNode *root, int* val, int* returnSize)
{
    if (root)
    {
        ++allSize;
        inner(root->left, val, returnSize);
        val[curptr++] = root->val;
        inner(root->right, val, returnSize);
        *returnSize = allSize;
    }
    else
    {
        *returnSize = 0;
    }
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *inorderTraversal(struct TreeNode *root, int *returnSize)
{
    int *val = (int *)malloc(sizeof(int) * 101);            // 树中节点数目在范围 [0, 100] 内
    allSize = 0;
    curptr = 0;
    inner(root, val, returnSize);
    return val;
}


int main()
{
    int *returnSize = (int *)malloc(sizeof(int));
    struct TreeNode *root = (struct TreeNode *)malloc(sizeof(struct TreeNode));
    root->val = 1;
    root->right = NULL;
    root->left = NULL;
    int *answer = inorderTraversal(root, returnSize);
    for (int i = 0; i < *returnSize; i++)
    {
        printf("%d\n", answer[i]);
    }

    return 0;
}
