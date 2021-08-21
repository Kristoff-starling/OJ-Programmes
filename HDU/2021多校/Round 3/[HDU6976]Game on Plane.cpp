#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=a;i<=b;i++)
#define LL long long
using namespace std;

const int MAXN=1e5;

template<typename T> T mygcd(T x,T y) {return (!y)?x:mygcd(y,x%y);}
template<typename T> T myabs(T x) {return (x>=0)?x:-x;}

int n;

struct frac
{
    LL A,B;int type;
    frac () {A=0;B=1;}
    frac (LL _A,LL _B) {A=_A;B=_B;}
    bool operator < (const frac &other) const
    {
        if (type!=other.type) return type<other.type;
        if (type==2) return false;
        return A*other.B<other.A*B;
    }
    bool operator == (const frac &other) const
    {
        if (type!=other.type) return false;
        if (type==2) return true;
        return A*other.B==other.A*B;
    }
}a[MAXN+48];

int tot,cnt[MAXN+48],num[MAXN+48];

bool cmp(int x,int y) {return x>y;}

int main ()
{
    int ca;scanf("%d",&ca);
    while (ca--)
    {
        scanf("%d",&n);LL x1,y1,x2,y2;
        rep(i,1,n)
        {
            scanf("%lld%lld%lld%lld",&x1,&y1,&x2,&y2);
            y2-=y1;x2-=x1;
            if (x2==0) {a[i].type=2;continue;}
            if (x2<0) x2=-x2,y2=-y2;
            if (y2==0)
            {
                a[i].A=0;a[i].B=1;a[i].type=1;
                continue; 
            }
            if (y2<0) a[i].type=0; else a[i].type=1;
            y2=myabs(y2);LL g=mygcd(y2,x2);y2/=g;x2/=g;
            a[i].A=y2;a[i].B=x2;
        }
        sort(a+1,a+n+1);
        int pt1=1,pt2;tot=0;
        while (pt1<=n)
        {
            pt2=pt1;
            while (pt2<=n && a[pt1]==a[pt2]) pt2++;pt2--;
            cnt[++tot]=pt2-pt1+1;pt1=pt2+1;
        }
        sort(cnt+1,cnt+tot+1,cmp);
        rep(i,1,tot) num[i]=0;
        int pt=1;
        rep(i,1,n)
        {
            num[pt]++;pt++;
            if (pt>tot || num[pt]==cnt[pt]) pt=1;
            printf("%d\n",i-num[1]);
        }
    }
    return 0;
}