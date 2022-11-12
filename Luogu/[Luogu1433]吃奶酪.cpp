#include <bits/stdc++.h>
using namespace std;

int n;
double X[48], Y[48]; // 记录每块奶酪的位置

// 计算 (x1, y1) 到 (x2, y2) 的欧拉距离
double query_distance(double x1, double y1, double x2, double y2)
{
    return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

// min_distance 记录了当前状态为 Mask，老鼠在第 i 个奶酪处时走过的最短距离
/*
这里使用了经典的”状态压缩“技巧：计算机中的数都是按照二进制存储的。我们用一个
n位的二进制数来记录当前已经吃过哪些奶酪，二进制的第 i 位是 1 表示第 i 个奶酪已
经吃过，0 则表示还没有吃。这样我们用一个整数 Mask 就可以记录当前老鼠已经吃过的和
还没有吃过的奶酪，非常简明。
*/
double min_distance[100048][21];

int main ()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%lf%lf", &X[i], &Y[i]);
    // 预处理初始状态：枚举老鼠吃过的第一个奶酪是哪个，将剩下的先赋成极大值
    for (int Mask = 0; Mask <= (1 << n) - 1; Mask++)
        for (int i = 1; i <= n; i++)
            min_distance[Mask][i] = 1e10;
    for (int i = 1; i <= n; i++)
        min_distance[1 << (i-1)][i] = query_distance(0, 0, X[i], Y[i]); // 注意第i个二进制位是 1<<(i-1)
    // 多吃掉一个奶酪，二进制表示中就会多一个1,从而数值变大。这是这里从小到大枚举状态递推的依据
    // 请仔细体会按照这个顺序递推计算的妙处
    for (int Mask = 0; Mask <= (1 << n) - 1; Mask++)
        for (int cur = 1; cur <= n; cur++)
        {
            // 从 (Mask, cur) 状态出发，考虑下一个吃的奶酪
            for (int nxt = 1; nxt <= n; nxt++)
                // 此处运用了一些位运算技巧：
                // * ~Mask表示对 Mask 中的 0/1 取反
                // * &是与运算，只有两个数对应位都是 1 才会获得 1
                // 下面的运算中，第二个数是只有第 nxt 位是 1 的一个数，因此只有 Mask 的对应位
                // 是 0 该运算的结果才会非零。这正好符合我们检查第 nxt 个奶酪还没有吃的要求
                if (~Mask & (1 << (nxt - 1)))
                {
                    min_distance[Mask | (1 << (nxt - 1))][nxt] = min(
                        min_distance[Mask | (1 << (nxt - 1))][nxt],
                        min_distance[Mask][cur] + query_distance(X[cur], Y[cur], X[nxt], Y[nxt]));
                }
        }
    // 我们不关心最后老鼠停在哪里，但我们要求所有奶酪都被吃完
    double ans = 1e10;
    for (int i = 1; i <= n; i++)
        ans = min(ans, min_distance[(1 << n) - 1][i]);
    printf("%.2lf\n", ans);
    return 0;
}