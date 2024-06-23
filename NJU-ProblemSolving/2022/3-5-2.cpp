#include <bits/stdc++.h>
#define Pair pair<int, int>
#define mp make_pair
using namespace std;

const int MAXN = 3000 + 10;
const int INF = 1e9;

int n, m;
vector<Pair> v[MAXN];
int h[MAXN], dist[MAXN][MAXN];
priority_queue<Pair> q;

bool bellman_ford()
{
    for (int i = 0; i <= n; i++)
        h[i] = 0;
    bool flag;
    for (int i = 0; i <= n; i++)
    {
        flag = false;
        for (int u = 1; u <= n; u++)
        {
            for (auto edge : v[u])
            {
                int to = edge.first, w = edge.second;
                if (h[to] > h[u] + w)
                {
                    h[to] = h[u] + w;
                    flag = true;
                }
            }
        }
        if (!flag) break;
    }
    return flag;
}

void dijkstra(int s)
{
    for (int i = 1; i <= n; i++)
        dist[s][i] = (i == s ? 0 : INF);
    q.push(mp(0, s));
    while (!q.empty())
    {
        int cur = q.top().second, d = -q.top().first;
        q.pop();
        if (d > dist[s][cur]) continue;
        for (auto edge : v[cur])
        {
            int to = edge.first, w = edge.second;
            if (dist[s][to] > dist[s][cur] + w + h[cur] - h[to])
            {
                dist[s][to] = dist[s][cur] + w + h[cur] - h[to];
                q.push(mp(-dist[s][to], to));
            }
        }
    }
}

bool johnson()
{
    if (bellman_ford()) return true;
    for (int s = 1; s <= n; s++)
    {
        dijkstra(s);
        for (int i = 1; i <= n; i++)
            if (dist[s][i] < INF)
                dist[s][i] = dist[s][i] - h[s] + h[i];
    }
    return false;
}

int main ()
{
    ios::sync_with_stdio(false);
    cin >> n >> m;
    int x, y, c;
    for (int i = 1; i <= m; i++)
    {
        cin >> x >> y >> c;
        v[x].push_back(mp(y, c));
    }
    for (int i = 1; i <= n; i++)
        v[0].push_back(mp(i, 0));
    if (johnson())
        cout << -1 << '\n';
    else
    {
        for (int i = 1; i <= n; i++)
        {
            long long ans = 0;
            for (int j = 1; j <= n; j++)
                ans += 1ll * j * dist[i][j];
            cout << ans << '\n';
        }
    }
    return 0;
}