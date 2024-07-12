#include <bits/stdc++.h>

int n, w, p;
std::vector<std::pair<int, int> > ans;

int getans(int n, int a, int answ)
{
    int res = 0;
    for (int _ = 1; _ <= (answ + w - 1) / w; _++)
        res = res * p + n;
    for (int _ = 1; _ <= (answ + w - 1) / w * w - answ; _++)
        res /= 10;
    return res;
}

int main ()
{
    int ca;
    scanf("%d", &ca);
    while (ca--)
    {
        scanf("%d", &n);
        ans.clear();
        if (1 <= n && n <= 9)
            w = 1;
        else if (10 <= n && n <= 99)
            w = 2;
        else
            w = 3;
        p = 1;
        for (int _ = 1; _ <= w; _++)
            p *= 10;
        for (int a = 1; a <= 10000; a++)
            for (int answ = 1; answ <= 6; answ++)
                if (w * a > answ) 
                {
                    int res = getans(n, a, answ);
                    int b = n * a - res;
                    if (b == w * a - answ)
                        ans.push_back(std::make_pair(a, b));
                }
        printf("%d\n", int(ans.size()));
        for (std::pair<int, int> ab : ans)
            printf("%d %d\n", ab.first, ab.second);
    }
    return 0;
}