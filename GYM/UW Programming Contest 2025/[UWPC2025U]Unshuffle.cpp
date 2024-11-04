#include <cstdio>
#include <iostream>
#include <vector>
using namespace std;

long long gcd(long long x, long long y)
{
    if (y == 0) return x; else return gcd(y, x % y);
}

int a[1000];
bool visited[1000];
vector<int> c;

int main ()
{
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", a + i);
    long long ans = 1;
    for (int i = 1; i <= n; i++)
        if (!visited[i])
        {
            int cnt = 0, cur = i;
            while (!visited[cur])
            {
                cnt++;
                visited[cur] = true;
                cur = a[cur];
            }
            ans = 1ll * ans * cnt / gcd(ans, cnt);
        }
    printf("%lld\n", ans - 1);
    return 0;
}