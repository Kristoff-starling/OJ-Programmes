/*
 * 本题的最佳解法应当在线性复杂度内解决问题
 * 本题的核心思想是: 从左往右考虑所有的区间时，如果存在 a_i, a_j 满足 a_i >= a_j 且
 * i < j，那么无论在哪个区间的最小值评选中 a_j 一定比 a_i 优 (因为此时 a_j 已经进入了
 * 我们的视野，且 a_i 一定先退出视野)
 * 所以用单调队列维护一个上升的序列即可，如果你不知道什么是单调队列，可以自行上网搜索教程
 * 学习。
 */
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 2e6 + 100;

int n, m, a[MAXN];

struct QueueNode
{
    int val, pos;
    QueueNode () {}
    QueueNode (int _val, int _pos)
    {
        val = _val;
        pos = _pos;
    } // 结构体的构造函数，用于结构体元素的初始化
};

QueueNode q[MAXN];
int head, tail;

int main ()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        scanf("%d", a + i);
    puts("0");
    head = 1; tail = 0;
    for (int i = 1; i <= n - 1; i++)
    {
        while (head <= tail && q[tail].val >= a[i]) tail--;
        q[++tail] = QueueNode(a[i], i);
        while (q[head].pos < i - m + 1) head++;
        printf("%d\n", q[head].val);
    }
    return 0;
}