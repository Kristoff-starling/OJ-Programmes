#include <bits/stdc++.h>
using namespace std;

int n;
int cnt[60];             // 每种长度碎片的数量
int min_len, max_len;    // 最短的碎片和最长的碎片

bool dfs(int stickLeft, int currentLength, int targetLength, int pt)
{
    if (stickLeft == 0) // 已经拼出了所有的目标木棍，找到解
        return true; 

    if (currentLength == targetLength) // 拼出一根目标木棍，接着拼下一根
        return dfs(stickLeft - 1, 0, targetLength, max_len);

    if (pt < min_len) return false;

    // 选择下一个使用的碎片长度
    for (int choice = pt; choice >= min_len; choice--)
        if (cnt[choice] > 0 && currentLength + choice <= targetLength)
        {
            cnt[choice]--;
            if (dfs(stickLeft, currentLength + choice, targetLength, choice)) return true;
            cnt[choice]++;
            /*
             * 最小表示法优化
             * 因为 cnt[choice] > 0，所以长度为 choice 的碎片总要被使用
             * 如果把它放进当前木棍无解，那么将他放入后面的木棍肯定也无解
             */
            if (currentLength == 0) return false;
            /*
             * 重要的剪枝性质：一个长碎片没有若干个长度之和等于它的短碎片好,
             * 因为后者更灵活——它们总可以组合起来当作前者，但它们也可以被拆
             * 开使用。
             * 因此在任意场景下应当能长则长，在下述剪枝中，用长碎片正好填满
             * 当前木棍的情况下无解，用小碎片组合起来填满当前木棍也一定无解。
             */
            if (currentLength + choice == targetLength) return false;
        }
    return false;
}

int main ()
{
    int x, len = 0;
    scanf("%d", &n);
    min_len = 100; max_len = 0;
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &x);
        if (x > 50) continue;
        cnt[x]++;
        len += x;
        min_len = min(min_len, x);
        max_len = max(max_len, x);
    }
    for (int ans = max_len; ans < len; ans++)
        if (len % ans == 0) // 单根木棍的长度一定是总长度的约数
        {
            bool res = dfs(len / ans, 0, ans, max_len);
            if (res) { printf("%d\n", ans); return 0; }
        }
    printf("%d\n", len);
    return 0;
}