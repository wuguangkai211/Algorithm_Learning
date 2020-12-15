#include <algorithm>
#include <cstdio>
#include <iostream>
using namespace std;

const int MAX_DIM = 3;  // 物品种类总数（解向量维度）为 3
const int DEFAULT = -1; // 默认值

int c = 30; // 背包的最大载重量为 30
int w[] = {16, 15, 15};
int p[] = {45, 25, 25};

// 子集树的通用结点类型
typedef struct Node
{
    int value;
    Node *lchild;
    Node *rchild;
    Node *parent;
} Node, *SuTree;

// 生成 0-1背包问题的回溯树（是一棵子集树）
void InitTree(SuTree &rtree, int deepth)
{
    if (deepth == 0) // 到达最大深度（叶子结点以下），结束生成
        return;
    Node *ln = (Node *)malloc(sizeof(Node)); // 为左右孩子分配空间
    Node *rn = (Node *)malloc(sizeof(Node));
    ln->lchild = ln->rchild = NULL, rn->lchild = rn->rchild = NULL;
    ln->parent = rn->parent = rtree; // 指示双亲节点
    ln->value = rn->value = DEFAULT;
    rtree->lchild = ln, rtree->rchild = rn;
    InitTree(ln, deepth - 1); // 递归创建
    InitTree(rn, deepth - 1);
}

// 回溯
void BackTrack(SuTree &rtree)
{
    if(!rtree->lchild && !rtree->rchild)                // 该节点是叶子节点
    {
        
    }

}

int main()
{
    SuTree rtree = (Node *)malloc(sizeof(Node)); // 回溯树根节点
    rtree->parent = NULL;
    rtree->lchild = rtree->rchild = NULL;
    rtree->value = DEFAULT;
    InitTree(rtree, MAX_DIM); // 初始化回溯树

    BackTrack(rtree);

    return 0;
}
