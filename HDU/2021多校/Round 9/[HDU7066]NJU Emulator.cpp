#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=a;i<=b;i++)
#define ull unsigned long long
using namespace std;

ull n;

int a[100];bool type[100];

void init()
{
    puts("p1");
    rep(i,2,8) puts("dup"),printf("add %d\n",i-1);
    puts("dup");puts("add 1");
}

int main ()
{
    int ca;scanf("%d",&ca);
    while (ca--)
    {
        scanf("%llu",&n);
        ull tmp=n;rep(i,1,16) a[i]=(tmp&15),tmp>>=4;
        rep(i,1,16) if (a[i]<=8) type[i]=false; else a[i+1]++,a[i]=16-a[i],type[i]=true;
        init();
        if (!type[16])
        {
            puts("p1");
            if (a[16]>1) printf("add %d\n",11-a[16]);
            else if (a[16]==0) puts("sub 9");
        }
        else
        {
            puts("dup");
            if (a[16]) printf("sub %d\n",10-a[16]);
        }
        for (int i=15;i>=1;i--)
        {
            puts("mul 1");
            if (!type[i])
                {if (a[i]) printf("add %d\n",10-a[i]);}
            else
                {if (a[i]) printf("sub %d\n",10-a[i]);}
        }
        puts("end");
    }
    return 0;
}