#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=a;i<=b;i++)
using namespace std;

const int MAXN=2e5;

int n,b[MAXN+48],c[MAXN+48],val[MAXN+48],N;
int d[MAXN+48],head[MAXN+48],to[MAXN+48],nxt[MAXN+48],f[MAXN+48],tot;
bool visited[MAXN+48];
int ans[MAXN+48],t;

void addedge(int x,int y,int id)
{
    to[++tot]=y;nxt[tot]=head[x];head[x]=tot;f[tot]=id;
    to[++tot]=x;nxt[tot]=head[y];head[y]=tot;f[tot]=id;
    d[x]++;d[y]++;
}

void fleury(int cur)
{
    for (int &i=head[cur];i;i=nxt[i]) if (!visited[f[i]])
        visited[f[i]]=true,fleury(to[i]);
    ans[++t]=cur;
}

int main ()
{
    scanf("%d",&n);rep(i,1,n-1) scanf("%d",b+i);rep(i,1,n-1) scanf("%d",c+i);
    N=0;rep(i,1,n-1) val[++N]=b[i],val[++N]=c[i];
    sort(val,val+N+1);N=unique(val+1,val+N+1)-(val+1);
    rep(i,1,n-1) b[i]=lower_bound(val+1,val+N+1,b[i])-val,c[i]=lower_bound(val+1,val+N+1,c[i])-val;
    rep(i,1,n-1) if (b[i]>c[i]) {puts("-1");return 0;}
    tot=0;rep(i,1,n-1) addedge(b[i],c[i],i);int s=1,cc=0;
    rep(i,1,N) if (d[i]&1) ++cc,s=i;
    if (!(cc==0 || cc==2)) {puts("-1");return 0;}
    t=0;fleury(s);
    if (t!=n) puts("-1");
    else {rep(i,1,n) printf("%d ",val[ans[i]]);puts("");}
    return 0;
}