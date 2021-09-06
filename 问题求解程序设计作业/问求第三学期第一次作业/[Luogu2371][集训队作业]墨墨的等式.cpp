#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=a;i<=b;i++)
#define LL long long
using namespace std;

const int INF=1e9;

int n;LL L,R;
int a[48];

int dist[500048];
int q[1000048];int head,tail;

int main ()
{
    scanf("%d%lld%lld",&n,&L,&R);rep(i,1,n) scanf("%d",a+i);
    sort(a+1,a+n+1);
    dist[0]=0;rep(i,1,a[n]) dist[i]=INF;
    head=tail=500010;q[head]=0;
    while (head<=tail)
    {
        int cur=q[head++];
        rep(i,1,n-1)
        {
            int to=cur+a[i];
            if (to<a[n] && dist[cur]<dist[to]) dist[to]=dist[cur],q[--head]=to;
            if (to>=a[n] && dist[cur]+1<dist[to-a[n]]) dist[to-a[n]]=dist[cur]+1,q[++tail]=to-a[n];
        }
    }
    LL ans=0;
    rep(i,0,a[n]-1)
    {
        if (dist[i]>=INF) continue;
        LL st=1ll*dist[i]*a[n]+i,ss,tt;
        LL div1=L/a[n],mo1=L%a[n],div2=R/a[n],mo2=R%a[n];
        if (mo1<=i) ss=div1*a[n]+i; else ss=(div1+1)*a[n]+i;
        if (mo2>=i) tt=div2*a[n]+i; else tt=(div2-1)*a[n]+i;
        ss=max(ss,st);if (tt>=ss) ans+=(tt-ss)/a[n]+1;
    }
    printf("%lld\n",ans);
    return 0;
}