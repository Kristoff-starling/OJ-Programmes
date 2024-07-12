#include <bits/stdc++.h>

const int MAXN = 2e5 + 10;

int n, k, m;
char a[MAXN];

int main ()
{
    int ca; scanf("%d", &ca);
    while (ca--)
    {
        scanf("%d%d%d", &n, &m, &k);
        scanf("%s", a + 1);
        a[0] = a[n + 1] = 'L';
        int cur = 0;
        bool flag = true;
        while (cur != n + 1)
        {
            if (a[cur] == 'C')
            {
                flag = false;
                break;
            }
            else if (a[cur] == 'W')
            {
                if (k == 0)
                {
                    flag = false;
                    break;
                }
                cur++;
                k--;
            }
            else
            {
                bool has_log = false, has_water = false;
                for (int i = 1; i <= m; i++)
                    if (a[cur + i] == 'L')
                    {
                        has_log = true;
                        cur = cur + i;
                        break;
                    }
                if (!has_log)
                {
                    for (int i = m; i >= 1; i--)
                    {
                        if (a[cur + i] == 'W')
                        {
                            has_water = true;
                            cur = cur + i;
                            break;
                        }
                    }
                    if (!has_water)
                    {
                        // consecutive m crocodiles
                        flag = false;
                        break;
                    }
                }
            }
        }
        puts(flag ? "Yes" : "No");
    }
    return 0;
}