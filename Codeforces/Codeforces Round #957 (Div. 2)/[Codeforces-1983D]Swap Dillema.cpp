#include <bits/stdc++.h>
#define LOWBIT(x) ((x) & (-x))

const int MAXN = 1e5 + 10;

int n;
int a[MAXN];
std::map<int, int> m;

int c[MAXN];

void init()
{
    for (int i = 1; i <= n; i++) c[i] = 0;
}

void update(int x, int delta)
{
    while (x <= n)
    {
        c[x] += delta;
        x += LOWBIT(x); 
    }
}

int query(int x)
{
    int res = 0;
    while (x)
    {
        res += c[x];
        x ^= LOWBIT(x);
    }
    return res;
}

int main ()
{
    int ca;
    scanf("%d", &ca);
    while (ca--)
    {
        scanf("%d", &n);
        m.clear();
        for (int i = 1; i <= n; i++)
        {
            scanf("%d", a + i);
            m[a[i]] = i;
        }
        bool f = true;
        for (int i = 1; i <= n; i++)
        {
            scanf("%d", a + i);
            if (m.find(a[i]) == m.end())
            {
                f = false;
            }
            a[i] = m[a[i]];
        }
        if (!f)
        {
            puts("No");
            continue;
        }
        init();
        int cnt = 0;
        for (int i = n; i >= 1; i--)
        {
            cnt += (query(a[i]) & 1);
            update(a[i], 1);
        }
        puts((cnt & 1) ? "No" : "Yes");
    }
    return 0;
}