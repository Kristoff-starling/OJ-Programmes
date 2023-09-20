#include <bits/stdc++.h>
#define LOWBIT(x) ((x) & (-x))
using namespace std;

const int MAXN = 5e5;

int n;
int a[MAXN + 48];

struct node
{
    int val, pos;
    bool operator < (const node &other) const { return val > other.val; }
}b[MAXN + 48];

namespace BIT
{
    int c[MAXN + 48];
    void update(int x) {while (x <= n) c[x] ++, x += LOWBIT(x);}
    int query(int x) {int res = 0; while (x) res += c[x], x ^= LOWBIT(x); return res;}
}

int main ()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", a + i), b[i].pos = i, b[i].val = a[i];
    sort(b + 1, b + n + 1);
    long long ans = 0; int ptr = 1;
    for (int i = 1; i <= n; i++)
    {
        while (ptr <= n && b[ptr].val == b[i].val) BIT::update(b[ptr].pos), ptr++;
        int p = b[i].pos, num = BIT::query(p - 1);
        int L = p - 1 - num, R = n - p - (ptr - 2 - num);
        ans += 1ll * L * R;
    }
    printf("%lld\n", ans);
    return 0;
}