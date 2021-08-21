#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=a;i<=b;i++)
using namespace std;

int main ()
{
    int x,s;scanf("%d%d",&x,&s);
    rep(i,0,30) if ((x&(1<<i)) && !(s&(1<<i))) {puts("0");return 0;}
    int cnt=0,tmp=x;rep(i,0,30) cnt+=(tmp&1),tmp>>=1;
    int pw=1;rep(i,1,cnt) pw<<=1;if (x==s) pw--;
    printf("%d\n",pw);return 0;
}