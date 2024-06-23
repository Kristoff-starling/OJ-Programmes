#include <bits/stdc++.h>

const int MAXN = 1005;
const int INF = 1e9;

int n, m;
int a1[MAXN][MAXN], a2[MAXN][MAXN];
int lu[MAXN][MAXN], ld[MAXN][MAXN], ru[MAXN][MAXN], rd[MAXN][MAXN], sum[MAXN];

void prepare_dp(int a[][MAXN], int dp[][MAXN], int ist, int ied, int jst, int jed)
{
    int n = std::abs(ist - ied), m = std::abs(jst - jed);
    for (int j = 0; j <= m + 1; j++)
        dp[0][j] = dp[n + 1][j] = -INF;
    for (int i = 0; i <= n + 1; i++)
        dp[i][0] = dp[i][m + 1] = -INF;
    int id = (ist < ied ? 1 : -1), jd = (jst < jed ? 1 : -1);
    dp[ist][jst] = a[ist][jst];
    for (int i = ist; i != ied; i += id)
        for (int j = jst; j != jed; j += jd)
            if (i != ist || j != jst)
                dp[i][j] = std::max(dp[i][j - jd], dp[i - id][j]) + a[i][j];
}

int solve(int a[][MAXN], int n, int m)
{
    prepare_dp(a, lu, 1, n + 1, 1, m + 1);
    prepare_dp(a, ld, n, 0, 1, m + 1);
    prepare_dp(a, ru, 1, n + 1, m, 0);
    prepare_dp(a, rd, n, 0, m, 0);
    int ans = -INF;
    for (int i = 1; i <= n; i++)
    {
        int g = -INF;
        sum[0] = 0;
        for (int j = 1; j <= m; j++)
            sum[j] = sum[j - 1] + a[i][j];
        for (int j = m; j >= 1; j--)
        {
            int f = std::max(lu[i - 1][j] + ld[i][j], lu[i][j] + ld[i + 1][j]) - sum[j];
            ans = std::max(ans, f + g);
            g = std::max(g, std::max(ru[i - 1][j] + rd[i][j], ru[i][j] + rd[i + 1][j]) + sum[j - 1]);
        }
    }
    // 特判: 两条路径相交于一点
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
        {
            ans = std::max(ans, lu[i - 1][j] + ld[i][j - 1] + ru[i][j + 1] + rd[i + 1][j] + a[i][j]);
            ans = std::max(ans, lu[i][j - 1] + ld[i + 1][j] + ru[i - 1][j] + rd[i][j + 1] + a[i][j]);
        }
    return ans;
}

int main ()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
        {
            scanf("%d", &a1[i][j]);
            a2[j][i] = a1[i][j];
        }
    printf("%d\n", std::max(solve(a1, n, m), solve(a2, m, n)));
    return 0;
}