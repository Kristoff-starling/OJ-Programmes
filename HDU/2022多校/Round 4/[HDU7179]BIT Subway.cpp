#include <bits/stdc++.h>
#define LL long long
using namespace std;

const int MAXN = 1e5;

int n; LL a[MAXN + 48];

int main ()
{
    int ca; scanf("%d", &ca);
    while (ca--)
    {
        scanf("%d", &n);
        for (int i = 1; i <= n; i++) scanf("%lld", a + i), a[i] *= 1000;
        LL ans1 = 0, ans2 = 0;
        for (int i = 1; i <= n; i++)
        {
            if (ans2 < 100000) ans2 += a[i];
            else if (ans2 < 200000) ans2 += a[i] / 5 * 4;
            else ans2 += a[i] / 2;
        }
        for (int i = 1; i <= n; i++)
            if (ans1 < 100000)
            {
                if (ans1 + a[i] > 100000) a[i] -= (100000 - ans1), ans1 = 100000, i--;
                else ans1 += a[i];
            }
            else if (ans1 < 200000)
            {
                if (ans1 + a[i] / 5 * 4> 200000) ans1 = 200000 + (a[i] - (200000 - ans1) / 4 * 5) / 2;
                else ans1 += a[i] / 5 * 4;
            }
            else ans1 += a[i] / 2;
        double a1 = ans1, a2 = ans2; a1 /= 1000; a2 /= 1000;
        printf("%.3lf %.3lf\n", a1, a2);
    }
    return 0;
}