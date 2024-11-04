#include <cstdio>
#include <iostream>
#include <cstring>
using namespace std;

const int MAXN = 2e5 + 10;

int n;
char s[MAXN];

int nxt[MAXN][26], fa[MAXN], tot;
int minlen[MAXN];

int main ()
{
    scanf("%d", &n);
    tot = 1; minlen[1] = 0;
    for (int i = 1; i <= n; i++)
    {
        scanf("%s", s + 1);
        int cur = 1;
        int len = strlen(s + 1);
        int ans = len;
        for (int j = 1; j <= len; j++)
        {
            int ch = s[j] - 'a' + 1;
            if (nxt[cur][ch] == 0)
            {
                nxt[cur][ch] = ++tot;
                fa[tot] = cur;
                minlen[tot] = MAXN * 2;
            }
            cur = nxt[cur][ch];
            if (minlen[cur] != -1)
                ans = min(ans, len - j + minlen[cur]);
        }
        printf("%d\n", ans);
        for (int i = 0; cur != 1; cur = fa[cur], i++)
            minlen[cur] = min(minlen[cur], i);
    }
    return 0;
}