#include <bits/stdc++.h>
#define LL long long
#define rep(i,a,b) for (int i=(a);i<=(b);i++)
using namespace std;

const int MAXN=2e5;

int n;
int a[MAXN+48],b[MAXN+48];
bool mark[MAXN+48];
LL ans;

int c[101],tot;
void doit(int id)
{
    tot=0;
    for (LL cur=id;cur<=(LL)n;cur*=id) c[tot++]=cur,mark[cur]=true;
    LL maxn=0;
    rep(Mask,0,(1<<tot)-1)
    {
        LL tmp=0;
        rep(i,0,tot-1) if (Mask>>i&1) tmp+=a[c[i]];
        rep(i,1,tot) if (Mask>>i&1) rep(j,0,i-1) if ((Mask>>j&1) && (i+1)%(j+1)==0)
            tmp-=b[c[i]];
        maxn=max(maxn,tmp);
    }
    ans+=maxn;
}

int main ()
{
    scanf("%d",&n);
    rep(i,1,n) scanf("%d",a+i);rep(i,1,n) scanf("%d",b+i);
    ans=a[1];memset(mark,false,sizeof(mark));
    rep(i,2,n) if (!mark[i]) doit(i);
    printf("%lld\n",ans);
    return 0;
}