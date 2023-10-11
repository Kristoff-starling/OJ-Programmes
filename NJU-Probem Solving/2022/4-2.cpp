#include <bits/stdc++.h>
using namespace std;

int n;

int black_cnt[3000], white_cnt[3000];

int main ()
{
    ios::sync_with_stdio(false);
    cin >> n; int u, v, c;
    for (int i = 1; i <= n * (n - 1) / 2; i++)
    {
        cin >> u >> v >> c;
        if (c == 0)
            black_cnt[u]++, black_cnt[v]++;
        else
            white_cnt[u]++, white_cnt[v]++;
    }
    long long ans = 0;
    for (int i = 1; i <= n; i++)
        ans += black_cnt[i] * white_cnt[i];
    ans = 1ll * n * (n - 1) * (n - 2) / 6 - ans / 2;
    cout << ans << endl;
    return 0;
}