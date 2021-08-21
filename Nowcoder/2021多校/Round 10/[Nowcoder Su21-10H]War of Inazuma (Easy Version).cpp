#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=a;i<=b;i++)
using namespace std;

int n,cnt[10000048];

int main ()
{
    scanf("%d",&n);cnt[0]=0;
    rep(i,0,(1<<n)-1)
    {
        cnt[i]=cnt[i>>1]+(i&1);
        if (cnt[i]&1) putchar('0'); else putchar('1');
    }
    puts("");return 0;
}