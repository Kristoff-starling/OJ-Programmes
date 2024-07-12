#include <bits/stdc++.h>

const int MAXN = 1e5 + 10;

int n, target, N, a[MAXN];
std::unordered_set<int> s, s1;

int main ()
{
    int ca, x; scanf("%d", &ca);
    while (ca--)
    {
        scanf("%d%d", &n, &target);
        int N = 0, ans = 1;
        s.clear(); s.insert(1);
        while (n--)
        {
            scanf("%d", &x);
            if (target % x == 0 && x != 1)
            {
                if (s.find(target / x) != s.end())
                {
                    s.clear(); s.insert(1);
                    ans++;
                }
                s1.clear(); 
                for (std::unordered_set<int>::iterator iter = s.begin(); iter != s.end(); iter++)
                {
                    s1.insert(*iter);
                    if (target % (1ll * x * *iter) == 0)
                        s1.insert(x * *iter);
                }
                s = s1;
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}