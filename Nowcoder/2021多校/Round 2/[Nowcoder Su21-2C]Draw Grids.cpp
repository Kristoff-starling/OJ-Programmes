#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=a;i<=b;i++)
using namespace std;

int main ()
{
    int n,m;scanf("%d%d",&n,&m);
    if ((n&1) && (m&1)) puts("NO"); else puts("YES");
    return 0;
}