#include <cstdio>
#include <iostream>
#include <set>
#include <unordered_map>
#define Pair pair<int, int>
#define mp make_pair
using namespace std;

int n, m;
int X[1010], Y[1010];
set<int> row, col, d1, d2;
unordered_map<long long, int> cnt;

long long cover = 0;

void check_and_add(int x, int y)
{
    if (1 <= x && x <= n && 1 <= y && y <= n)
    {
        long long ind = 1ll * x * (n + 10) + y;
        cnt[ind]++;
    }
}

int main ()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++)
    {
        int x, y;
        scanf("%d%d", &x, &y);
        row.insert(x); col.insert(y);
        d1.insert(x - y); d2.insert(x + y);
    }
    cover = 1ll * int(row.size()) * n;
    cover += 1ll * int(col.size()) * n;
    for (auto d : d1)
    {
        int k = d;
        cover += n - (k > 0 ? k : -k);
    }
    for (auto s : d2)
    {
        int k = n + 1 - s;
        cover += n - (k > 0 ? k : -k);
    }
    for (auto r : row)
        for (auto c : col)
            check_and_add(r, c);
    for (auto d : d1)
        for (auto s : d2)
        {
            if ((s + d) % 2 == 0)
            {
                int xx = (s + d) / 2, yy = s - xx;
                check_and_add(xx, yy);
            }
        }
    for (auto d : d1)
    {
        for (auto r : row)
        {
            int xx = r, yy = r - d;
            check_and_add(xx, yy);
        }
        for (auto c : col)
        {
            int xx = c + d, yy = c;
            check_and_add(xx, yy);
        }
    }
    for (auto s : d2)
    {
        for (auto r : row)
        {
            int xx = r, yy = s - r;
            check_and_add(xx, yy);
        }
        for (auto c : col)
        {
            int xx = s - c, yy = c;
            check_and_add(xx, yy);
        }
    }
    for (unordered_map<long long, int>::iterator iter = cnt.begin(); iter != cnt.end(); iter++)
    {
        if (iter->second == 1)
            cover -= 1;
        else if (iter->second == 3)
            cover -= 2;
        else if (iter->second == 6)
            cover -= 3;
    }
    printf("%lld\n", 1ll * n * n - cover);
    return 0;
}