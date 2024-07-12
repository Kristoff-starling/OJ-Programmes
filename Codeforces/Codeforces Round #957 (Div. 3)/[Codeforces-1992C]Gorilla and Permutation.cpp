#include <bits/stdc++.h>

int main ()
{
    int ca; scanf("%d", &ca);
    int n, m, k;
    while (ca--)
    {
        scanf("%d%d%d", &n, &m, &k);
        for (int i = n; i >= m + 1; i--)
            printf("%d ", i);
        for (int i = 1; i <= m; i++)
            printf("%d ", i);
        puts("");
    }
    return 0;
}