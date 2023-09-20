#include <bits/stdc++.h>
#define LOWBIT(x) ((x) & (-x))
using namespace std;

const int MAXN = 2e5;
int a[MAXN + 48], ans = 0, n;
int need[MAXN + 48];

vector<int> point[MAXN + 48];

namespace BIT
{
    int c[MAXN + 48];
    void update(int x, int val) {while (x <= n + 10) c[x] = max(c[x], val), x += LOWBIT(x);}
    int query(int x) {int res = 0; while (x) res = max(res, c[x]), x ^= LOWBIT(x); return res;}
}

int main ()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", a + i), need[i] = i - a[i];
    for (int i = 1; i <= n; i++) if (need[i] >= 0) point[need[i]].push_back(i-1);
    int ans = 0;
    for (int i = 0; i <= n; i++)
    {
        for (auto r : point[i])
        {
            int curans = BIT::query(r - i + 1) + 1;
            ans = max(ans, curans);
            BIT::update(r - i + 2, curans);
        }
    }
    printf("%d\n", ans);
    return 0;
}