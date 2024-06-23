#include <bits/stdc++.h>
using namespace std;

const int MAXN = 2e5 + 10;

int n, m, st;
unordered_set<int> v[MAXN];
int q[MAXN], head, tail;
int dist[MAXN];
unordered_set<int> unreachable;

int main ()
{
    scanf("%d%d", &n, &m);
    int x, y;
    for (int i = 1; i <= m; i++)
    {
        scanf("%d%d", &x, &y);
        v[x].insert(y);
        v[y].insert(x);
    }
    unreachable.clear();
    dist[1] = 0;
    for (int i = 2; i <= n; i++)
    {
        dist[i] = -1;
        unreachable.insert(i);
    }
    head = tail = 1; q[1] = 1;
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
    for (int i = 2; i <= n; i++)
        printf("%d ", dist[i]);
    puts("");
    return 0;
}