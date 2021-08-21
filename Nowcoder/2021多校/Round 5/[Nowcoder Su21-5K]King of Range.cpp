#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=a;i<=b;i++)
#define LL long long
using namespace std;

const int MAXN=1e5;

template<typename T> void check_min(T &x,T y) {if (y<x) x=y;}
template<typename T> void check_max(T &x,T y) {if (y>x) x=y;}

int n,q,a[MAXN+48];

int stmin[MAXN+48][21],stmax[MAXN+48][21];
int Log[MAXN+48];

void init_ST()
{
    Log[1]=0;rep(i,2,n) Log[i]=Log[i>>1]+1;
    rep(i,1,n) stmin[i][0]=stmax[i][0]=a[i];
    rep(j,1,20) rep(i,1,n)
    {
        stmin[i][j]=stmin[i][j-1];stmax[i][j]=stmax[i][j-1];
        if (i+(1<<(j-1))<=n) check_min(stmin[i][j],stmin[i+(1<<(j-1))][j-1]),check_max(stmax[i][j],stmax[i+(1<<(j-1))][j-1]);
    }
}

int query_stmin(int l,int r)
{
    int k=Log[r-l+1];
    return min(stmin[l][k],stmin[r-(1<<k)+1][k]);
}

int query_stmax(int l,int r)
{
    int k=Log[r-l+1];
    return max(stmax[l][k],stmax[r-(1<<k)+1][k]);
}

int main ()
{
    scanf("%d%d",&n,&q);rep(i,1,n) scanf("%d",a+i);
    init_ST();int minn,maxn,delta;LL ans;
    while (q--)
    {
        scanf("%d",&delta);
        int R=1;minn=maxn=a[1];ans=0;
        while (R<=n && maxn-minn<=delta) R++,check_max(maxn,a[R]),check_min(minn,a[R]);
        if (R<=n)
        {
            ans=n-R+1;
            rep(i,2,n)
            {
                minn=query_stmin(i,R);maxn=query_stmax(i,R);
                while (R<=n && maxn-minn<=delta) R++,check_max(maxn,a[R]),check_min(minn,a[R]);
                if (R==n+1) break;
                ans+=n-R+1;
            }
        }
        printf("%lld\n",ans);
    }
    return 0;
}