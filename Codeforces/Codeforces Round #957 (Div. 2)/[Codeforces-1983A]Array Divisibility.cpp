#include <bits/stdc++.h>
using namespace std;

int n;

int main ()
{
    int ca;
    scanf("%d", &ca);
    while (ca--)
    {
        scanf("%d", &n);
        for (int i = 1; i <= n; i++)
        {
            int num = 1;
            for (int j = 1; j <= i; j++)
                if (i % j == 0 && num % j != 0)
                    num *= j;
            printf("%d ", num);
        }
        puts("");
    }
    return 0;
}