#include <bits/stdc++.h>
using namespace std;

const int MAXN = 5e5;

int n, q, a[MAXN + 48];

namespace SegmentTree
{
    long long sum[MAXN << 2]; int val[MAXN << 2];
    #define lson(cur) ((cur) << 1)
    #define rson(cur) ((cur) << 1 | 1)
    void pushup(int cur, int l, int r)
    {
        sum[cur] = sum[lson(cur)] + sum[rson(cur)];
        val[cur] = (val[lson(cur)] == val[rson(cur)]) ? val[lson(cur)] : -1;
    }
    void pushdown(int cur, int l, int r)
    {
        if (val[cur] >= 0)
        {
            int mid = (l + r) >> 1;
            val[lson(cur)] = val[cur]; sum[lson(cur)] = 1ll * val[cur] * (mid - l + 1);
            val[rson(cur)] = val[cur]; sum[rson(cur)] = 1ll * val[cur] * (r - mid);
        }
    }
    void build(int cur, int l, int r)
    {
        if (l == r) { val[cur] = sum[cur] = a[l]; return; }
        int mid = (l + r) >> 1;
        build(lson(cur), l, mid);
        build(rson(cur), mid + 1, r);
        pushup(cur, l, r);
    }
    void modify1(int cur, int left, int right, int x, int l, int r)
    {
        if (val[cur] == 0) return;
        if (left <= l && r <= right && val[cur] != -1)
        {
            val[cur] /= x;
            sum[cur] = 1ll * val[cur] * (r - l + 1);
            return;
        }
        int mid = (l + r) >> 1;
        pushdown(cur, l, r);
        if (left <= mid) modify1(lson(cur), left, right, x, l, mid);
        if (mid + 1 <= right) modify1(rson(cur), left, right, x, mid + 1, r);
        pushup(cur, l, r);
    }
    void modify2(int cur, int left, int right, int x, int l, int r)
    {
        if (left <= l && r <= right)
        {
            val[cur] = x;
            sum[cur] = 1ll * val[cur] * (r - l + 1);
            return;
        }
        int mid = (l + r) >> 1;
        pushdown(cur, l, r);
        if (left <= mid) modify2(lson(cur), left, right, x, l, mid);
        if (mid + 1 <= right) modify2(rson(cur), left, right, x, mid + 1, r);
        pushup(cur, l, r);
    }
    long long query(int cur, int left, int right, int l, int r)
    {
        if (left <= l && r <= right) return sum[cur];
        long long res = 0;
        int mid = (l + r) >> 1;
        pushdown(cur, l, r);
        if (left <= mid) res += query(lson(cur), left, right, l, mid);
        if (mid + 1 <= right) res += query(rson(cur), left, right, mid + 1, r);
        pushup(cur, l, r);
        return res;
    }
}

int main ()
{
    int op, l, r, x;
    scanf("%d%d", &n, &q); for (int i = 1; i <= n; i++) scanf("%d", a + i);
    SegmentTree::build(1, 1, n);
    while (q--)
    {
        scanf("%d%d%d", &op, &l, &r);
        switch(op)
        {
            case 1:
                scanf("%d", &x);
                SegmentTree::modify1(1, l, r, x, 1, n);
                break;
            case 2:
                scanf("%d", &x);
                SegmentTree::modify2(1, l, r, x, 1, n);
                break;
            case 3:
                printf("%lld\n", SegmentTree::query(1, l, r, 1, n));
                break;
        }
    }
    return 0;
}
