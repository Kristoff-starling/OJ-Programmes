#include <bits/stdc++.h>

int n, m;
int a[1000][1000];
char s[1000];

int main ()
{
    int ca, x;
    scanf("%d", &ca);
    while (ca--)
    {
        scanf("%d%d", &n, &m);
        for (int i = 1; i <= n; i++)
        {
            scanf("%s", s + 1);
            for (int j = 1; j <= m; j++)
                a[i][j] = s[j] - '0';
        }
        for (int i = 1; i <= n; i++)
        {
            scanf("%s", s + 1);
            for (int j = 1; j <= m; j++)
            {
                x = s[j] - '0';
                a[i][j] -= x;
                if (a[i][j] < 0)
                    a[i][j] += 3;
            }
        }
        bool f = true;
        for (int i = 1; i <= n; i++)
        {
            int sum = 0;
            for (int j = 1; j <= m; j++)
                sum += a[i][j];
            if (sum % 3 != 0) f = false;
        }
        for (int j = 1; j <= m; j++)
        {
            int sum = 0;
            for (int i = 1; i <= n; i++)
                sum += a[i][j];
            if (sum % 3 != 0) f = false;
        }
        puts(f ? "Yes" : "No");
    }
    return 0;
}