#include <bits/stdc++.h>
using namespace std;

int main ()
{
    int n;scanf("%d",&n);
    if (n<=125) puts("4");
    else if (n>=212) puts("8");
    else puts("6");
    return 0;
}