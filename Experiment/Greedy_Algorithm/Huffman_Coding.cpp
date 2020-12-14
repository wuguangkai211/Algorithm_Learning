#include <algorithm>
#include <iostream>
#include <string>
using namespace std;

// 默认初始化值
const int DEFAULT_I = -1;
const double DEFAULT_D = -1.0;
const double INF = double(0x3f3f3f3f);

// 最大字符数目
const int ALPHA_NUM = 5;

// Huffman 树的结点类型
typedef struct Node
{
    string ch;                  // 结点代表的字符（仅对叶子结点有意义）
    string code;                // 结点的 Huffman 编码
    double weight;              // 该节点的权重
    int lchild, rchild, parent; // 存储指向左右孩子和父节点的数值指针
} Node;

//找权值最小的两个节点 a和 b
void GetMinNode(Node huffTree[], int &a, int &b, const int &n);

// 构造 Huffman 树
void Huff_Create(Node huffTree[], int w[], string ch[]);

// 向 Huffman树的叶子节点中写入 Huffman编码
void Huff_Encode(Node huffTree[]);

// 将给定的 Huffman编码转换成字母序列
string Huff_Decode(Node huffTree[], string s);

int main()
{
    //编码过程
    Node huffTree[2 * ALPHA_NUM]; // 模拟二叉树
    string str[] = {"A", "B", "C", "D", "E"};
    int w[] = {20, 40, 10, 15, 15}; // 存储这五个字母的频数（ 100制）
    Huff_Create(huffTree, w, str);
    Huff_Encode(huffTree);

    //解码过程
    string s;
    cout << "Please enter a huffman code string: ";
    cin >> s;
    cout << Huff_Decode(huffTree, s) << endl;

    return 0;
}

// 找权值最小的两个节点 a和 b
void GetMinNode(Node huffTree[], int &a, int &b, const int &end)
{
    double weight = INF;
    for (int i = 0; i < end; i++)
    {
        if (huffTree[i].parent != DEFAULT_I) //判断节点是否已经选过
            continue;
        else if (huffTree[i].weight < weight)
        {
            weight = huffTree[i].weight;
            a = i;
        }
    }
    weight = INF; //找权值第二小的节点的位置
    for (int i = 0; i < end; i++)
    {
        if (huffTree[i].parent != DEFAULT_I || (i == a)) //排除已经选过的节点和上一步选出的节点
            continue;
        else if (huffTree[i].weight < weight)
        {
            weight = huffTree[i].weight;
            b = i;
        }
    }
    if (huffTree[a].lchild < huffTree[b].lchild) //规定：左孩子小的放左边（让树的左边深一些，符合书写习惯）
    {                                            // 这里的交换并不影响 Huffman算法的正确性，不交换也可以
        swap(a, b);
    }
}

// 构造 Huffman 树
void Huff_Create(Node huffTree[], int w[], string ch[])
{
    for (int i = 0; i < 2 * ALPHA_NUM - 1; i++)
    { // 初始化二叉树结点
        huffTree[i].ch = "";
        huffTree[i].code = "";
        huffTree[i].weight = DEFAULT_D;
        huffTree[i].parent = DEFAULT_I;
        huffTree[i].lchild = DEFAULT_I, huffTree[i].rchild = DEFAULT_I;
    }
    for (int i = 0; i < ALPHA_NUM; i++)
    { // 将参数表中的节点权重信息导入到前 n个节点中
        huffTree[i].ch = ch[i];
        huffTree[i].weight = w[i];
    }
    for (int j = ALPHA_NUM; j < 2 * ALPHA_NUM - 1; j++)
    { // 关键部分（合成父节点）
        int i1 = 0, i2 = 0;
        GetMinNode(huffTree, i1, i2, j);                                //选出两个权值最小的节点 i1、i2
        huffTree[i1].parent = huffTree[i2].parent = j;                  // 两个节点的父节点
        huffTree[j].lchild = i1, huffTree[j].rchild = i2;               // 输入合成节点的左右孩子编号
        huffTree[j].weight = huffTree[i1].weight + huffTree[i2].weight; // 权值等于两个子树之根节点的权值之和
    }
}

// 向 Huffman树的叶子节点中写入 Huffman编码
void Huff_Encode(Node huffTree[])
{
    for (int i = 0; i < ALPHA_NUM; i++) // 前 ALPHA_NUM个节点是叶子节点
    {
        string s = "";
        int j = i;                              // 取出当前的叶子结点（不修改 i)
        while (huffTree[j].parent != DEFAULT_I) //从叶子往上找到根节点
        {
            int k = huffTree[j].parent;  // 获取其上一层父节点的位置
            if (j == huffTree[k].lchild) // 该节点是它的父节点的左孩子
            {
                s = s + "0"; // 左枝记为 0
            }
            else
            {
                s = s + "1"; // 右枝记为 1
            }
            j = k; // 向上移动
        }
        cout << "The huffman code of char \'" << huffTree[i].ch << "\' is: ";
        for (int r = s.size() - 1; r >= 0; r--) // 倒序输出（从根节点到叶子结点的顺序）
        {
            cout << s[r];
            huffTree[i].code += s[r]; //保存该字符的 Huffman编码
        }
        cout << endl;
    }
}

// 将给定的 Huffman编码转换成字母序列
string Huff_Decode(Node huffTree[], string s)
{
    cout << "After decode: ";
    string temp = ""; //  暂存 Huffman编码的一部分
    string str = "";  // 用于保存解码后的字符串
    for (int i = 0; i < s.size(); i++)
    {
        temp += s[i];
        for (int j = 0; j < ALPHA_NUM; j++) // 遍历叶子结点，寻找编码对应的字符
        {
            if (temp == huffTree[j].code)
            {
                str += huffTree[j].ch;
                temp = ""; // 译出一个字母后，清空暂存编码并结束巡查
                break;
            }
        }
    }
    if (temp != "") // 输入非法
    {
        str = "ERROR!";
    }
    return str;
}
