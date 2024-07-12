#include <bits/stdc++.h>

int main ()
{
    int ca; scanf("%d", &ca);
    while (ca--)
    {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        for (int _ = 1; _ <= 5; _++)
        {
            if (a <= b && a <= c)
                a++;
            else if (b <= a && b <= c)
                b++;
            else
                c++;
        }
        printf("%d\n", a * b * c);
    }
    return 0;
}