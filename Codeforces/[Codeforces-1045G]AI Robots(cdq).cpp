#include <bits/stdc++.h>
using namespace std;

const int MAXN = 2e5;
const int lim = 1e9;

int n, k;
long long ans = 0;

struct robot
{
    int x, r, q;
    bool operator < (const robot &other) const { return q < other.q; }
}a[MAXN + 48];

namespace SegmentTree
{
    struct node
    {
        int lson, rson, sum;
    }tree[MAXN * 30 + 48]; int tot, root;
    int Create()
    {
        ++tot;
        tree[tot].lson = tree[tot].rson = tree[tot].sum = 0;
        return tot;
    }
    void build()
    {
        tot = 0;
        root = Create();
    }
    void pushup(int cur)
    {
        tree[cur].sum = tree[tree[cur].lson].sum + tree[tree[cur].rson].sum;
    }
    void modify(int &cur, int pos, int delta, int l, int r)
    {
        if (cur == 0) cur = Create();
        if (l == r) {tree[cur].sum += delta; return;}
        int mid = (l + r) >> 1;
        if (pos <= mid)
            modify(tree[cur].lson, pos, delta, l, mid);
        else
            modify(tree[cur].rson, pos, delta, mid + 1, r);
        pushup(cur);
    }
    int query(int cur, int left, int right, int l, int r)
    {
        if (cur == 0) return 0;
        if (left <= l && r <= right) return tree[cur].sum;
        int rt = 0, mid = (l + r) >> 1;
        if (left <= mid) rt += query(tree[cur].lson, left, right, l, mid);
        if (mid + 1 <= right) rt += query(tree[cur].rson, left, right, mid + 1, r);
        return rt;
    }
}

void cdq(int l, int r)
{
    if (l == r) return;
    int mid = (l + r) >> 1, L, R;
    cdq(l, mid); cdq(mid + 1, r);
    sort(a + l, a + mid + 1); sort(a + mid + 1, a + r + 1);
    L = l; R = l - 1;
    SegmentTree::build();
    for (int i = mid + 1; i <= r; i++)
    {
        while (R < mid && a[R+1].q <= a[i].q + k)
        {
            R++;
            SegmentTree::modify(SegmentTree::root, a[R].x, 1, 0, lim);
        }
        while (L <= R && a[L].q < a[i].q - k)
        {
            SegmentTree::modify(SegmentTree::root, a[L].x, -1, 0, lim);
            L++;
        }
        ans += SegmentTree::query(SegmentTree::root, max(a[i].x - a[i].r, 0), min(a[i].x + a[i].r, lim), 0, lim);
    }
}

int main ()
{
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; i++) scanf("%d%d%d", &a[i].x, &a[i].r, &a[i].q);
    sort(a + 1, a + n + 1, [&](const robot &r1, const robot &r2){ return r1.r > r2.r; });
    cdq(1, n);
    printf("%lld\n", ans);
    return 0;
}