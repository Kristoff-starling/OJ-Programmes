#include <bits/stdc++.h>
using namespace std;

int n, A, B;
int a[1000];

/* 将每一层楼看作图的一个顶点，从一层楼按一次按钮可以到达另一层楼，
 * 则在两个顶点之间连一条边，这样原问题转化为从A到B最少走多少条边，
 * 可以用 bfs 解决。
 */

int dist[1000]; // 每层楼的最小步数
int q[1000], head, tail;

void update(int cur, int nxt)
{
    if (1 <= nxt && nxt <= n && dist[nxt] == -1)
    {
        dist[nxt] = dist[cur] + 1;
        q[++tail] = nxt;
    }
}

void bfs()
{
    for (int i = 1; i <= n; i++) dist[i] = -1;
    dist[A] = 0;
    q[1] = A; head = tail = 1;
    int cur, nxt;
    while (head <= tail)
    {
        cur = q[head++];
        // go up
        nxt = cur + a[cur];
        update(cur, nxt);
        // go down
        nxt = cur - a[cur];
        update(cur, nxt);
    }
}

int main ()
{
    scanf("%d%d%d", &n, &A, &B);
    for (int i = 1; i <= n; i++) scanf("%d", a + i);
    bfs();
    printf("%d\n", dist[B]);
    return 0;
}