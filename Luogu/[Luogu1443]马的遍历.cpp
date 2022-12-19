#include <bits/stdc++.h>
using namespace std;

int n, m, x, y;
int dist[1000][1000];

// 注意这个位移数组的写法，它使得枚举8个方向的移动变得非常简单
int dx[] = {-2, -1, 1, 2, 2, 1, -1, -2}, dy[] = {1, 2, 2, 1, -1, -2, -2, -1};

int q[1000000], head, tail; // 使用队列执行宽度优先搜索
void bfs()
{
    q[1] = x; q[2] = y; head = 1; tail = 2;
    dist[x][y] = 0;
    while (head <= tail)
    {
        int curx = q[head++], cury = q[head++];
        for (int dir = 0; dir < 8; dir++)
        {
            int nxtx = curx + dx[dir], nxty = cury + dy[dir]; // 与位移数组配套的写法
            if (1 <= nxtx && nxtx <= n && 1 <= nxty && nxty <= m && dist[nxtx][nxty] == -1)
            {
                dist[nxtx][nxty] = dist[curx][cury] + 1;
                q[++tail] = nxtx;
                q[++tail] = nxty;
            }
        }
    }
}

int main ()
{
    scanf("%d%d%d%d", &n, &m, &x, &y);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m ;j++)
            dist[i][j] = -1;
    bfs();
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
            printf("%d ", dist[i][j]);
        puts("");
    }
    return 0;
}