#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct TreeNode
{
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};


bool isSameTree(struct TreeNode* p, struct TreeNode* q){
    if(p && q){
        if(p->val != q->val){       // 根节点的值不相同，则树不相同
            return false;
        }
        else{       // 注意这里的递归（分治法）操作：在上面的条件下，左右子树均相同才算是两棵树相同
            return (isSameTree(p->left, q->left) && isSameTree(p->right, q->right));
        }
    }
    else if(!p && !q){      // 当两棵树的根节点均为空指针时，两棵树是相同的
        return true;
    }
    else{                   // 两棵树中只有一课时是空树时，两棵树结构不同，绝对不相同
        return false;
    }
}
