#include <bits/stdc++.h>
using namespace std;

int a[10];

int main ()
{
    int n, x, ans = 0;
    scanf("%d", &n);
    while (n--)
    {
        scanf("%d", &x); a[0]++;
        for (int i = 3; i >= 0; i--)
        {
            a[i + x] += a[i];
            if (i + x >= 4) ans += a[i];
            a[i] = 0;
        }
    }
    printf("%d\n", ans);
    return 0;
}