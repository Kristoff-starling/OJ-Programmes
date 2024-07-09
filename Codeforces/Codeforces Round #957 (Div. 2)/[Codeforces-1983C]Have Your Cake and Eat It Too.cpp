#include <bits/stdc++.h>

const int MAXN = 2e5 + 10;

int n;
int a[MAXN], b[MAXN], c[MAXN];
int la, ra, lb, rb, lc, rc;
long long tot;

void cl(int A[], int &l)
{
    long long sum = 0; int pt = 0;
    while (sum < tot)
        sum += A[++pt];
    l = pt;
}

void cr(int A[], int &r)
{
    long long sum = 0; int pt = n + 1;
    while (sum < tot)
        sum += A[--pt];
    r = pt;
}

bool check_sum(int A[], int l, int r)
{
    long long sum = 0;
    if (l > r) return false;
    for (int i = l; i <= r; i++)
        sum += A[i];
    return sum >= tot;
}

int main ()
{
    int ca;
    scanf("%d", &ca);
    while (ca--)
    {
        scanf("%d", &n);
        tot = 0;
        for (int i = 1; i <= n; i++)
        {
            scanf("%d", a + i);
            tot += a[i];
        }
        for (int i = 1; i <= n; i++)
            scanf("%d", b + i);
        for (int i = 1; i <= n; i++)
            scanf("%d", c + i);
        tot = (tot + 2) / 3;
        cl(a, la); cl(b, lb); cl(c, lc);
        cr(a, ra); cr(b, rb); cr(c, rc);
        // A B C
        if (check_sum(b, la + 1, rc - 1))
        {
            printf("%d %d %d %d %d %d\n", 1, la, la + 1, rc - 1, rc, n);
            continue;
        }
        // A C B
        if (check_sum(c, la + 1, rb - 1))
        {
            printf("%d %d %d %d %d %d\n", 1, la, rb, n, la + 1, rb - 1);
            continue;
        }
        // B A C
        if (check_sum(a, lb + 1, rc - 1))
        {
            printf("%d %d %d %d %d %d\n", lb + 1, rc - 1, 1, lb, rc, n);
            continue;
        }
        // B C A
        if (check_sum(c, lb + 1, ra - 1))
        {
            printf("%d %d %d %d %d %d\n", ra, n, 1, lb, lb + 1, ra - 1);
            continue;
        }
        // C A B
        if (check_sum(a, lc + 1, rb - 1))
        {
            printf("%d %d %d %d %d %d\n", lc + 1, rb - 1, rb, n, 1, lc);
            continue;
        }
        // C B A
        if (check_sum(b, lc + 1, ra - 1))
        {
            printf("%d %d %d %d %d %d\n", ra, n, lc + 1, ra - 1, 1, lc);
            continue;
        }
        puts("-1");
    }
    return 0;
}