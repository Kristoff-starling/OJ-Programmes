#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=a;i<=b;i++)
#define REP(i,a,b) for (int i=a;i>=b;i--)
using namespace std;

const int MAXN=1e5;

int n,m;
int mark[MAXN+48];
int lim;
int nxt[MAXN+48];
int pos[MAXN+48];

int main ()
{
    int ca;scanf("%d",&ca);
    while (ca--)
    {
        scanf("%d%d",&n,&m);
        rep(i,1,n) mark[i]=0;int x;
        rep(i,1,m) scanf("%d",&x),mark[x]=1;
        mark[n+1]=1;
        nxt[n+1]=n+1;
        REP(i,n,1) if (mark[i]==1) nxt[i]=i; else nxt[i]=i+1;
        pos[0]=0;
        rep(i,1,n-m)
        {
            pos[i]=pos[i-1]+1;
            while (mark[pos[i]]) pos[i]++;
        }
        lim=n+1;int tmp=0;
        REP(i,n,1)
        {
            if (mark[i]) tmp--; else tmp++;
            if (tmp<0) break;
            lim=i;
        }
        int cnt0=0,cur=0,cntb=0;bool f=false;
        rep(i,1,n)
        {
            if (!mark[i]) cur++; else cntb++;
            if (mark[i] || (i<n && mark[i+1])) cnt0+=cur,cur=0;
            if ((cnt0+cur)*2>n-m) break;
            if (cur)
            {
                int L=i+1,R=nxt[L]-1;
                if (R-L+1-cnt0-cntb>0) continue;
            }
            if ((cnt0+cur)*2+m<n-m) continue;
            if ((cnt0+cur)*2==n-m) f=true;
            else
            {
                cerr<<i<<' '<<"*"<<endl;
                int pp=pos[(cnt0+cur)*2+1];
                cerr<<pp<<' '<<lim<<endl;
                if (pp>=lim) f=true;
            }
        }
        if (f) puts("YES"); else puts("NO");
    }
}