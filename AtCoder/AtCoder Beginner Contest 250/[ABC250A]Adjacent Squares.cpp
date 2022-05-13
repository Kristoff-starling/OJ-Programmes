#include <bits/stdc++.h>
using namespace std;

int main ()
{
    int h,w,r,c,ans=0;
    scanf("%d%d%d%d",&h,&w,&r,&c);
    ans=(r!=1)+(r!=h)+(c!=1)+(c!=w);
    printf("%d\n",ans);
    return 0;
}