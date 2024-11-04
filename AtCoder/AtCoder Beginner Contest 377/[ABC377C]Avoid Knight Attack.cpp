#include <cstdio>
#include <iostream>
#include <set>
#define Pair pair<int, int>
#define mp make_pair
using namespace std;

int n, m;
set<Pair> cnt;

int dx[] = {-2, -1, 1, 2, 2, 1, -1, -2}, dy[] = {1, 2, 2, 1, -1, -2, -2, -1};

int main ()
{
    scanf("%d%d", &n, &m);
    int x, y;
    for (int i = 1; i <= m; i++)
    {
        scanf("%d%d", &x, &y);
        cnt.insert(mp(x, y));
        for (int dir = 0; dir < 8; dir++)
        {
            int xx = x + dx[dir], yy = y + dy[dir];
            if (1 <= xx && xx <= n && 1 <= yy && yy <= n)
                cnt.insert(mp(xx, yy));
        }
    }
    long long ans = 1ll * n * n - int(cnt.size());
    printf("%lld\n", ans);
    return 0;
}