#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=a;i<=b;i++)
#define pb push_back
using namespace std;

const int MAXN=1e6;

int n,k;
int b[MAXN+48];

vector<int> v[MAXN+48];int d[MAXN+48];
int sta[MAXN+48],tot;
int head,tail,q[MAXN+48],ans[MAXN+48];

int main ()
{
    scanf("%d%d",&n,&k);int p,x;tot=0;
    rep(i,1,k) scanf("%d%d",&p,&x),b[p]=x;
    rep(i,1,n)
    {
        if (!b[i])
        {
            if (tot) v[sta[tot]].pb(i),d[i]++;
            sta[++tot]=i;
        }
        else
        {
            if (tot<b[i]-1) {puts("-1");return 0;}
            if (tot>b[i]-1) v[i].pb(sta[b[i]]),d[sta[b[i]]]++;
            tot=b[i]-1;if (tot) v[sta[tot]].pb(i),d[i]++;
            sta[++tot]=i; 
        }
    }
    int id=0;head=1;tail=0;rep(i,1,n) if (!d[i]) q[++tail]=i;
    while (head<=tail)
    {
        int cur=q[head++];ans[cur]=++id;
        for (auto item : v[cur])
        {
            d[item]--;
            if (!d[item]) q[++tail]=item;
        }
    }
    rep(i,1,n-1) printf("%d ",ans[i]);
    printf("%d\n",ans[n]);return 0;
}