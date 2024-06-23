#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;
const int base = 10005;

template<typename T> inline void check_max(T &x, T y) { x = (x > y ? x : y); }

int n, k;
int v1[110], v2[110];
int dp[110][20100];

int main ()
{
    ios::sync_with_stdio(false);
    cin >> n >> k;
    for (int i = 1; i <= n; i++)
        cin >> v1[i] >> v2[i];
    for (int i = 0; i <= n; i++)
        for (int j = 0; j <= base + base; j++)
            dp[i][j] = -INF;
    dp[0][base] = 0;
    for (int i = 0; i <= n - 1; i++)
    {
        for (int j = 0; j <= base + base; j++)
            if (dp[i][j] >= 0)
            {
                check_max(dp[i + 1][j], dp[i][j]);
                int v = v1[i + 1] - k * v2[i + 1];
                if (0 <= j + v && j + v <= base + base)
                    check_max(dp[i + 1][j + v], dp[i][j] + v1[i + 1] + v2[i + 1]);
            }
    }
    cout << dp[n][base] << '\n';
    return 0;
}