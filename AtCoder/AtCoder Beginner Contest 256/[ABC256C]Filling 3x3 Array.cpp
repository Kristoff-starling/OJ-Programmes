#include <bits/stdc++.h>
using namespace std;

int main ()
{
    int h1, h2, h3, w1, w2, w3;
    scanf("%d%d%d%d%d%d", &h1, &h2, &h3, &w1, &w2, &w3);
    int ans = 0;
    for (int a = 1; a <= h1; a++)
        for (int b = 1; b <= h1; b++)
            for (int c = 1; c <= h2; c++)
                for (int d = 1; d <= h2; d++)
                {
                    int e = h1 - a - b, f = h2 - c - d;
                    int g = w1 - a - c, h = w2 - b - d;
                    if (e > 0 && f > 0 && g > 0 && h > 0 && h3 - g - h > 0 && h3 - g - h == w3 - e - f)
                        ans++;
                }
    printf("%d\n", ans);
    return 0;
}