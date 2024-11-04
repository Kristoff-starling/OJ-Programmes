#include <cstdio>
#include <iostream>
using namespace std;

const int MAXN = 1010;

int n, m;

int a[MAXN][MAXN];
int min1[MAXN][MAXN], min2[MAXN][MAXN], min3[MAXN][MAXN], min4[MAXN][MAXN];
int w1[MAXN][MAXN], w2[MAXN][MAXN];

int main ()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            scanf("%d", &a[i][j]);
    for (int i = 0; i <= n + 1; i++)
        for (int j = 0; j <= m + 1; j++)
            min1[i][j] = min2[i][j] = min3[i][j] = min4[i][j] = 1e9;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
        {
            min1[i][j] = min(min1[i - 1][j], min1[i][j - 1]);
            if (a[i][j] != -1)
                min1[i][j] = min(min1[i][j], a[i][j]);
            if (a[i][j] != -1 && min1[i - 1][j - 1] < 1e9)
                w1[i][j] = a[i][j] + min1[i - 1][j - 1];
            else
                w1[i][j] = 1e9;
        }
    for (int i = 1; i <= n; i++)
        for (int j = m; j >= 1; j--)
        {
            min2[i][j] = min(min2[i - 1][j], min2[i][j + 1]);
            if (a[i][j] != -1)
                min2[i][j] = min(min2[i][j], a[i][j]);
            if (a[i][j] != -1 && min2[i - 1][j + 1] < 1e9)
                w2[i][j] = a[i][j] + min2[i - 1][j + 1];
            else
                w2[i][j] = 1e9;
        }
    for (int i = n; i >= 1; i--)
        for (int j = 1; j <= m; j++)
            min3[i][j] = min(w1[i][j], min(min3[i + 1][j], min3[i][j - 1]));
    for (int i = n; i >= 1; i--)
        for (int j = m; j >= 1; j--)
            min4[i][j] = min(w2[i][j], min(min4[i + 1][j], min4[i][j + 1]));
    int ans = 1e9;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            if (a[i][j] != -1 && min3[i + 1][j - 1] < 1e9 && min4[i + 1][j + 1] < 1e9)
                ans = min(ans, a[i][j] + min3[i + 1][j - 1] + min4[i + 1][j + 1]);
    if (ans < 1e9)
        printf("%d\n", ans);
    else
        puts("-1");
    return 0;
}
/*
5 5
-1 8 3 -1 3
20 3 9 8 17
4 -1 20 12 8
17 2 14 16 1
5 10 13 5 1
5 5
12 14 -1 -1 -1
1 -1 16 -1 -1
-1 9 -1 19 -1
-1 -1 -1 19 -1
14 11 -1 -1 1
*/