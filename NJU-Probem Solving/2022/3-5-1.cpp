#include <bits/stdc++.h>
using namespace std;

const int MAXN = 300 + 10;
const int INF = 1e8;

int n, m, ans;
int dist[MAXN][MAXN], ga[MAXN][MAXN];

int main ()
{
    ios::sync_with_stdio(false);
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            dist[i][j] = ga[i][j] = INF;
    int u, v, c;
    for (int i = 1; i <= m; i++)
    {
        cin >> u >> v >> c;
        ga[u][v] = ga[v][u] = min(ga[u][v], c);
        dist[u][v] = dist[v][u] = min(dist[u][v], c);
    }
    ans = INF;
    for (int k = 1; k <= n; k++)
    {
        for (int i = 1; i <= k - 1; i++)
            for (int j = i + 1; j <= k - 1; j++)
                ans = min(ans, ga[k][i] + dist[i][j] + ga[j][k]);
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
    }
    cout << (ans == INF ? -1 : ans) << '\n';
    return 0;
}