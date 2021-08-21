#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=a;i<=b;i++)
#define LL long long
#define LOWBIT(x) (x & (-x))
using namespace std;

const int MAGIC=1000;
const int MAXN=3e5;

int n,a[MAXN+48];
LL ans[MAXN+48];

struct BIT
{
    LL c[MAXN+48];    
    void init() {memset(c,0,sizeof(c));}
    void modify(int x,LL delta) {while (x<=MAXN) c[x]+=delta,x+=LOWBIT(x);}
    LL query(int x) {LL res=0;while (x) res+=c[x],x^=LOWBIT(x);return res;}
    LL Query(int l,int r) {l=max(l,1);return query(r)-query(l-1);}
}t1,t2;

bool exist[MAXN+48];
int cntbig;LL sum;
int cnt[MAGIC+48][MAGIC+48];

int main ()
{
    scanf("%d",&n);rep(i,1,n) scanf("%d",a+i);
    cntbig=0;memset(exist,false,sizeof(exist));t1.init();t2.init();
    rep(i,1,n)
    {
        ans[i]=ans[i-1];
        rep(j,1,MAGIC) if (exist[j]) ans[i]+=(a[i]%j);
        ans[i]+=1ll*cntbig*a[i];ans[i]-=t1.query(a[i]);
        if (a[i]<=MAGIC)
            rep(j,1,a[i]-1) ans[i]+=1ll*j*cnt[a[i]][j];
        else
        {
            ans[i]+=sum;
            int div=1;
            while (a[i]*div<=MAXN)
            {
                int L=a[i]*div,R=min(a[i]*(div+1)-1,MAXN);
                int cc=t2.Query(L,R);
                ans[i]-=1ll*cc*a[i]*div;
                div++;
            }
        }
        sum+=a[i];
        rep(j,1,MAGIC) cnt[j][a[i]%j]++;
        exist[a[i]]=true;
        if (a[i]>MAGIC)
        {
            cntbig++;
            int div=1;
            while (a[i]*div<=MAXN) t1.modify(a[i]*div,a[i]),div++;
        }
        t2.modify(a[i],1);
    }
    rep(i,1,n) printf("%lld ",ans[i]);puts("");
    return 0;
}