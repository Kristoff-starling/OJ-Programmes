#include <cstdio>
#include <iostream>
#include <cstring>
using namespace std;

int n, q;
long long t[110], p[110];
char s[100];

long long parse_num(int l, int r)
{
    long long ans = 0;
    for (int i = l; i <= r; i++)
        ans = ans * 10 + (s[i] - '0');
    return ans;
}

long long parse(char s[])
{
    int l = 0, r = 1, len = strlen(s + 1);
    long long sum = 0;
    while (l < len)
    { 
        while (isdigit(s[r]))
            r++;
        long long num = parse_num(l + 1, r - 1);
        if (s[r] == 'd') 
            sum += num * 1440;
        else if (s[r] == 'h')
            sum += num * 60;
        else
            sum += num;
        l = r;
        r++;
    }
    return sum;
}

int main ()
{
    scanf("%d%d", &n, &q);
    for (int i = 1; i <= n; i++)
    {
        scanf("%s%lld", s + 1, p + i);
        t[i] = parse(s);
    }
    while (q--)
    {
        scanf("%s", s + 1);
        long long T = parse(s);
        long long ans = 1e18;
        long long curans = 0;
        for (int i = n; i >= 1; i--)
        {
            long long x = (T + t[i] - 1) / t[i];
            ans = min(ans, curans + x * p[i]);
            long long xx = T / t[i];
            curans += xx * p[i];
            T -= xx * t[i];
        }
        double aa = (double)ans / 100;
        printf("$%.2lf\n", aa);
    }
    return 0;
}
/*
3 5
1m 60
1h 1999
1d 12999
45m
4d3h
3d49m
10d2m
4m
*/