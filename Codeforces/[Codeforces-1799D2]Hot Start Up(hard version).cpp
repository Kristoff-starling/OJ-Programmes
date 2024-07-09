#include <bits/stdc++.h>
#define LL long long
using namespace std;

const int INF = 1e9;
const int MAXN = 3e5 + 10;

template<typename T> void check_min(T &x, T y) { x = (x < y ? x : y); }

int n, k;

int last[MAXN];
int a[MAXN], cold[MAXN], hot[MAXN];
LL dp[MAXN][2], sum[MAXN];

int main ()
{
    int ca; scanf("%d", &ca);
    while (ca--)
    {
        scanf("%d%d", &n, &k);
        for (int i = 1; i <= n; i++)
            scanf("%d", a + i);
        for (int i = 1; i <= k; i++)
            scanf("%d", cold + i);
        for (int i = 1; i <= k; i++)
            scanf("%d", hot + i);

        dp[0][0] = dp[1][0] = 0;
        for (int i = 1; i <= k; i++) last[i] = 0;
        sum[1] = cold[a[1]];
        for (int i = 2; i <= n; i++)
            sum[i] = sum[i - 1] + (a[i] == a[i - 1] ? hot : cold)[a[i]];
        
        for (int i = 1; i <= n; i++)
        {
            dp[i][0] = dp[i][1] = min(dp[i - 1][0], dp[i - 1][1]) + cold[a[i]];
            if (a[i] == a[i - 1])
                check_min(dp[i][1], min(dp[i - 1][0], dp[i - 1][1]) + hot[a[i]]);
            else if (last[a[i]])
                check_min(dp[i][0], dp[last[a[i]] + 1][0] + sum[i - 1] - sum[last[a[i]] + 1] + hot[a[i]]);
            last[a[i]] = i;
        }

        printf("%lld\n", min(dp[n][0], dp[n][1]));
    }
    return 0;
}