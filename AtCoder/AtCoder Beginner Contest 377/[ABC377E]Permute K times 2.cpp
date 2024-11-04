#include <cstdio>
#include <iostream>
#include <vector>
using namespace std;

const int MAXN = 2e5 + 10;

int n; long long k;
int a[MAXN], ans[MAXN];
int c[MAXN], cnt;
bool visited[MAXN];

int quick_pow(int x, long long y, int mod)
{
    int ans = 1;
    while (y)
    {
        if (y & 1)
            ans = 1ll * ans * x % mod;
        x = 1ll * x * x % mod;
        y >>= 1;
    }
    return ans;
}

int main ()
{
    scanf("%d%lld", &n, &k);
    for (int i = 1; i <= n; i++)
        scanf("%d", a + i);
    for (int i = 1; i <= n; i++)
        if (!visited[i])
        {
            cnt = 0;
            int cur = i;
            while (!visited[cur])
            {
                visited[cur] = true;
                c[++cnt] = cur;
                cur = a[cur];
            }
            int step = quick_pow(2, k, cnt);
            step = (step == 0) ? cnt - 1 : step - 1;
            for (int j = 1; j <= cnt; j++)
                ans[c[j]] = a[c[(j + step - 1) % cnt + 1]];
        }
    for (int i = 1; i <= n; i++)
        printf("%d ", ans[i]);
    puts("");
    return 0;
}