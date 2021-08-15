#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=a;i<=b;i++)
using namespace std;

const int MAXN=4e5;

int n;
int s[MAXN+48],t[MAXN+48],ans[MAXN+48];

int main ()
{
    scanf("%d",&n);rep(i,1,n) scanf("%d",s+i),s[n+i]=s[i];rep(i,1,n) scanf("%d",t+i),t[n+i]=t[i];
    int minn=t[1],pos=1;rep(i,2,n) if (t[i]<minn) minn=t[i],pos=i;
    ans[pos]=t[pos];
    rep(i,pos+1,pos+n-1)
        ans[i]=min(ans[i-1]+s[i-1],t[i]);
    rep(i,1,n) if (!ans[i]) printf("%d\n",ans[i+n]); else printf("%d\n",ans[i]);
    return 0;
}