#include <bits/stdc++.h>
using namespace std;

int n, m;

char s[200][20];
int map_Mask[200];

int mask_table[100], tot;
int dp[110][70][70];

int main ()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
    {
        scanf("%s", s[i] + 1);
        for (int j = 1; j <= m; j++)
            if (s[i][j] == 'H')
                map_Mask[i] |= (1 << (j - 1));
    }
    for (int Mask = 0; Mask < (1 << m); Mask++)
    {
        if (!(Mask & (Mask << 1)) && !(Mask & (Mask << 2)))
            mask_table[++tot] = Mask;
    }
    for (int i = 0; i <= n; i++)
        for (int j = 1; j <= tot; j++)
            for (int k = 1; k <= tot; k++)
                dp[i][j][k] = -100000;
    dp[0][1][1] = 0;
    int ans = 0;
    for (int i = 1; i <= n; i++)
        for (int p1 = 1; p1 <= tot; p1++)
            for (int p2 = 1; p2 <= tot; p2++)
            {
                int mask1 = mask_table[p1], mask2 = mask_table[p2];
                if (dp[i-1][p1][p2] >= 0)
                    for (int cur = 1; cur <= tot; cur++)
                    {
                        int Mask = mask_table[cur];
                        if (!(Mask & map_Mask[i]) && !(Mask & mask1) && !(Mask & mask2))
                        {
                            dp[i][cur][p1] = max(dp[i][cur][p1], dp[i-1][p1][p2] + __builtin_popcount(Mask));
                            ans = max(ans, dp[i][cur][p1]);
                        }
                    }
            }
    printf("%d\n", ans);
    return 0;
}