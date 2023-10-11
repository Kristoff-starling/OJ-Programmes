#include <bits/stdc++.h>
using namespace std;

const int MAXN = 2e5 + 10;

int n, m, st;
unordered_set<int> v[MAXN];
int q[MAXN], head, tail;
int dist[MAXN];
unordered_set<int> unreachable;

void solve()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) v[i].clear();
    int x, y;
    for (int i = 1; i <= m; i++)
    {
        scanf("%d%d", &x, &y);
        v[x].insert(y);
        v[y].insert(x);
    }
    scanf("%d", &st);
    unreachable.clear();
    for (int i = 1; i <= n; i++)
    {
        dist[i] = (i == st ? 0 : -1);
        if (i != st)
            unreachable.insert(i);
    }
    head = tail = 1; q[1] = st;
    while (head <= tail)
    {
        int cur = q[head++];
        for (auto iter = unreachable.begin(); iter != unreachable.end(); )
        {
            int to = *iter;
            if (v[cur].find(to) == v[cur].end())
            {
                dist[to] = dist[cur] + 1;
                q[++tail] = to;
                iter = unreachable.erase(iter);
            }
            else { ++iter; }
        }
    }
    for (int i = 1; i <= n; i++)
        if (i != st)
            printf("%d ", dist[i]);
    puts("");
}

int main ()
{
    int ca;
    scanf("%d", &ca);
    while (ca--) solve();
    return 0;
}