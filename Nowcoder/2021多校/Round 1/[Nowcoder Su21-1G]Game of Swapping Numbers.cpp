#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=a;i<=b;i++)
#define LL long long
using namespace std;

const int MAXN=5e5;

template<typename T> T myabs(T x) {return x>=0?x:-x;}

int n,k,a[MAXN+48],b[MAXN+48],sgna[MAXN+48],sgnb[MAXN+48];

struct node
{
    int val;int from;
    bool operator < (const node &other) const {return val<other.val;}
}t[MAXN*2+48];

int pos[MAXN+48],neg[MAXN+48],tot1,tot2;

int main ()
{
    scanf("%d%d",&n,&k);rep(i,1,n) scanf("%d",a+i);rep(i,1,n) scanf("%d",b+i);
    if (n==2)
    {
        if (k&1) swap(a[1],a[2]);
        printf("%lld\n",(long long)myabs(a[1]-b[1])+(long long)myabs(a[2]-b[2]));
        return 0;
    }
    rep(i,1,n) t[i].val=a[i],t[i].from=i;rep(i,n+1,n+n) t[i].val=b[i-n],t[i].from=i;
    sort(t+1,t+n+n+1);
    rep(i,1,n) if (t[i].from<=n) sgna[t[i].from]=1; else sgnb[t[i].from-n]=1;
    LL ans=0;rep(i,1,n) ans+=myabs(a[i]-b[i]);
    tot1=tot2=0;rep(i,1,n) if (sgna[i]==sgnb[i]) if (!sgna[i]) pos[++tot1]=-min(a[i],b[i]); else neg[++tot2]=max(a[i],b[i]);
    sort(pos+1,pos+tot1+1);sort(neg+1,neg+tot2+1);
    rep(i,1,min(k,tot1)) ans-=2ll*pos[i],ans-=2ll*neg[i];
    printf("%lld\n",ans);return 0;
}