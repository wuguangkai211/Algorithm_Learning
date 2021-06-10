#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct TreeNode
{
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

bool twoTree(struct TreeNode *t1, struct TreeNode *t2){
    bool flag = false;
    if(t1 && t2){
        if(t1->val == t2->val){
            if(twoTree(t1->left, t2->right) && twoTree(t1->right, t2->left)){
                flag = true;
            }
        }
    }
    else if(!t1 && !t2){
        flag = true;
    }
    return flag;
}

bool isSymmetric(struct TreeNode *root)
{
    bool flag = false;
    if (!root)
    {
        flag = true;
    }
    else
    {
        struct TreeNode *lpt = root->left;
        struct TreeNode *rpt = root->right;
        if (lpt && rpt)
        {
            if(lpt->val == rpt->val){
                if(twoTree(lpt->left, rpt->right) && twoTree(lpt->right, rpt->left)){
                    flag = true;
                }
            }
        }
        else if(!lpt && !rpt){
            flag = true;
        }
    }
    return flag;
}

int main()
{
    struct TreeNode *root = (struct TreeNode *)malloc(sizeof(struct TreeNode));
    root->left = (struct TreeNode *)malloc(sizeof(struct TreeNode));
    root->right = (struct TreeNode *)malloc(sizeof(struct TreeNode));
    root->left->left = (struct TreeNode *)malloc(sizeof(struct TreeNode));
    root->right->left = (struct TreeNode *)malloc(sizeof(struct TreeNode));

    root->left->right = NULL;
    root->right->right = NULL;
    root->left->left->left = NULL;
    root->left->left->right = NULL;
    root->right->left->left = NULL;
    root->right->left->right = NULL;

    root->val = 1;
    root->left->val = 2;
    root->right->val = 2;
    root->left->left->val = 2;
    root->right->left->val = 2;

    isSymmetric(root) ? printf("true") : printf("false");

    return 0;
}