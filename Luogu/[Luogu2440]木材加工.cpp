/*
 * 木棒小段长度越长，能切出来的段数就越少
 * 二分答案
 */
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e5 + 10;

int n, k;
int a[MAXN];

bool check(int l)
{
    int cnt = 0;
    for (int i = 1; i <= n; i++)
        cnt += a[i] / l;
    return cnt >= k;
}

int main ()
{
    scanf("%d%d", &n, &k);
    int l = 1, r = 0, mid, ans = 0;
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", a + i);
        r = max(r, a[i]); // 答案的上界是最长木棒的长度
    }
    while (l <= r)
    {
        mid = (l + r) >> 1;
        if (check(mid)) ans = mid, l = mid + 1; else r = mid - 1;
    }
    printf("%d\n", ans);
    return 0;
}