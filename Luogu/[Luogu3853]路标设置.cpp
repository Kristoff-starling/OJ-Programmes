/*
 * 该问题的最大特点在于: 最大间隔与需要的路标个数之间的关系是单调的，即如果想要达到更小的
 * 最大间隔，我们至少需要用不少于之前的路标。
 * 因此我们可以采用“二分答案”的思路: 通过二分法枚举最大间隔，然后判断是否可行。由于之前
 * 提到的单调性，二分法总能帮我们排除某一侧的所有答案
 * 如果你对二分答案不太了解，可以上网查询相关的资料
 */
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e5 + 10;

int L, n, k;
int a[MAXN];

bool check_valid(int mid)
{
    int cnt = 0;
    for (int i = 1; i <= n - 1; i++)
        cnt += (a[i + 1] - a[i] + mid - 1) / mid - 1;
    // (a + b - 1) / b 等价与 ceil(a / b)
    // 这里采取了贪心的思想: 想要让最大间隔小于等于 mid，我们再 (a[i], a[i+1]) 这个
    // 区间中至少需要额外安放这么多路标
    return cnt <= k;
}

int main ()
{
    scanf("%d%d%d", &L, &n, &k);
    for (int i = 1; i <= n; i++)
        scanf("%d", a + i);
    int l = 1, r = L, mid, ans = L;
    while (l <= r)
    {
        mid = (l + r) >> 1;
        if (check_valid(mid))
        // 如果 mid 可行，那么所有比 mid 大的答案都可行 (因为它们只会花费更少的路标)，
        // 所以我们可以搜索更小的答案
            ans = mid, r = mid - 1;
        else
        // 如果 mid 不可行，那么所有比 mid 小的答案都可行 (因为它们只会花费更多的路标)，
        // 所以我们只能搜索更大的答案
            l = mid + 1;
    }
    printf("%d\n", ans);
    return 0;
}