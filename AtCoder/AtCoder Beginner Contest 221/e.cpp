#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=a;i<=b;i++)
#define REP(i,a,b) for (int i=a;i>=b;i--)
#define LOWBIT(x) (x & (-x))
using namespace std;

const int MOD=998244353;

int add(int x) {if (x>=MOD) x-=MOD;return x;}
int sub(int x) {if (x<0) x+=MOD;return x;}
void Add(int &x,int y) {x=add(x+y);}
void Sub(int &x,int y) {x=sub(x-y);}

const int MAXN=3e5;
const int INV2=499122177;

int n,a[MAXN+48];
int pw[MAXN+48],ipw[MAXN+48];

int val[MAXN+48],tot;

namespace BIT
{
    int c[MAXN+48];
    void init() {memset(c,0,sizeof(c));}
    void update(int x,int delta) {while (x) Add(c[x],delta),x^=LOWBIT(x);}
    int query(int x) {int res=0;while (x<=tot) Add(res,c[x]),x+=LOWBIT(x);return res;}
}

int main ()
{
    scanf("%d",&n);rep(i,1,n) scanf("%d",a+i),val[++tot]=a[i];
    sort(val+1,val+tot+1);tot=unique(val+1,val+tot+1)-(val+1);
    rep(i,1,n) a[i]=lower_bound(val+1,val+tot+1,a[i])-val;
    pw[0]=1;rep(i,1,n) pw[i]=add(pw[i-1]+pw[i-1]);
    ipw[0]=1;rep(i,1,n) ipw[i]=1ll*ipw[i-1]*INV2%MOD;
    BIT::init();int ans=0;
    REP(i,n,1)
    {
        int cur=BIT::query(a[i]);
        cur=1ll*cur*ipw[i]%MOD*INV2%MOD;Add(ans,cur);
        BIT::update(a[i],pw[i]);
    }
    printf("%d\n",ans);return 0;
}