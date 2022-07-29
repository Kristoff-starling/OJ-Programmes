#include <bits/stdc++.h>
#define LL long long
using namespace std;

const int MAXN = 1e5;

int n;

namespace LinearBase
{
    LL b[60];
    void clear() {for (int i = 0; i < 60; i++) b[i] = 0;}
    void insert(LL x)
    {
        for (int i = 59; i >= 0; i--)
            if (x >> i & 1)
            {
                if (b[i] == 0) {b[i] = x; return;}
                else x ^= b[i];
            }
    }
    LL query()
    {
        LL res = 0;
        for (int i = 59; i >= 0; i--)
            if (((~res) >> i & 1) && b[i] != 0) res ^= b[i];
        return res;
    }
}

int main ()
{
    int ca; scanf("%d", &ca);
    while (ca--)
    {
        scanf("%d", &n); LL x;
        LinearBase::clear();
        for (int i = 1; i <= n; i++) scanf("%lld", &x), LinearBase::insert(x);
        printf("%lld\n", LinearBase::query());
    }
    return 0;
}