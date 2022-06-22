#include <bits/stdc++.h>
#define LOWBIT(x) ((x) & (-x))
using namespace std;

const int MOD = 998244353;
const int MAXN = 2e5;

int add(int x) { if (x >= MOD) x -= MOD; return x; }
int sub(int x) { if (x < 0) x += MOD; return x; }
void Add(int &x, int y) { x = add(x + y); }
void Sub(int &x, int y) { x = sub(x - y); }

int n, q, a[MAXN + 48];

struct BIT
{
    int c[MAXN + 48];
    void init() { memset(c, 0, sizeof(c)); }
    void update(int x, int delta)
    {
        while (x <= n)
        {
            Add(c[x], delta);
            x += LOWBIT(x);
        }
    }
    int query(int x)
    {
        int res = 0;
        while (x)
        {
            Add(res, c[x]);
            x ^= LOWBIT(x);
        }
        return res;
    }
}c1, c2, c3;

int main ()
{
    scanf("%d%d", &n, &q);
    c1.init(); c2.init(); c3.init();
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", a + i);
        c1.update(i, a[i]);
        c2.update(i, 1ll * i * a[i] % MOD);
        c3.update(i, 1ll * i * i % MOD * a[i] % MOD);
    }
    int op, x, v;
    while (q--)
    {
        scanf("%d", &op);
        if (op == 1)
        {
            scanf("%d%d", &x, &v);
            int delta = (v - a[x] + MOD) % MOD; a[x] = v;
            c1.update(x, delta);
            c2.update(x, 1ll * x * delta % MOD);
            c3.update(x, 1ll * x * x % MOD * delta % MOD);
        } 
        else
        {
            scanf("%d", &x);
            int ans1 = (1ll * x * x + 3ll * x + 2) % MOD * c1.query(x) % MOD;
            int ans2 = (1ll * x * 2 + 3 + MOD) % MOD * c2.query(x) % MOD;
            int ans3 = c3.query(x);
            printf("%d\n", 1ll * add(sub(ans1-ans2)+ans3) * ((MOD + 1) >> 1) % MOD);
        }
    }
    return 0;
}