#include <bits/stdc++.h>
using namespace std;

int n;
char a[1010][1010];
bool visited[1010][1010];

int dx[] = {-1, 0, 1, 0}, dy[] = {0, 1, 0, -1};
int perimeter, area, ans_perimeter, ans_area;

bool isIceCream(int x, int y)
{
    return 1 <= x && x <= n && 1 <= y && y <= n && a[x][y] == '#';
}

void dfs(int x, int y)
{
    visited[x][y] = true;
    area++;  // dfs 所到之处都是新的冰激淋格子，更新面积
    for (int dir = 0; dir < 4; dir++)
    {
        int nxtx = x + dx[dir], nxty = y + dy[dir];
        if (!isIceCream(nxtx, nxty))     // dir 方向的格子不是冰激淋，则发现一条周长边
            perimeter++;
        else if (!visited[nxtx][nxty])   // 注意不要重复搜索已经经过的格子
            dfs(nxtx, nxty);
    }
}

int main ()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%s", a[i] + 1);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            if (a[i][j] == '#' && !visited[i][j]) // 发现一个新的冰激凌球
            {
                perimeter = area = 0;
                dfs(i, j);                        // 搜集新冰激淋球的周长和面积信息
                if (area > ans_area || (area == ans_area && perimeter < ans_perimeter))
                    ans_area = area, ans_perimeter = perimeter;
            }
    printf("%d %d\n", ans_area, ans_perimeter);
    return 0;
}