#include <bits/stdc++.h>

int main ()
{
    int ca; scanf("%d", &ca);
    while (ca--)
    {
        int n, k, a, maxa = 0;
        scanf("%d%d", &n, &k);
        for (int i = 1; i <= k; i++)
        {
            scanf("%d", &a);
            maxa = std::max(a, maxa);
        }
        printf("%d\n", 2 * (n - maxa) - (k - 1));
    }
    return 0;
}