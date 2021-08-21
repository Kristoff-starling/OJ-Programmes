#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=a;i<=b;i++)
#define REP(i,a,b) for (int i=a;i>=b;i--)
#define LL long long
using namespace std;

const int MAXN=1e5;

int n,m;

int t[MAXN+48];

struct node
{
    int k;
    LL id[3],l[3],r[3];
}Ans[MAXN+48],ans[MAXN+48];

bool check(LL x)
{
    LL cnt=1;LL cur=0;
    rep(i,1,n)
    {
        if (cur+t[i]<=x)
        {
            ans[i].k=1; 
            ans[i].id[1]=cnt;
            ans[i].l[1]=cur;ans[i].r[1]=cur+t[i];
            cur+=t[i];
            if (cur==x) cnt++,cur=0;
        }
        else
        {
            ans[i].k=2;
            ans[i].id[1]=cnt;
            ans[i].l[1]=cur;ans[i].r[1]=x;
            cnt++;
            cur=t[i]-(x-cur);
            ans[i].id[2]=cnt;
            ans[i].l[2]=0;ans[i].r[2]=cur;
        }
    }
    if (!cur) cnt--;
    if (cnt<=m) return true; else return false;
}

void copyans() {rep(i,1,n) Ans[i]=ans[i];}

int main ()
{
    scanf("%d%d",&n,&m);rep(i,1,n) scanf("%d",t+i);
    LL l=t[1];rep(i,2,n) l=max(l,(long long)t[i]);
    LL r=1e18,mid;
    while (l<=r)
    {
        mid=(l+r)>>1;
        if (check(mid)) copyans(),r=mid-1; else l=mid+1;
    }
    rep(i,1,n)
    {
        printf("%d ",Ans[i].k);
        REP(j,Ans[i].k,1)
        {
            printf("%lld %lld %lld",Ans[i].id[j],Ans[i].l[j],Ans[i].r[j]);
            if (j==1) puts(""); else printf(" ");
        }
    }
    return 0;
}