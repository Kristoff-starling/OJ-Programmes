#include <bits/stdc++.h>
using namespace std;

const int MAXN = 3e5 + 10;

int n, m;
vector<int> v[MAXN];

int dfn[MAXN], low[MAXN], ind;
bool cut[MAXN];

void tarjan(int cur, int father)
{
    dfn[cur] = low[cur] = ++ind;
    int child_cnt = 0;
    for (auto to : v[cur])
        if (!dfn[to])
        {
            child_cnt++; tarjan(to, cur);
            low[cur] = min(low[cur], low[to]);
            if (low[to] >= dfn[cur])
            if (father && low[to] >= dfn[cur])
                cut[cur] = true;
        }
        else if (to != father)
            low[cur] = min(low[cur], dfn[to]);
    if (!father && child_cnt > 1)
        cut[cur] = true;
}

int main ()
{
    ios::sync_with_stdio(false);
    cin >> n >> m;
    int x, y;
    for (int i = 1; i <= m; i++)
    {
        cin >> x >> y;
        v[x].push_back(y);
        v[y].push_back(x);
    }
    for (int i = 1; i <= n; i++)
        if (!dfn[i])
            tarjan(i, 0);
    int cut_cnt = 0;
    for (int i = 1; i <= n; i++)
        if (cut[i])
            cut_cnt++;
    cout << cut_cnt << '\n';
    for (int i = 1; i <= n; i++)
        if (cut[i])
            cout << i << ' ';
    return 0;
}