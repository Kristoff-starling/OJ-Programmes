#include <cstdio>
#include <iostream>
#include <cstring>
#include <string>
#include <cstdlib>
#include <utility>
#include <cctype>
#include <algorithm>
#include <bitset>
#include <set>
#include <map>
#include <vector>
#include <queue>
#include <deque>
#include <stack>
#include <cmath>
#define LL long long
#define LB long double
#define x first
#define y second
#define Pair pair<int,LL>
#define pb push_back
#define pf push_front
#define mp make_pair
#define LOWBIT(x) x & (-x)
using namespace std;
  
const int MOD=100003;
const LL LINF=2e16;
const int INF=1e9;
const int magic=348;
const double eps=1e-10;
  
inline int getint()
{
    char ch;int res;bool f;
    while (!isdigit(ch=getchar()) && ch!='-') {}
    if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
    while (isdigit(ch=getchar())) res=res*10+ch-'0';
    return f?res:-res;
}
 
int head[100048],nxt[200048],to[200048],f[200048],tot=1;
inline void addedge(int s,int t,int cap)
{
    to[++tot]=t;nxt[tot]=head[s];head[s]=tot;f[tot]=cap;
    to[++tot]=s;nxt[tot]=head[t];head[t]=tot;f[tot]=0;
}
 
int n;
int a[1048][1048];
 
inline void Clear()
{
    tot=1;
    memset(head,0,sizeof(head));
}
 
int depth[100048];queue<int> q;
inline bool bfs()
{
    int i,x,y;
    for (i=0;i<=n+n+1;i++) depth[i]=-1;
    depth[0]=0;q.push(0);
    while (!q.empty())
    {
        x=q.front();q.pop();
        for (i=head[x];i;i=nxt[i])
        {
            y=to[i];
            if (depth[y]==-1 && f[i])
            {
                depth[y]=depth[x]+1;
                q.push(y);
            }
        }
    }
    if (depth[n+n+1]==-1) return false; else return true;
}
 
inline int dfs(int x,int maxf)
{
    if (x==n+n+1) return maxf;
    int i,y,minf,now,ans=0;
    for (i=head[x];i;i=nxt[i])
    {
        y=to[i];
        if (depth[y]==depth[x]+1 && f[i])
        {
            minf=min(maxf-ans,f[i]);
            now=dfs(y,minf);
            f[i]-=now;f[i^1]+=now;ans+=now;
        }
        if (ans>=maxf) return ans;
    }
    if (ans==0) depth[x]=0;
    return ans;
}
 
int main ()
{
    int i,j,ca;ca=getint();
    while (ca--)
    {
        n=getint();Clear();
        for (i=1;i<=n;i++)
            for (j=1;j<=n;j++)
            {
                a[i][j]=getint();
                if (a[i][j]) addedge(i,n+j,1);
            }
        for (i=1;i<=n;i++) addedge(0,i,1);
        for (i=1;i<=n;i++) addedge(n+i,n+n+1,1);
        int ans=0;
        while (bfs()) ans+=dfs(0,INF);
        if (ans>=n) printf("Yes\n"); else printf("No\n");
    }
    return 0;
}
