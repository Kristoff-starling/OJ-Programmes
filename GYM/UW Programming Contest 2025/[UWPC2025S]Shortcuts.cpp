#include <cstdio>
#include <iostream>
#include <vector>
#include <cstring>
#define ull unsigned long long
using namespace std;


const int p1 = 31, p2 = 97;
const int m1 = 998244353, m2 = 1e9 + 7;

int n, q;
char s1[30][30], s2[30][30];
int L[30], ll[30];
int hsh1[30], hsh2[30], h1[100010], h2[100010], pw1[100010], pw2[100010];
char s[100010];
vector<int> sc[100010];
int dp[100010], sol[100010];

ull query_hash1(int l, int r)
{
    return (h1[r] - 1ll * h1[l - 1] * pw1[r - l + 1] % m1 + m1) % m1;
}

ull query_hash2(int l, int r)
{
    return (h2[r] - 1ll * h2[l - 1] * pw2[r - l + 1] % m2 + m2) % m2;
}

void print_sol(int pos)
{
    char tmps[10];
    if (pos == 0)
        return;
    if (sol[pos] == 0)
    {
        print_sol(pos - 1);
        tmps[0] = s[pos];
        tmps[1] = 0;
        printf("%s", tmps);
    }
    else
    {
        int lastpos = pos - L[sol[pos]];
        print_sol(lastpos);
        printf("%s", s1[sol[pos]] + 1);
        tmps[0] = 'A' + sol[pos] - 1;
        tmps[1] = 0;
        printf("%s", tmps);
    }
}

int main ()
{
    // freopen("s.in", "r", stdin);
    scanf("%d%d", &n, &q);
    for (int i = 1; i <= n; i++)
    {
        scanf("%s%s", s1[i] + 1, s2[i] + 1);
        ll[i] = strlen(s1[i] + 1);
        L[i] = strlen(s2[i] + 1);
        hsh1[i] = hsh2[i] = 0;
        for (int j = 1; j <= L[i]; j++)
        {
            hsh1[i] = (1ll * hsh1[i] * p1 % m1 + s2[i][j]) % m1;
            hsh2[i] = (1ll * hsh2[i] * p2 % m2 + s2[i][j]) % m2;
        }
    }
    pw1[0] = pw2[0] = 1;
    for (int i = 1; i <= 50000; i++)
    {
        pw1[i] = 1ll * pw1[i - 1] * p1 % m1;
        pw2[i] = 1ll * pw2[i - 1] * p2 % m2;
    }
    while (q--)
    {
        scanf("%s", s + 1);
        int l = strlen(s + 1);
        for (int i = 1; i <= l; i++)
            sc[i].clear();
        h1[0] = h2[0] = 0;
        for (int i = 1; i <= l; i++)
        {
            h1[i] = (1ll * h1[i - 1] * p1 % m1 + s[i]) % m1;
            h2[i] = (1ll * h2[i - 1] * p2 % m2 + s[i]) % m2;
        }
        for (int id = 1; id <= n; id++)
            for (int i = 1; i <= l - L[id] + 1; i++)
            {
                if (query_hash1(i, i + L[id] - 1) == hsh1[id] && query_hash2(i, i + L[id] - 1) == hsh2[id])
                {
                    sc[i + L[id] - 1].push_back(id);
                }
            }
        dp[0] = 0;
        for (int i = 1; i <= l; i++)
        {
            dp[i] = dp[i - 1] + 1;
            sol[i] = 0;
            for (auto id : sc[i])
            {
                int pos = i - L[id];
                if (dp[i] > dp[pos] + ll[id] + 1)
                {
                    dp[i] = dp[pos] + ll[id] + 1;
                    sol[i] = id;
                }
            }
        }
        print_sol(l);
        puts("");
    }
    return 0;
}
/*
2 5
omw onmyway
wayn whereareyounow
iamonmyway
iamonmywhereareyounow
whereareyounow
onmyway
applepear
*/