/*
 * 本题看似复杂，但有一个非常简单的道理:
 * 最后剩下的数长度是固定的，因此只要能让前面的数变小，不惜一切代价也要去做
 * 对于每个数位来说，只要在剩余的次数范围内能让这个位置的数变小，那就一定要删
 */
#include <bits/stdc++.h>
using namespace std;

int n, k;
char s[1000];
bool keep[1000];

int main ()
{
    scanf("%s", s + 1);
    scanf("%d", &k);
    n = strlen(s + 1);
    memset(keep, true, sizeof(keep));
    int killed = 0;
    for (int i = 1; i <= n && killed < k; i++)
    {
        bool kill = false;
        for (int j = i + 1; j <= min(i + (k - killed), n); j++)
            if (s[i] > s[j])
            {
                kill = true;
                break;
            }
        if (kill)
        {
            keep[i] = false;
            killed++;
        }
    }
    // 输出不能带有前导 0
    int print = 0;
    bool non_zero = false;
    for (int i = 1; i <= n && print < n - k; i++)
        if (keep[i])
        {
            print++;
            if (s[i] != '0') non_zero = true;
            if (non_zero) printf("%c", s[i]);
        }
    puts(non_zero ? "" : "0");
    return 0;
}