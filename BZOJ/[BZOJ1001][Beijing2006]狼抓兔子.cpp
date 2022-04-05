#include <cstdio>
#include <iostream>
#include <cstring>
#include <string>
#include <cstdlib>
#include <utility>
#include <vector>
#include <algorithm>
#include <queue>
#include <cmath>
#include <deque>
#include <stack>
#include <cmath>
#include <set>
#include <map>
#define LL long long
#define LB long double
#define Pair pair<int,int>
#define x first
#define y second
#define pb push_back
#define mp make_pair
#define LOWBIT(x) x & (-x)
using namespace std;
 
const int INF=2e9;
const LL LINF=2e16;
const int MOD=1e9+7;
const int magic=348;
const double eps=1e-10;
 
inline int getint()
{
    char ch;int res=0;bool f;
    while (!isdigit(ch=getchar()) && ch!='-') {}
    if (ch=='-') f=false,res=0; else res=ch-'0',f=true;
    while (isdigit(ch=getchar())) res=res*10+ch-'0';
    return f?res:-res;
}
 
int n,m;
int S,T;
 
int head[2500048],to[5000048],nxt[5000048],f[5000048],tot=0;
inline void addedge(int s,int t,int l)
{
    to[++tot]=t;nxt[tot]=head[s];head[s]=tot;f[tot]=l;
    to[++tot]=s;nxt[tot]=head[t];head[t]=tot;f[tot]=l;
}
 
int dist[2500048];
bool visited[2500048];
priority_queue<Pair> q;
 
int dijkstra()
{
    int i,y,cur;
    for (i=1;i<=(n-1)*(m-1)*2+48;i++) dist[i]=INF;
    dist[S]=0;
    q.push(mp(0,S));
    memset(visited,false,sizeof(visited));
    while (!q.empty())
    {
        Pair res=q.top();q.pop();
        cur=res.y;
        if (visited[cur]) continue;
        visited[cur]=true;
        for (i=head[cur];i;i=nxt[i])
        {
            y=to[i];
            if (dist[cur]+f[i]<dist[y])
            {
                dist[y]=dist[cur]+f[i];
                q.push(mp(-dist[y],y));
            }
        }
    }
    return dist[T];
}
 
int main ()
{
    int i,j,len;
    n=getint();m=getint();
    S=m*2*n+1;T=m*2*n+2;
    for (i=1;i<=n;i++)
        for (j=1;j<=m-1;j++)
        {
            len=getint();
            if (i==1) addedge(S,j*2,len);
            if (i==n) addedge((m-1)*2*(n-2)+(j-1)*2+1,T,len);
            if (2<=i && i<=n-1) addedge((m-1)*2*(i-2)+(j-1)*2+1,(m-1)*2*(i-1)+j*2,len);
        }
    for (i=1;i<=n-1;i++)
        for (j=1;j<=m;j++)
        {
            len=getint();
            if (j==1) addedge((m-1)*2*(i-1)+1,T,len);
            if (j==m) addedge((m-1)*2*i,S,len);
            if (2<=j && j<=m-1) addedge((m-1)*2*(i-1)+(j-1)*2,(m-1)*2*(i-1)+(j-1)*2+1,len);
        }
    for (i=1;i<=n-1;i++)
        for (j=1;j<=m-1;j++)
        {
            len=getint();
            addedge((m-1)*2*(i-1)+(j-1)*2+1,(m-1)*2*(i-1)+j*2,len);
        }
    printf("%d\n",dijkstra());
    return 0;
}
