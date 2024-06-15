#include <bits/stdc++.h>

const int MAXN = 1e5 + 10;

int n, ans;
std::map<int, int> m;
int a[MAXN], mark[MAXN], N;

void solve()
{
    a[N + 1] = 0;
    for (int i = 1; i <= N; i++)
        mark[i] = 0;
    int l = 1, r = 1, ldelta = 0, rdelta = 0;
    for (;;)
    {
        while (r < N && a[r] - rdelta <= a[r + 1])
        {
            r++;
            rdelta -= mark[r];
        }
        while (l <= N && a[l] - ldelta == 0)
        {
            l++;
            ldelta -= mark[l];
        }
        if (l > N) break;
        int amount = std::min(a[l] - ldelta, a[r] - rdelta - a[r + 1]);
        ans = std::min(ans, r - l + 1);
        ldelta += amount; rdelta += amount;
        mark[r + 1] += amount;
    }
}

int main ()
{
    std::ios::sync_with_stdio(false);
    std::cin >> n;
    int x;
    for (int i = 1; i <= n; i++)
    {
        std::cin >> x;
        m[x]++;
    }
    ans = n;
    for (std::map<int, int>::iterator l = m.begin(), r = l; l != m.end(); l = r)
    {
        r = std::next(l);
        while (r != m.end() && r->first == std::prev(r)->first + 1)
            ++r;
        N = 0;
        for (std::map<int, int>::iterator tmp = l; tmp != r; tmp++)
            a[++N] = tmp->second;
        solve();
    }
    std::cout << ans << '\n';
    return 0;
}