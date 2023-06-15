#include <bits/stdc++.h>
using namespace std;

const int MAXN = 310;

int n;

double dp[MAXN][MAXN][MAXN]; // #1, #2, #3

double solve(int c1, int c2, int c3)
{
    if (c1 == 0 && c2 == 0 && c3 == 0) return 0;
    if (c1 < 0 || c2 < 0 || c3 < 0) return 0;
    if (dp[c1][c2][c3] != -1) return dp[c1][c2][c3];
    dp[c1][c2][c3] = (
        (1.0 * c1 / n) * solve(c1 - 1, c2, c3) +
        (1.0 * c2 / n) * solve(c1 + 1, c2 - 1, c3) +
        (1.0 * c3 / n) * solve(c1, c2 + 1, c3 - 1) +
        1
    ) / (c1 + c2 + c3) * n;
    return dp[c1][c2][c3];
}

int main ()
{
    scanf("%d", &n);
    int c1 = 0, c2 = 0, c3 = 0, x;
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &x);
        switch(x)
        {
            case 1: c1++; break;
            case 2: c2++; break;
            case 3: c3++; break;
            default: assert(0);
        }
    }
    for (int i = 0; i <= n; i++)
        for (int j = 0; j <= n; j++)
            for (int k = 0; k <= n; k++)
                dp[i][j][k] = -1;
    printf("%.9lf\n", solve(c1, c2, c3));
    return 0;
}