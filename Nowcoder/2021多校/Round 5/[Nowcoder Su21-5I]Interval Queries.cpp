#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=a;i<=b;i++)
#define REP(i,a,b) for (int i=a;i>=b;i--)
#define pb push_back
using namespace std;

const int MOD=998244353;
const int MAGIC=348;
const int MAXN=1e5;

int add(int x) {if (x>=MOD) x-=MOD;return x;}
int sub(int x) {if (x<0) x+=MOD;return x;}
void Add(int &x,int y) {x=add(x+y);}
void Sub(int &x,int y) {x=sub(x-y);}

template<typename T> void check_max(T &x,T y) {if (y>x) x=y;}
template<typename T> void check_min(T &x,T y) {if (y<x) x=y;}

int n,q;

struct node
{
    int l,r,k,id;
    void input(int _id) {scanf("%d%d%d",&l,&r,&k);id=_id;}
    bool operator < (const node &other) const {return r<other.r;}
}qq[MAXN+48];

int ar(int x) {return (x-1)/MAGIC+1;}

vector<node> seq[MAXN+48];
int ans[MAXN+48];

int a[MAXN+48];
int L[MAXN+48],R[MAXN+48],cnt[MAXN+48];

int pw[MAXN+48],maxn;
int htot,hmaxn[MAXN+48],hl[MAXN+48],hlval[MAXN+48],hr[MAXN+48],hrval[MAXN+48];

void init()
{
    htot=0;maxn=0;
    memset(L,0,sizeof(L));memset(R,0,sizeof(R));memset(cnt,0,sizeof(cnt));
}

void doit_add(int x)
{
    cnt[x]++;
    if (cnt[x]==1)
    {
        ++htot;hmaxn[htot]=maxn;
        int l=x,r=x;
        if (x>1 && cnt[x-1]) l=L[x-1];
        if (x<n && cnt[x+1]) r=R[x+1];
        check_max(maxn,r-l+1); 
        hl[htot]=r;hlval[htot]=L[r];hr[htot]=l;hrval[htot]=R[l];
        L[r]=l;R[l]=r;
    }
}

void doit_sub(int x)
{
    cnt[x]--;
    if (!cnt[x])
    {
        L[hl[htot]]=hlval[htot];R[hr[htot]]=hrval[htot];maxn=hmaxn[htot];
        L[x]=R[x]=0;
        htot--;
    }
}

int main ()
{
    scanf("%d%d",&n,&q);
    rep(i,1,n) scanf("%d",a+i);
    rep(i,1,q)
    {
        qq[i].input(i);
        if (ar(qq[i].l)==ar(qq[i].r)) seq[0].pb(qq[i]); else seq[ar(qq[i].l)].pb(qq[i]);
    }
    pw[0]=1;rep(i,1,n) pw[i]=1ll*pw[i-1]*(n+1)%MOD;
    rep(i,1,n) sort(seq[i].begin(),seq[i].end());
    for (auto item : seq[0])
    {
        maxn=0;rep(i,item.l,item.r) doit_add(a[i]);
        int Ans=1ll*maxn*pw[0]%MOD;
        rep(i,1,item.k-1)
        {
            doit_add(a[item.l-i]);doit_add(a[item.r+i]);
            Add(Ans,1ll*maxn*pw[i]%MOD);
        }
        ans[item.id]=Ans;
        REP(i,item.k-1,1) doit_sub(a[item.r+i]),doit_sub(a[item.l-i]);
        REP(i,item.r,item.l) doit_sub(a[i]);
    }
    rep(blo,1,n) if (int(seq[blo].size()))
    {
        int ll,rr=blo*MAGIC;
        init();
        for (auto item : seq[blo])
        {
            while (rr<item.r) ++rr,doit_add(a[rr]);
            ll=blo*MAGIC+1;
            while (ll>item.l) --ll,doit_add(a[ll]);
            int Ans=1ll*maxn*pw[0]%MOD;
            rep(i,1,item.k-1)
            {
                doit_add(a[item.l-i]);doit_add(a[item.r+i]);
                Add(Ans,1ll*maxn*pw[i]%MOD);
            }
            ans[item.id]=Ans;
            REP(i,item.k-1,1) doit_sub(a[item.r+i]),doit_sub(a[item.l-i]);
            while (ll<blo*MAGIC+1) doit_sub(a[ll]),ll++;
        }
    }
    rep(i,1,q) printf("%d\n",ans[i]);
    return 0;
}