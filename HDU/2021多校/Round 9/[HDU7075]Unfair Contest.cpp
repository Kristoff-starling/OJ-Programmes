#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=a;i<=b;i++)
#define LL long long
#define mp make_pair
#define x first
#define y second
using namespace std;

const int MAXN=1e5;

int n,s,t,h,a[MAXN+48],b[MAXN+48];
LL suma[MAXN+48],sumb[MAXN+48];
pair<int,LL> a1,a2,b1,b2;
pair<int,int> an[4],bn[4];pair<LL,LL> as[4],bs[4];

int main ()
{
    int ca;scanf("%d",&ca);
    while (ca--)
    {
        scanf("%d%d%d%d",&n,&s,&t,&h);swap(s,t);
        rep(i,1,n-1) scanf("%d",a+i);rep(i,1,n-1) scanf("%d",b+i);
        sort(a+1,a+n);sort(b+1,b+n);
        suma[0]=0;rep(i,1,n-1) suma[i]=suma[i-1]+a[i];
        sumb[0]=0;rep(i,1,n-1) sumb[i]=sumb[i-1]+b[i];
        if (s==0) a1.x=1,a1.y=suma[n-s-t-1]+1; else a1.x=a[s],a1.y=suma[n-t-1]-suma[s-1];
        if (t==0) a2.x=h,a2.y=suma[n-1]-suma[s]+h; else a2.x=a[n-t],a2.y=suma[n-t]-suma[s];
        if (s==0) b1.x=1,b1.y=sumb[n-s-t-1]+1; else b1.x=b[s],b1.y=sumb[n-t-1]-sumb[s-1];
        if (t==0) b2.x=h,b2.y=sumb[n-1]-sumb[s]+h; else b2.x=b[n-t],b2.y=sumb[n-t]-sumb[s];
        an[1]=mp(1,1);as[1]=mp(a1.y,a1.y);an[2]=mp(a1.x,a2.x);as[2]=mp(a1.y,a2.y);an[3]=mp(a2.x,a2.x);as[3]=mp(a2.y,a2.y);
        bn[1]=mp(b1.x,b1.x);bs[1]=mp(b1.y,b1.y);bn[2]=mp(b1.x,b2.x);bs[2]=mp(b1.y,b2.y);bn[3]=mp(h,h);bs[3]=mp(b2.y,b2.y);
        int ans=h+1,xx,yy;
        rep(i,1,3) rep(j,1,3)
        {
            if (as[i].y<=bs[j].x) continue;
            if (bs[j].x>=as[i].x-1) xx=an[i].x+bs[j].x+1-as[i].x,yy=bn[j].x,ans=min(ans,xx-yy);
            else if (bs[j].y>=as[i].x-1) xx=an[i].x,yy=as[i].x-1-bs[j].x+bn[j].x,ans=min(ans,xx-yy);
            else xx=an[i].x,yy=bn[j].y,ans=min(ans,xx-yy);
        }
        if (ans==h+1) puts("IMPOSSIBLE"); else printf("%d\n",ans);
    }
    return 0;
}