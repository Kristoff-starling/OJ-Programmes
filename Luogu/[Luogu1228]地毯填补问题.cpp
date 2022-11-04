#include <bits/stdc++.h>
using namespace std;

int k, x, y;

// 在 (dx, dy) 处的 2^k * 2^k 的棋盘上挖去 (x, y) 的方案输出
// (x, y) 是小棋盘中的相对坐标
void solve(int k, int x, int y, int dx, int dy) 
{
    if (k == 0) return;
    int hlen = 1 << (k - 1);
    // 存储四个子区域中挖空的位置
    int x1, y1, x2, y2, x3, y3, x4, y4;
    x1 = hlen; y1 = hlen;
    x2 = hlen; y2 = 1;
    x3 = 1; y3 = hlen;
    x4 = 1; y4 = 1;
    if (x <= hlen && y <= hlen)
    {
        x1 = x; y1 = y;
        printf("%d %d 1\n", dx + hlen + 1, dy + hlen + 1);
    }
    else if (x <= hlen && y > hlen)
    {
        x2 = x; y2 = y - hlen;
        printf("%d %d 2\n", dx + hlen + 1, dy + hlen);
    }
    else if (x > hlen && y <= hlen)
    {
        x3 = x - hlen; y3 = y;
        printf("%d %d 3\n", dx + hlen, dy + hlen + 1);
    }
    else
    {
        assert(x > hlen && y > hlen);
        x4 = x - hlen; y4 = y - hlen;
        printf("%d %d 4\n", dx + hlen, dy + hlen);
    }
    // 递归，处理四个子区域
    solve(k - 1, x1, y1, dx, dy);
    solve(k - 1, x2, y2, dx, dy + hlen);
    solve(k - 1, x3, y3, dx + hlen, dy);
    solve(k - 1, x4, y4, dx + hlen, dy + hlen);
}

int main ()
{
    scanf("%d%d%d", &k, &x, &y);
    solve(k, x, y, 0, 0);
    return 0;
}