#include <bits/stdc++.h>
using namespace std;

const int MOD = 998244353;
const int MAXN = 2e4;

long long N; int D;
int fac[MAXN + 48], ifac[MAXN + 48];

int add(int x) { if (x >= MOD) x -= MOD; return x; }
int sub(int x) { if (x < 0) x += MOD; return x; }
void Add(int &x, int y) { x = add(x + y); }
void Sub(int &x, int y) { x = sub(x - y); }

int quick_pow(int x, int y)
{
    int res = 1;
    while (y)
    {
        if (y & 1) res = 1ll * res * x % MOD;
        x = 1ll * x * x % MOD; y >>= 1;
    }
    return res;
}

void init_C()
{
    fac[0] = 1; for (int i = 1; i <= MAXN; i++) fac[i] = 1ll * fac[i-1] * i % MOD;
    ifac[MAXN] = quick_pow(fac[MAXN], MOD - 2);
    for (int i = MAXN - 1; i >= 0; i--) ifac[i] = 1ll * ifac[i+1] * (i+1) % MOD;
}

int C(int x, int y)
{
    if (x < y || y < 0) return 0;
    return 1ll * fac[x] * ifac[y] % MOD * ifac[x - y] % MOD;
}

struct Matrix
{
    int b[3][3], n;
    void init(int _n) { n = _n; }
    void clear() { memset(b, 0, sizeof(b)); }
    void init_I() { clear(); for (int i = 1; i <= n; i++) b[i][i] = 1; }
    Matrix operator * (Matrix other)
    {
        Matrix res; res.init(n); res.clear();
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                for (int k = 1; k <= n; k++)
                    Add(res.b[i][j], 1ll * b[i][k] * other.b[k][j] % MOD);
        return res;
    }
}trans, init;

Matrix quick_pow(Matrix x, long long y)
{
    Matrix res; res.n = x.n; res.init_I();
    while (y)
    {
        if (y & 1) res = res * x;
        x = x * x; y >>= 1;
    }
    return res;
}

int main ()
{
    scanf("%lld%d", &N, &D);
    init_C();
    int ans = 1;
    for (int d = 1; d <= D + 1; d++)
    {
        trans.n = 2;
        trans.b[1][1] = C(D-1, d);   trans.b[1][2] = C(D-1, d-1);
        trans.b[2][1] = C(D-1, d-1); trans.b[2][2] = C(D-1, d-2);
        trans = quick_pow(trans, N-1);
        init.n = 2;
        init.b[1][1] = 1; init.b[2][1] = 0;
        init = trans * init;
        Add(ans, 1ll * init.b[1][1] * C(D-1, d) % MOD);
        Add(ans, 1ll * init.b[2][1] * C(D-1, d-1) % MOD);
        init.b[1][1] = 0; init.b[2][1] = 1;
        init = trans * init;
        Add(ans, 1ll * init.b[1][1] * C(D-1, d-1) % MOD);
        Add(ans, 1ll * init.b[2][1] * C(D-1, d-2) % MOD);
    }
    printf("%d\n", ans);
    return 0;
}