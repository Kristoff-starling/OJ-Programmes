#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e9;

template<typename T> inline void check_max(T &x, T y) { x = x > y ? x : y; }
template<typename T> inline void check_min(T &x, T y) { x = x < y ? x : y; }

int n, m;
int ga[50][50];
int dp[100000][16];

int main ()
{
    ios::sync_with_stdio(false);
    cin >> n >> m;
    int x, y, c;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            ga[i][j] = 200;
    for (int i = 1; i <= m; i++)
    {
        cin >> x >> y >> c;
        int val = min(ga[x - 1][y - 1], c);
        ga[x - 1][y - 1] = ga[y - 1][x - 1] = val;
    }
    for (int Mask = 1; Mask <= (1 << n) - 1; Mask++)
        for (int i = 0; i < n; i++)
            dp[Mask][i] = (Mask == (1 << i) ? 0 : MAXN);
    for (int Mask = 1; Mask <= (1 << n) - 1; Mask++)
        for (int cur = 0; cur < n; cur++)
            for (int nxt = 0; nxt < n; nxt++)
                if ((~Mask & (1 << nxt)) && ga[cur][nxt] > 0)
                    check_min(dp[Mask | (1 << nxt)][nxt], dp[Mask][cur] + ga[cur][nxt]);
    int ans = MAXN; 
    for (int i = 0; i < n; i++)
        check_min(ans, dp[(1 << n) - 1][i]);
    cout << (ans == MAXN ? -1 : ans) << endl;
    return 0;
}