#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=a;i<=b;i++)
using namespace std;

int main ()
{
    int S,T;scanf("%d%d",&S,&T);int ans=0;
    rep(i,0,S) rep(j,0,S-i) rep(k,0,S-i-j)
        if (i*j*k<=T) ans++;
    printf("%d\n",ans);return 0;
}