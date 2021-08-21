#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=a;i<=b;i++)
#define LOWBIT(x) ((x) & (-x))
using namespace std;

const int MAXN=1e5;
const int MOD=998244353;

int add(int x) {if (x>=MOD) x-=MOD;return x;}
int sub(int x) {if (x<0) x+=MOD;return x;}
void Add(int &x,int y) {x=add(x+y);}
void Sub(int &x,int y) {x=sub(x-y);}
void Mul(int &x,int y) {x=1ll*x*y%MOD;}

int n,q,a[MAXN+48];

namespace SegmentTree
{
    int cnt[MAXN<<2],sum1[MAXN<<2],sum2[MAXN<<2],lazy[MAXN<<2];
    void pushdown(int cur)
    {
        Mul(lazy[cur<<1],lazy[cur]);Mul(sum1[cur<<1],lazy[cur]);
        Mul(lazy[cur<<1|1],lazy[cur]);Mul(sum1[cur<<1|1],lazy[cur]);
        lazy[cur]=1;
    }
    void pushup(int cur)
    {
        sum1[cur]=add(sum1[cur<<1]+sum1[cur<<1|1]);
        sum2[cur]=add(sum2[cur<<1]+sum2[cur<<1|1]);
        cnt[cur]=max(cnt[cur<<1],cnt[cur<<1|1]);
        if (cnt[cur]==0) sum1[cur]=sum2[cur]=0;
    }
    void build(int cur,int l,int r)
    {
        if (l==r)
        {
            cnt[cur]=0;int tmp=a[l];
            while (tmp) cnt[cur]+=(tmp&1),tmp>>=1;
            int pt=31;while (!(a[l]>>pt&1)) pt--;
            sum1[cur]=(1<<pt);sum2[cur]=a[l]-sum1[cur];lazy[cur]=1;
            return;
        }
        int mid=(l+r)>>1;
        build(cur<<1,l,mid);build(cur<<1|1,mid+1,r);
        pushup(cur);lazy[cur]=1;
    }
    int query(int cur,int left,int right,int l,int r)
    {
        if (left<=l && r<=right) return add(sum1[cur]+sum2[cur]);
        int res=0,mid=(l+r)>>1;pushdown(cur);
        if (left<=mid) Add(res,query(cur<<1,left,right,l,mid));
        if (mid+1<=right) Add(res,query(cur<<1|1,left,right,mid+1,r));
        pushup(cur);return res;
    }
    void modify1(int cur,int left,int right,int l,int r)
    {
        if (cnt[cur]==0) return;
        if (l==r)
        {
            if (sum2[cur]) sum2[cur]-=LOWBIT(sum2[cur]); else sum1[cur]=0;
            cnt[cur]--;return;
        }
        pushdown(cur);int mid=(l+r)>>1;
        if (left<=mid) modify1(cur<<1,left,right,l,mid);
        if (mid+1<=right) modify1(cur<<1|1,left,right,mid+1,r);
        pushup(cur);
    }
    void modify2(int cur,int left,int right,int l,int r)
    {
        if (cnt[cur]==0) return;
        if (left<=l && r<=right)
        {
            Mul(lazy[cur],2);Mul(sum1[cur],2);
            return;
        }
        pushdown(cur);int mid=(l+r)>>1;
        if (left<=mid) modify2(cur<<1,left,right,l,mid);
        if (mid+1<=right) modify2(cur<<1|1,left,right,mid+1,r);
        pushup(cur);
    }
}

int main ()
{
    int ca,op,l,r;scanf("%d",&ca);
    while (ca--)
    {
        scanf("%d",&n);rep(i,1,n) scanf("%d",a+i);
        SegmentTree::build(1,1,n);
        scanf("%d",&q);
        while (q--)
        {
            scanf("%d%d%d",&op,&l,&r);
            if (op==1) printf("%d\n",SegmentTree::query(1,l,r,1,n));
            if (op==2) SegmentTree::modify1(1,l,r,1,n);
            if (op==3) SegmentTree::modify2(1,l,r,1,n);
        }
    }
    return 0;
}