#include <bits/stdc++.h>
#define Pair pair<int,int>
using namespace std;

const int MAXN = 5e5;

int n, k, b[MAXN + 48];
vector<int> v[MAXN + 48];

set<int> s[100];

char ga[100][100];

int dist[MAXN + 48];
priority_queue<Pair> q;

void dijkstra()
{
    for (int i = 1; i <= n; i++) dist[i] = 1e9;
    dist[1] = 0;
    q.push(make_pair(0, 1));
    while (!q.empty())
    {
        Pair ele = q.top(); q.pop();
        int d = -ele.first, cur = ele.second;
        if (d != dist[cur]) continue;
        for (auto to : v[cur])
        {
            int c = (to > cur ? to - cur : cur - to);
            if (dist[cur] + c < dist[to])
            {
                dist[to] = dist[cur] + c;
                q.push(make_pair(-dist[to], to));
            }
        }
    }
}

int main ()
{
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; i++) scanf("%d", b + i), s[b[i]].insert(i);
    for (int i = 1; i <= k; i++) scanf("%s", ga[i] + 1);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= k; j++) if (j != b[i] && ga[b[i]][j] == '1')
        {
            set<int>::iterator iter = s[j].lower_bound(i);
            if (iter != s[j].end()) v[i].push_back(*iter);
            if (iter != s[j].begin()) v[i].push_back(*(--iter));
        }
    dijkstra();
    int ans = 1e9;
    for (int i = 2; i <= n; i++) if (b[i] == b[n]) ans = min(ans, dist[i] + n - i);
    if (ans >= 1e9) ans = -1;
    printf("%d\n", ans);
    return 0;
}