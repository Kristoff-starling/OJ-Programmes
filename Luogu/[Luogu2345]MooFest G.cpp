#include <bits/stdc++.h>
#define LL long long
using namespace std;

const int MAXN = 1e5;

int n;

struct cow
{
    int pos, vol;
    void input() { scanf("%d%d", &vol, &pos); }
}a[MAXN + 48];

bool cmp_pos(cow x, cow y) {return x.pos < y.pos;}
bool cmp_vol(cow x, cow y) {return x.vol < y.vol;}

LL ans = 0;

void solve(int l, int r)
{
    if (l == r) return;
    int mid = (l + r) >> 1;
    solve(l, mid); solve(mid + 1, r);
    /*
     * 左侧的每头牛只需要处理右侧 vol 比它小的牛的答案
     * 右侧的每头牛只需要处理左侧 vol 比它小的牛的答案
     * 根据 vol 按照类似归并排序的顺序处理这些牛
     */
    sort(a + l, a + mid + 1, cmp_vol);
    sort(a + mid + 1, a + r + 1, cmp_vol);
    int lcnt = 0, rcnt = 0; LL lsum = 0, rsum = 0;
    int lpt = l, rpt = mid + 1;
    while (lpt <= mid  && rpt <= r)
        if (a[lpt].vol <= a[rpt].vol)
        {
            ans += 1ll * a[lpt].vol * (rsum - 1ll * a[lpt].pos * rcnt);
            lcnt++; lsum += a[lpt].pos; lpt++;
        }
        else
        {
            ans += 1ll * a[rpt].vol * (1ll * a[rpt].pos * lcnt - lsum);
            rcnt++; rsum += a[rpt].pos; rpt++;
        }
    while (lpt <= mid) ans += 1ll * a[lpt].vol * (rsum - 1ll * a[lpt].pos * rcnt), lpt++;
    while (rpt <= r) ans += 1ll * a[rpt].vol * (1ll * a[rpt].pos * lcnt - lsum), rpt++;
}

int main ()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) a[i].input();
    sort(a + 1, a + n + 1, cmp_pos);
    solve(1, n);
    printf("%lld\n", ans);
    return 0;
}