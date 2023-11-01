#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e5 + 10;

int n;

int w[MAXN];
vector<int> v[MAXN];

int dp[MAXN][2], deg[MAXN];

void dfs(int cur)
{
    int sum1 = 0, sum2 = 0;
    for (int son : v[cur])
    {
        dfs(son);
        sum1 += dp[son][0];
        sum2 += max(dp[son][0], dp[son][1]);
    }
    dp[cur][0] = sum2;
    dp[cur][1] = w[cur] + sum1;
}

int main ()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", w + i);
    int x, y;
    for (int i = 1; i <= n - 1; i++)
    {
        scanf("%d%d", &x, &y);
        v[y].push_back(x);
        deg[x]++;
    }
    int root = 1;
    for (int i = 1; i <= n; i++)
        if (deg[i] == 0) { root = i; break; }
    dfs(root);
    printf("%d\n", max(dp[root][0], dp[root][1]));
    return 0;
}