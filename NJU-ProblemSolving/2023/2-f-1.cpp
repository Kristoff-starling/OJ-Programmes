#include <bits/stdc++.h>

const int MAXN = 1005;
const int INF = 1e9;

int n, m;
int a[MAXN][MAXN], dp[MAXN][MAXN];

int main ()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            scanf("%d", &a[i][j]);
    dp[1][1] = a[1][1];
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            if (i != 1 || j != 1)
            {
                dp[i][j] = -INF;
                if (i > 1) dp[i][j] = std::max(dp[i][j], dp[i - 1][j] + a[i][j]);
                if (j > 1) dp[i][j] = std::max(dp[i][j], dp[i][j - 1] + a[i][j]);
            }
    printf("%d\n", dp[n][m]);
    return 0;
}