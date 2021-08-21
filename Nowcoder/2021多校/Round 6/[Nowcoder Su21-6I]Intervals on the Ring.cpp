#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=a;i<=b;i++)
using namespace std;

const int MAXN=1000;

int n,m;

struct node
{
    int l,r;
    bool operator < (const node &other) const {return l<other.l;}
}a[MAXN+48];

int main ()
{
    int ca;scanf("%d",&ca);
    while (ca--)
    {
        scanf("%d%d",&n,&m);
        rep(i,1,m) scanf("%d%d",&a[i].l,&a[i].r);
        if (m==1)
        {
            puts("1");
            printf("%d %d\n",a[1].l,a[1].r);
            continue;
        }
        sort(a+1,a+m+1);
        a[m+1]=a[1];
        printf("%d\n",m);
        rep(i,1,m) printf("%d %d\n",a[i+1].l,a[i].r);
    }
    return 0;
}