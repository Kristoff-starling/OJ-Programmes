#include <bits/stdc++.h>

const int MOD = 1e9 + 7;
const int MAXN = 5010;

int n;
int c[MAXN][MAXN];

void init_c()
{
    c[0][0] = 1;
    for (int i = 1; i <= 5000; i++)
    {
        c[i][0] = c[i][i] = 1;
        for (int j = 1; j <= i - 1; j++)
            c[i][j] = (c[i - 1][j - 1] + c[i - 1][j]) % MOD;
    }
}

int C(int x, int y)
{
    if (y == 0) return 1;
    if (x < 0 || y < 0 || x < y) return 0;
    return c[x][y];
}

int main ()
{
    int ca; scanf("%d", &ca);
    init_c();
    while (ca--)
    {
        scanf("%d", &n);
        int ans = 0;
        for (int s = 0; s <= n; s++)
            // s is the size of the subset
            // MEX(S, s + 1)
            for (int m = s + 1; m <= n + s + 1; m++)
            {
                // MEX(S, s + 1) = m
                // m - (s + 1) numbers exist in S, and m does not exist in S
                // C(m - 1, m - (s + 1)) * C(n - m, s - m + (s + 1))
                ans = (ans + 1ll * C(std::min(n, m - 1), m - (s + 1)) * C(n - m, s - m + (s + 1)) % MOD * m % MOD) % MOD;
            }
        printf("%d\n", ans);
    }
    return 0;
}