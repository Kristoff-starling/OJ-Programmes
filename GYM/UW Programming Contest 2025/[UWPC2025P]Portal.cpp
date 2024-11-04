#include <cstdio>
#include <iostream>
#include <cstring>
using namespace std;

int R, C, sx, sy;
char s[1000010];

int main ()
{
    scanf("%d%d%d%d", &R, &C, &sx, &sy);
    scanf("%s", s + 1);
    int len = strlen(s + 1);
    int xx = sx, yy = sy;
    for (int i = 1; i <= len; i++)
    {
        if (s[i] == 'P')
        {
            yy--;
            if (yy == -1) yy = C - 1;
        }
        else if (s[i] == 'Q')
        {
            yy++;
            if (yy == C) yy = 0;
        }
        else if (s[i] == 'R')
        {
            xx++;
            if (xx == R) xx = 0;
        }
        else if (s[i] == 'S')
        {
            xx--;
            if (xx == -1) xx = R - 1;
        }
    }
    printf("%d %d\n", xx, yy);
    return 0;
}