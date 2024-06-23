#include <bits/stdc++.h>
using namespace std;

const int MAXN = 200010;

int n, m, e;
vector<int> v[MAXN];
int linkv[MAXN], choose[MAXN];
int dx[MAXN], dy[MAXN];
int head, tail, q[MAXN << 1];

bool bfs()
{
    head = 1; tail = 0;
    for (int i = 1; i <= n; i++)
    {
        dx[i] = 0;
        if (!choose[i]) q[++tail] = i;
    }
    for (int i = 1; i <= m; i++)
        dy[i] = 0;
    bool flag = false;
    while (head <= tail)
    {
        int cur = q[head++];
        for (auto to : v[cur])
            if (!dy[to])
            {
                dy[to] = dx[cur] + 1;
                if (!linkv[to])
                    flag = true;
                else
                {
                    dx[linkv[to]] = dy[to] + 1;
                    q[++tail] = linkv[to];
                }
            }
    }
    return flag;
}

int find_aug(int cur)
{
    for (auto to : v[cur])
        if (dy[to] == dx[cur] + 1)
        {
            dy[to] = 0;
            if (!linkv[to] || find_aug(linkv[to]))
            {
                linkv[to] = cur;
                choose[cur] = true;
                return 1;
            }
        }
    return 0;
}

int main ()
{
    int x, y;
    scanf("%d%d%d", &n, &m, &e);
    for (int i = 1; i <= e; i++)
    {
        scanf("%d%d", &x, &y);
        v[x].push_back(y);
    }
    int ans = 0;
    while (bfs())
        for (int i = 1; i <= n; i++)
            if (!choose[i])
                ans += find_aug(i);
    printf("%d\n", ans);
    return 0;
}