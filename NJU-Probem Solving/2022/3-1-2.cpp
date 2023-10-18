#include <bits/stdc++.h>
using namespace std;

int n, m;
int deg[2000];

int main ()
{
    ios::sync_with_stdio(false);
    cin >> n >> m;
    int x, y;
    for (int i = 1; i <= m; i++)
    {
        cin >> x >> y;
        deg[y]++;
    }
    int rk1 = 0;
    for (int i = 1; i <= n; i++)
        if (deg[i] == 0)
            if (rk1 == 0)
                rk1 = i;
            else if (rk1 > 0)
                rk1 = -1;
    cout << rk1 << '\n';
    return 0;
}