#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e6 + 10;

int n, m;
vector<int> v[MAXN];
int deg[MAXN], ans[MAXN], pt;

struct edge_hash
{
    unordered_map<long long, int> s;
    long long id(int x, int y)
    {
        if (x > y) swap(x, y);
        return 1ll * x * (n + 10) + y;
    }
    void add(int x, int y)
    {
        s[id(x, y)]++;
    }
    void remove(int x, int y)
    {
        s[id(x, y)]--;
    }
    bool find(int x, int y)
    {
        return s[id(x, y)] != 0;
    }
}h;

void dfs(int cur)
{
    while (!v[cur].empty())
    {
        int to = v[cur].back();
        if (h.find(cur, to))
        {
            h.remove(cur, to);
            dfs(to);
        }
        else
            v[cur].pop_back();
    }
    ans[++pt] = cur;
}

int main ()
{
    ios::sync_with_stdio(false);
    cin >> n >> m;
    int x, y, odd_cnt = 0, start = 1;
    for (int i = 1; i <= m; i++)
    {
        cin >> x >> y;
        v[x].push_back(y); deg[y]++;
        v[y].push_back(x); deg[x]++;
        h.add(x, y);
    }
    for (int i = 1; i <= n; i++)
        if (deg[i] & 1)
            odd_cnt++, start = i;
    if (odd_cnt == 0 || odd_cnt == 2)
    {
        puts("YES");
        dfs(start);
        for (int i = 1; i <= m + 1; i++)
            printf("%d ", ans[i]);
        puts("");
    }
    else puts("NO");
    return 0;
}