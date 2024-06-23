#include <bits/stdc++.h>
using namespace std;

const int MAXN = 10010;
const int MAXM = 200010;

int n, m;

struct Edge
{
    int x, y, c;
    bool operator < (const Edge &other) const { return c > other.c; }
    void input() { cin >> x >> y >> c; }
}edge[MAXM];

namespace DSU
{
    int pre[MAXN];
    void init()
    {
        for (int i = 1; i <= n; i++)
            pre[i] = i;
    }
    int find_anc(int x)
    {
        if (pre[x] != x) pre[x] = find_anc(pre[x]);
        return pre[x];
    }
    bool issame(int x, int y)
    {
        return find_anc(x) == find_anc(y);
    }
    void update(int x, int y)
    {
        x = find_anc(x); y = find_anc(y);
        pre[x] = y;
    }
}

int main ()
{
    ios::sync_with_stdio(false);
    cin >> n >> m;
    for (int i = 1; i <= m; i++)
        edge[i].input();
    sort(edge + 1, edge + m + 1); 
    DSU::init();
    int cnt = 0, ans = 0;
    for (int i = 1; i <= m && cnt < n - 1; i++)
        if (!DSU::issame(edge[i].x, edge[i].y))
        {
            cnt++;
            ans += edge[i].c;
            DSU::update(edge[i].x, edge[i].y);
        }
    cout << ans << '\n';
    return 0;
}