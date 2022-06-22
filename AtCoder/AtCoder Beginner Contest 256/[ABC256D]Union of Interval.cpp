#include <bits/stdc++.h>
using namespace std;

const int MAXN = 2e5;

int n;

struct interval
{
    int l, r;
    bool operator < (const interval &other) const {return l < other.l;}
}a[MAXN + 48];

int main ()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d%d", &a[i].l, &a[i].r);
    sort(a + 1, a + n + 1);
    int L = a[1].l, R = a[1].r;
    for (int i = 2; i <= n; i++)
        if (a[i].l > R)
        {
            printf("%d %d\n", L, R);
            L = a[i].l; R = a[i].r;
        }
        else
            R = max(R, a[i].r);
    printf("%d %d\n", L, R);
    return 0;
}