#include <bits/stdc++.h>
#define LL long long
#define rep(i,a,b) for (int i=(a);i<=(b);i++)
#define REP(i,a,b) for (int i=(a);i>=(b);i--)
using namespace std;

const int MOD=1e9+7;
const int MAXN=1e6;

// template<typename T> inline void check_min(T &x,T y) {x=(x<y?x:y);}

int n,a[MAXN+48];

struct node
{
    int val,pos;
    bool operator < (const node &other) const {return val<other.val;}
}c[MAXN+48];

int L[MAXN+48],R[MAXN+48];
int sta[MAXN+48],stot;

void gen()
{
    LL p,q,x,y,z;
    scanf("%lld%lld%lld%lld%lld",&p,&q,&x,&y,&z);
    a[1]=p;a[2]=q;
    rep(i,3,n) a[i]=(x*a[i-2]+y*a[i-1]+z)%1000000+1;
}

int st_max[21][MAXN+48], st_or[21][MAXN+48];
int Log[MAXN+48];

void init_rmq()
{
    Log[1]=Log[0]=0;rep(i,2,n) Log[i]=Log[i>>1]+1;
    rep(i,1,n) st_max[0][i]=st_or[0][i]=a[i];
    rep(j,1,20) rep(i,1,n)
    {
        st_max[j][i]=st_max[j-1][i];st_or[j][i]=st_or[j-1][i];
        if (i+(1<<(j-1))<=n)
        {
            st_max[j][i]=max(st_max[j][i],st_max[j-1][i+(1<<(j-1))]);
            st_or[j][i]|=st_or[j-1][i+(1<<(j-1))];
        }
    }
}

int query_max(int l,int r)
{
    int k=Log[r-l+1];
    return max(st_max[k][l],st_max[k][r-(1<<k)+1]);
}

int query_or(int l,int r)
{
    int k=Log[r-l+1];
    return (st_or[k][l] | st_or[k][r-(1<<k)+1]);
}

int main ()
{
    // freopen ("a.in","r",stdin);
    int ca,l,r;scanf("%d",&ca);
    while (ca--)
    {
        scanf("%d",&n);gen();
        init_rmq();
        a[0]=a[n+1]=0;
        stot=1;sta[1]=0;
        rep(i,1,n)
        {
            while (stot>=0 && a[sta[stot]]>=a[i]) stot--;
            L[i]=sta[stot]+1;sta[++stot]=i;
        }
        stot=1;sta[1]=n+1;
        REP(i,n,1)
        {
            while (stot>=0 && a[sta[stot]]>=a[i]) stot--;
            R[i]=sta[stot]-1;sta[++stot]=i;
        }
        __int128_t ans=0;
        rep(i,1,n)
        {
            l=L[i];r=R[i];
            ans=max(ans, (__int128_t)(query_max(l,r)-a[i])
                *a[i]
                *(r-l+1)
                *query_or(l,r));
        }
        int fans=ans%MOD;
        printf("%d\n",fans);
    }
    return 0;
}