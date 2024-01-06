#include <bits/stdc++.h>
using namespace std;

const int MAXN = 3e5 + 10;

int n, X, Y;
vector<int> v[MAXN];
int sz[MAXN], fa[MAXN];

void dfs(int cur, int father)
{
    sz[cur] = 1;
    fa[cur] = father;
    for (auto y : v[cur])
        if (y != father)
        {
            dfs(y, cur);
            sz[cur] += sz[y];
        }
}

int main () {
    ios::sync_with_stdio(false);
    cin >> n >> X >> Y;
    int x, y;
    for (int i = 1; i <= n - 1; i++)
    {
        cin >> x >> y;
        v[x].push_back(y);
        v[y].push_back(x);
    }
    dfs(X, 0);
    int u = Y;
    while (fa[u] != X)
        u = fa[u];
    cout << 1ll * n * (n - 1) - 1ll * sz[Y] * (n - sz[u]) << endl;
    return 0;
}