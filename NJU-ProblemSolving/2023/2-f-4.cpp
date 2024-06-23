#include <bits/stdc++.h>

const int MAXN = 5e6 + 10;

int n, ans;
int a[MAXN], mark[MAXN];

int main ()
{
    std::ios::sync_with_stdio(false);
    std::cin >> n;
    for (int i = 1; i <= n; i++)
        std::cin >> a[i];
    for (int i = 1; i <= n; i++)
        mark[i] = 0;
    ans = n;
    int l = 1, r = 1, ldelta = 0, rdelta = 0;
    for (;;)
    {
        while (r < n && a[r] - rdelta <= a[r + 1])
        {
            r++;
            rdelta -= mark[r];
        }
        while (l <= n && a[l] - ldelta == 0)
        {
            l++;
            ldelta -= mark[l];
        }
        if (l > n) break;
        int amount = std::min(a[l] - ldelta, a[r] - rdelta - a[r + 1]);
        ans = std::min(ans, r - l + 1);
        ldelta += amount; rdelta += amount;
        mark[r + 1] += amount;
    }
    std::cout << ans << '\n';
    return 0;
}