#include <cstdio>
#include <iostream>
using namespace std;

const int MAXN = 2e5 + 10;

int n, q;
int a[MAXN << 2];
int minn[MAXN << 2];

void build(int cur, int l, int r)
{
    if (l == r)
    {
        minn[cur] = a[l];
        return;
    }
    int mid = (l + r) >> 1;
    build(cur << 1, l, mid);
    build(cur << 1 | 1, mid + 1, r);
    minn[cur] = min(minn[cur << 1], minn[cur << 1 | 1]);
}

int query(int cur, int ql, int qr, int l, int r)
{
    if (ql <= l && r <= qr)
        return minn[cur];
    int ans = 1e9;
    int mid = (l + r) >> 1;
    if (ql <= mid) ans = min(ans, query(cur << 1, ql, qr, l, mid));
    if (mid + 1 <= qr) ans = min(ans, query(cur << 1 | 1, ql, qr, mid + 1, r));
    return ans;
}

int main ()
{
    scanf("%d%d", &n, &q);
    a[1] = 0; int x;
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &x);
        a[i + 1] = a[i] + x;
    }
    n++;
    int l, r;
    build(1, 1, n);
    while (q--)
    {
        scanf("%d%d", &l, &r);
        l++; r++;
        if (a[l] == a[r] && query(1, l, r, 1, n) == a[l])
            puts("MAYBE");
        else
            puts("NO");
    }
    return 0;
}
/*
10 5
10 -8 9 5 -7 -9 9 -9 -10 10
1 7
6 9
3 6
0 8
8 10
*/