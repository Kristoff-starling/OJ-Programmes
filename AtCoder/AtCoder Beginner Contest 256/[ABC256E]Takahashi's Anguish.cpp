#include <bits/stdc++.h>
using namespace std;

const int MAXN = 2e5;

int n;
int nxt[MAXN + 48], c[MAXN + 48];
bool visited[MAXN + 48];

int main ()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", nxt + i);
    for (int i = 1; i <= n; i++) scanf("%d", c + i);
    long long ans = 0;
    for (int i = 1; i <= n; i++) if (!visited[i])
    {
        int cur = i;unordered_set<int> s;s.clear();
        while (!visited[cur]) visited[cur] = true, s.insert(cur), cur = nxt[cur];
        if (s.find(cur) != s.end())
        {
            int minn = c[cur], tmp = cur;
            do
            {
                cur = nxt[cur];
                minn = min(minn, c[cur]);
            }
            while (cur != tmp);
            ans += minn; 
        }
    }
    printf("%lld\n", ans);
    return 0;
}