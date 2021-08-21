#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=a;i<=b;i++)
#define REP(i,a,b) for (int i=a;i>=b;i--)
#define Pair pair<int,int>
#define x first
#define y second
#define mp make_pair
#define LOWBIT(x) (x & (-x))
using namespace std;

const int MAXN=1e5;
const int MOD=998244353;

int n,a[MAXN+48],maxn[MAXN+48],pos[MAXN+48],ans[MAXN+48];

int add(int x) {if (x>=MOD) x-=MOD;return x;}
int sub(int x) {if (x<0) x+=MOD;return x;}
void Add(int &x,int y) {x=add(x+y);}
void Sub(int &x,int y) {x=sub(x-y);}

namespace SegmentTree
{
    int maxn[MAXN*4],maxpos[MAXN*4];
    void build(int cur,int l,int r)
    {
        maxn[cur]=maxpos[cur]=0;
        if (l==r) return;
        int mid=(l+r)>>1;
        build(cur<<1,l,mid);build(cur<<1|1,mid+1,r);
    }
    void pushup(int cur)
    {
        if (maxn[cur<<1]>maxn[cur<<1|1]) maxn[cur]=maxn[cur<<1],maxpos[cur]=maxpos[cur<<1]; else maxn[cur]=maxn[cur<<1|1],maxpos[cur]=maxpos[cur<<1|1];
    }
    void modify(int cur,int pos,int val,int l,int r)
    {
        if (l==r) {maxn[cur]=val;maxpos[cur]=pos;return;}
        int mid=(l+r)>>1;
        if (pos<=mid) modify(cur<<1,pos,val,l,mid); else modify(cur<<1|1,pos,val,mid+1,r);
        pushup(cur);
    }
    Pair query(int cur,int left,int right,int l,int r)
    {
        if (left>right) return mp(0,0);
        if (left<=l && r<=right) return mp(maxn[cur],maxpos[cur]);
        int mid=(l+r)>>1;Pair res=mp(0,0);
        if (left<=mid)
        {
            Pair tmp=query(cur<<1,left,right,l,mid);
            if (tmp.x>res.x) res=tmp;
        }
        if (mid+1<=right)
        {
            Pair tmp=query(cur<<1|1,left,right,mid+1,r);
            if (tmp.x>res.x) res=tmp;
        }
        return res;
    }
}

int to[MAXN+48][21],sum[MAXN+48][21];

int query(int st,int lim)
{
    int cur=st,res=0;
    REP(i,20,0) if (to[cur][i]<lim) Add(res,sum[cur][i]),cur=to[to[cur][i]][1];
    return res;
}

void modify(int cur,int nxt)
{
    to[cur][0]=cur;to[cur][1]=nxt;
    rep(i,2,20) to[cur][i]=to[to[to[cur][i-1]][1]][i-1];
    sum[cur][0]=ans[cur];
    rep(i,1,20) sum[cur][i]=add(sum[cur][i-1]+sum[to[to[cur][i-1]][1]][i-1]);
}

int main ()
{
    int ca;scanf("%d",&ca);
    while (ca--)
    {
        scanf("%d",&n);rep(i,1,n) scanf("%d",a+i),pos[a[i]]=i;
        maxn[n]=a[n];REP(i,n-1,1) maxn[i]=max(maxn[i+1],a[i]);
        rep(i,0,20) to[n+1][i]=n+1,sum[n+1][i]=0;
        SegmentTree::build(1,1,n);
        rep(i,1,n)
        {
            int p=pos[i];Pair res=SegmentTree::query(1,1,p-1,1,n);
            if (res.x==0) ans[p]=1; else ans[p]=query(res.y,p);
            res=SegmentTree::query(1,p+1,n,1,n);
            if (res.x==0) modify(p,n+1); else modify(p,res.y);
            SegmentTree::modify(1,p,i,1,n);
        }
        int Ans=0;
        rep(i,1,n) if (maxn[i]==a[i]) Add(Ans,ans[i]);
        printf("%d\n",Ans);
    }
    return 0;
}