#include <cstdio>
#include <iostream>
#include <cmath>
using namespace std;

long long bsum[10000010];

long long valid(long long n, long long bb)
{
    if (n % bb != 0) return 0;
    n /= bb;
    long long a = (long long)(sqrt(n));
    if (a * a != n) return 0;
    return a;
}

int main ()
{
    bsum[1] = 1;
    int lim = 2000000;
    for (int i = 2; i <= 2000000; i++)
    {
        long long sq = 1ll * i * i;
        bsum[i] = bsum[i - 1] + sq;
        if (bsum[i] > 1e18)
        {
            lim = i;
            break;
        }
    }
    long long n;
    scanf("%lld", &n);
    long long b = lim;
    while (b > 0)
    {
        long long a = valid(n, bsum[b]);
        if (a > 0)
        {
            puts("YES");
            printf("%lld %lld\n", a, b);
            return 0;
        }
        b--;
    }
    puts("NO");
    return 0;
}