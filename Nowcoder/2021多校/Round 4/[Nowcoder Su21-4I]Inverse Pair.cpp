#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=a;i<=b;i++)
#define LOWBIT(x) (x & (-x))
using namespace std;

const int MAXN=2e5;

int n,a[MAXN+48];
bool exist[MAXN+48];

namespace BIT
{
    int c[MAXN+48];
    void init() {memset(c,0,sizeof(c));}
    void modify(int x) {while (x) c[x]++,x^=LOWBIT(x);}
    int query(int x) {int res=0;while (x<=n) res+=c[x],x+=LOWBIT(x);return res;}
}

int main ()
{
    scanf("%d",&n);rep(i,1,n) scanf("%d",a+i);BIT::init();
    long long ans=0;
    rep(i,1,n) if (!exist[a[i]+1]) exist[a[i]]=true,ans+=BIT::query(a[i]+1),BIT::modify(a[i]); else ans+=BIT::query(a[i]+2),BIT::modify(a[i]+1);
    printf("%lld\n",ans);return 0;
}