#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=a;i<=b;i++)
#define REp(i,a,b) for (int i=a;i>=b;i--)
#define LL long long
using namespace std;

LL n;int tot;
int b[48];

bool dp[20][61][20];

int q[20*60*20*3+1],head,tail;

void doit()
{
    tot=0;LL tmp=n;
    while (tmp) b[++tot]=tmp%10,tmp/=10;
}

void push(int x,int y,int z) {q[++tail]=x;q[++tail]=y;q[++tail]=z;}

int main ()
{
    int ca;scanf("%d",&ca);
    while (ca--)
    {
        scanf("%lld",&n);
        doit();
        rep(i,0,tot) rep(j,0,tot*3) rep(k,0,20) dp[i][j][k]=false;
        int ans=0;
        for (;;)
        {
            ans++;
            dp[0][ans][0]=true;
            head=1;tail=0;push(0,ans,0);bool f=false;
            while (head<=tail)
            {
                int cur=q[head++],avail=q[head++],lasts=q[head++];
                if (cur==tot && avail==0 && lasts==0) {f=true;break;}
                if (!avail && !lasts) continue;
                int minn=avail+lasts,maxn=avail*3+lasts;
                if (minn%10<=b[cur+1]) minn=minn/10*10+b[cur+1]; else minn=minn/10*10+10+b[cur+1];
                for (int cursum=minn;cursum<=maxn;cursum+=10)
                    for (int nxta=0;nxta<=avail;nxta++)
                        if (!dp[cur+1][nxta][cursum/10])
                        {
                            dp[cur+1][nxta][cursum/10]=true;
                            push(cur+1,nxta,cursum/10);
                        }
            }
            if (f) break;
        }
        printf("%d\n",ans);
    }
    return 0;
}