#include <cstdio>
#include <iostream>
using namespace std;

const int MAXN = 1e6 + 10;

int fac[MAXN], ifac[MAXN];
int num3[MAXN], c[MAXN], cnt3[MAXN];

int L = 1e6;
char s[MAXN];
int pw[30];

int inv[10];

int main ()
{
    inv[1] = 1;
    inv[2] = 2;
    for (int i = 1; i <= L; i++)
    {
        int num = i;
        num3[i] = 0;
        while (num % 3 == 0)
        {
            num3[i]++;
            num /= 3;
        }
    }
    int q, n;
    scanf("%d", &q);
    pw[0] = 1;
    for (int i = 1; i <= 15; i++)
        pw[i] = pw[i - 1] * 3;
    while (q--)
    {
        scanf("%d", &n);
        scanf("%s", s + 1);
        for (int i = 1; i <= n; i++)
            if (s[i] == 'B')
                s[i] = 0;
            else if (s[i] == 'G')
                s[i] = 1;
            else
                s[i] = 2;
        c[1] = 1; cnt3[1] = 0;
        int cc = 1;
        // C(n - 1, i - 1) = C(n - 1, i - 2) * (n - i + 1) / (i - 1)
        for (int i = 2; i <= n; i++)
        {
            cnt3[i] = cnt3[i - 1] + num3[n - i + 1] - num3[i - 1];
            int aa1 = (n - i + 1) / pw[num3[n - i + 1]], aa2 = (i - 1) / pw[num3[i - 1]];
            cc = 1ll * cc * aa1 % 3 * inv[aa2 % 3] % 3;
            if (cnt3[i] > 0)
            {
                c[i] = 0;
            }
            else
            {
                c[i] = cc;
            }
        }
        int ans = 0;
        for (int i = 1; i <= n; i++)
            if (n & 1)
                ans = (ans - (int)(s[i]) * c[i] % 3 + 3) % 3;
            else
                ans = (ans + (int)(s[i]) * c[i] % 3) % 3;
        ans = (3 - ans) % 3;
        if (ans == 0)
            printf("B");
        else if (ans == 1)
            printf("G");
        else
            printf("R");
    }
    return 0;
}