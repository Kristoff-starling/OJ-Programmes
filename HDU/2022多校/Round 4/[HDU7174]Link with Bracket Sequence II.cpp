#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;
const int MAXN = 500;

int add(int x) {if (x >= MOD) x -= MOD; return x;}
int sub(int x) {if (x < 0) x += MOD; return x;}
void Add(int &x, int y) {x = add(x + y);}
void Sub(int &x, int y) {x = sub(x - y);}

int n, m;
int a[MAXN + 48], f[MAXN + 48][MAXN + 48], g[MAXN + 48][MAXN + 48];

int solve1(int l, int r);

int solve2(int l, int r)
{
    if (l > r) return 1;
    if (g[l][r] != -1) return g[l][r];
    g[l][r] = 0;
    if (a[l] == 0 && a[r] == 0) Add(g[l][r], 1ll * m * solve1(l + 1, r - 1) % MOD);
    if (a[l] == 0 && a[r] < 0) Add(g[l][r], solve1(l + 1, r - 1));
    if (a[r] == 0 && a[l] > 0) Add(g[l][r], solve1(l + 1, r - 1));
    if (a[l] > 0 && a[l] + a[r] == 0) Add(g[l][r], solve1(l + 1, r - 1));
    return g[l][r];
}

int solve1(int l, int r)
{
    if (l > r) return 1;
    if (f[l][r] != -1) return f[l][r];
    f[l][r] = 0;
    // case 1: 1 segment
    Add(f[l][r], solve2(l, r));
    // case 2: 2 segments
    for (int rr = l + 1; rr < r; rr += 2) Add(f[l][r], 1ll * solve2(l, rr) * solve1(rr + 1, r) % MOD);
    return f[l][r];
}

int main ()
{
    int ca; scanf("%d", &ca);
    while (ca--)
    {
        scanf("%d%d", &n, &m);
        for (int i = 1; i <= n; i++) scanf("%d", a + i);
        if (n & 1) {puts("0"); continue;}
        for (int i = 1; i <= n; i++) for (int j = i; j <= n; j++) f[i][j] = g[i][j] = -1;
        printf("%d\n", solve1(1, n));
    }
    return 0;
}