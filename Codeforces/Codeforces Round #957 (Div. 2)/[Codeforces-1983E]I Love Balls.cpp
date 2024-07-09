#include <bits/stdc++.h>

const int MOD = 1e9 + 7;
const int MAXN = 5e5 + 10;

int quick_pow(int x, int y)
{
    int res = 1;
    while (y)
    {
        if (y & 1)
            res = 1ll * res * x % MOD;
        x = 1ll * x * x % MOD;
        y >>= 1;
    }
    return res;
}

int fac[MAXN], ifac[MAXN], inv[MAXN];

int main ()
{
    fac[0] = 1;
    for (int i = 1; i <= MAXN; i++)
        fac[i] = 1ll * fac[i - 1] * i % MOD;
    ifac[MAXN] = quick_pow(fac[MAXN], MOD - 2);
    for (int i = MAXN - 1; i >= 0; i--)
        ifac[i] = 1ll * ifac[i + 1] * (i + 1) % MOD;
    for (int i = 1; i <= MAXN; i++)
        inv[i] = 1ll * fac[i - 1] * ifac[i] % MOD;
    int ca, n, k, x, sum, sum1, sum2;
    scanf("%d", &ca);
    while (ca--)
    {
        scanf("%d%d", &n, &k);
        sum1 = sum2 = 0;
        for (int i = 1; i <= n; i++)
        {
            scanf("%d", &x);
            if (i <= k) sum1 = (sum1 + x) % MOD; else sum2 = (sum2 + x) % MOD;
        }
        if (k == n)
        {
            printf("%d %d\n", (sum1 + sum2) % MOD, 0);
            continue;
        }
        int num1, num2;
        if ((n - k) & 1)
        {
            num1 = 1ll * k * inv[2] % MOD;
            num2 = (n - k + 1) / 2;
        }
        else
        {
            num1 = 1ll * k * inv[n - k + 1] % MOD * ((n - k) / 2 + 1) % MOD;
            num2 = (n - k) / 2;
        }
        int s1 = (1ll * sum1 * num1 % MOD * inv[k] % MOD + 1ll * sum2 * num2 % MOD * inv[n - k] % MOD) % MOD;
        int s2 = (sum1 + sum2) % MOD - s1;
        if (s2 < 0) s2 += MOD;
        printf("%d %d\n", s1, s2);
    }
    return 0;
}