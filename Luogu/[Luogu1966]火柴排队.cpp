/*
 * 本题要求最小化 \sigma (a_i - b_i) ^ 2
 * 将括号展开: (a_i - b_i) ^ 2 = a_i ^ 2 - 2 * a_i * b_i + b_i ^ 2
 * 容易发现 \sigma (a_i ^ 2 + b_i ^ 2) 不会随着交换发生变化，所以我们最大化
 * \sigma (a_i * b_i)
 * 根据排序不等式 (顺序和 \geq 乱序和 \geq 逆序和)，我们应当让 {a} 和 {b} 中
 * 排名相同的数处在相同位置。如果将 a, b 离散化，即转化为需要多少次交换可以让 {a}
 * 和 {b} 相同
 * 这是一个经典问题，使用分治法求逆序对即可.
 * 
 * 如果你仍然有疑惑，可以上网搜索排序不等式的证明、分治法求逆序对的原理、或者其他题解.
 */
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100010;
const int MOD = 1e8 - 3;

int n;
int a[MAXN], b[MAXN];
int pos[MAXN];
long long ans = 0;

/*
 * normalize() 函数完成一个数列的离散化，即将每个数替换成
 * 它在原数组中的排名。该操作在不影响数之间大小关系的情况下，
 * 将值域映射到了 [1,n]。
 * 
 * 下面是一种非常简洁的离散化写法。离散化是一种常见的技巧，
 * 如果你暂时无法理解，请上网查询 lower_bound() 函数的含义。
 */
int val[MAXN];
void normalize(int arr[])
{
    for (int i = 1; i <= n; i++)
        val[i] = arr[i];
    sort(val + 1, val + n + 1);
    for (int i = 1; i <= n; i++)
        arr[i] = lower_bound(val + 1, val + n + 1, arr[i]) - val;
}

// 分治法求逆序对数目
int tmp[MAXN];
void mergesort(int l, int r)
{
    if (l == r) return;
    int mid = (l + r) >> 1;
    mergesort(l, mid); mergesort(mid + 1, r);
    int lpt = l, rpt = mid + 1, pt = l;
    while (lpt <= mid && rpt <= r)
        if (b[lpt] < b[rpt])
        {
            tmp[pt] = b[lpt];
            lpt++; pt++;
            ans += rpt - mid - 1; // 所有处于右区间的比 b[lpt] 小的数都与 b[lpt] 构成逆序对
        }
        else
        {
            tmp[pt] = b[rpt];
            rpt++; pt++;
        }
    while (lpt <= mid) tmp[pt] = b[lpt], lpt++, pt++, ans += rpt - mid - 1;
    while (rpt <= r) tmp[pt] = b[rpt], rpt++, pt++;
    for (int i = l; i <= r; i++) b[i] = tmp[i];
}

int main ()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", a + i); // 注意scanf也支持通过这种写法进行数组读入
    for (int i = 1; i <= n; i++)
        scanf("%d", b + i);
    normalize(a); normalize(b);
    for (int i = 1; i <= n; i++) pos[a[i]] = i;
    for (int i = 1; i <= n; i++)
        b[i] = pos[b[i]];
    mergesort(1, n);
    printf("%lld\n", ans % MOD);
    return 0;
}