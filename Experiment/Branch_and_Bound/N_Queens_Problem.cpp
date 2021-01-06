#include <iostream>
#include <queue>

using namespace std;

class Node
{
public:
    int t;    // 当前已经放置了多少个皇后（对应行号）
    int n;    // 需要放置多少个皇后
    int *pos; // pos[1]代表第 1个皇后所放的列数，所放的行数为 1，这样设置可以不用检查行是否相等

public:
    Node(int n) : t(0), n(n)   
    {
        pos = new int[n + 1];
        for (int i = 0; i <= n; ++i)
        {
            pos[i] = 0;
        }
    }

    Node(const Node &other)
    {
        t = other.t;
        n = other.n;
        pos = new int[other.n + 1];   
        for (int i = 0; i <= n; ++i)
        {
            pos[i] = other.pos[i];
        }
    }

    ~Node()
    {
        if (pos != NULL)
        {
            delete[] pos;
            pos = NULL;
        }
    }         

    bool Legal(int next);           // 判断该放置点是否合法
};

bool Node::Legal(int next)
{
    for (int i = 1; i <= t; i++) //代表已经放置的皇后的行
    {
        int j = pos[i]; //代表已经放置的皇后的列
        if (j == next)  //同列
        {
            return false;
        }
        else if ((next - j) == (i - (t + 1))) //右上角到左下角的对角线
        {
            return false;
        }
        else if ((next - j) == ((t + 1) - i)) //左上角到右下角的对角线
        {
            return false;
        }
    }
    return true;
}

// n皇后问题类型
class Queen
{
private:
    int n;      //皇后数量
public:
    Queen(int x) : n(x){}
    void Solve(); //排列皇后的方式
};

void Queen::Solve()
{
    queue<Node> q;          // 建立普通队列
    Node f(n);              // 建立根节点
    q.push(f);              // 根节点入队
    while (!q.empty())      // 保证队列不为空
    {
        Node x = q.front();
        q.pop();
        if (x.t == n)               // 如果该出队节点已经安置完所有的皇后
        {
            for (int i = 1; i <= n; i++)
            {
                printf("%2d", x.pos[i]);
            }
            printf("\n");
            return;                 // 找到一种可行方案，结束算法
        }
        //一次性将当前节点的所有扩展节点考虑完，符合条件的插入队列
        for (int j = 1; j <= n; j++)
        {
            //利用剪枝函数，将不符合条件的分支切掉
            if (x.Legal(j))
            {
                Node child(x);          // 构造新扩展节点，并拷贝历史位置记录
                child.pos[child.t] = j; //记录新安排的皇后的位置
                ++child.t;              // 新节点的皇后安排数目比原来多 1个
                q.push(child);          // 新节点入队
            }
        }
    }
}

int main()
{
    int n = 5;
    Queen queen(n);
    queen.Solve();
}
