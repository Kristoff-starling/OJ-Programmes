/*
 * 每个物品有不选，放入左集合，放入右集合三种状态
 * 暴力搜索的复杂度会达到 3 ^ n，无法通过.
 * 考虑将 n 个物品分成两部分分别搜索，最后将 delta 相同的合并起来
 * 复杂度降低到 3 ^ (n / 2).
 */
#include <bits/stdc++.h>
using namespace std;

int n;
int a[100];

unordered_map<int, unordered_set<int> > m1, m2;
bool ans[2000000];  // 记录每个子集是否可以划分

void dfs(int cur, int lim, int sum, int Mask, unordered_map<int, unordered_set<int> > &m)
{   
    /*
     * 将半边的答案存储到 map 当中: 两个阵营的差为 sum 的选法多了 Mask 这一种
     * map 映射的内容是 unordered_set，对能达到同样 sum 的相同的 Mask 进行去重
     * 注意我们只需要记录非负的情况，因为负的倒过来就是正的
     */
    if (cur > lim)
    {
        if (sum >= 0) m[sum].insert(Mask);
        return;
    }

    // Choice 1: 不选
    dfs(cur + 1, lim, sum, Mask, m);
    // Choice 2: 放入左集合
    dfs(cur + 1, lim, sum + a[cur], Mask | (1 << (cur - 1)), m);
    // Choice 3: 放入右集合
    dfs(cur + 1, lim, sum - a[cur], Mask | (1 << (cur - 1)), m);
}

int main ()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", a + i);
    dfs(1, n / 2, 0, 0, m1);
    dfs(n / 2 + 1, n, 0, 0, m2);
    for (auto item : m1)  
        /*
         * 这是 C++11 标准下的新写法: item 是一个 pair，item.first 是 key, 
         * item.second 是 value.
         * 这种写法比传统的
         * for (unordered_map<...> iter = m1.begin(); iter != m1.end(); iter++)
         * 要简洁很多.
         */
        for (auto Mask1 : item.second)
        // 遍历 unordered_set，同样是 C++11 下的新写法
            for (auto Mask2 : m2[item.first])
                ans[Mask1 | Mask2] = true;
    int count = 0;
    for (int i = 1; i <= (1 << n) - 1; i++)
        if (ans[i]) count++;
    printf("%d\n", count);
    return 0;
}