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
const int INF=2e9;
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
 
inline LL getLL()
{
    char ch;LL res;bool f;
    while (!isdigit(ch=getchar()) && ch!='-') {}
    if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
    while (isdigit(ch=getchar())) res=res*10+ch-'0';
    return f?res:-res;
}
 
int n,e;
vector<Pair> v[100048];
LL depth[100048];bool visited[100048];
 
namespace LinerBase
{
    LL d[70];
    inline void init() {memset(d,0ll,sizeof(d));}
    inline void Insert(LL x)
    {
        int i;
        for (i=62;i>=0;i--)
            if ((x>>i)&1)
            {
                if (d[i])
                    x^=d[i];
                else
                {
                    d[i]=x;
                    break;
                }
            }
    }
    inline LL query(LL x)
    {
        LL res=x;int i;
        for (i=62;i>=0;i--)
            if ((res^d[i])>res) res^=d[i];
        return res;
    }
}
 
void dfs(int cur)
{
    visited[cur]=true;
    int i,to;
    for (i=0;i<int(v[cur].size());i++)
    {
        to=v[cur][i].x;
        if (!visited[to])
        {
            depth[to]=depth[cur]^v[cur][i].y;
            dfs(to);
        }
        else
        {
            LinerBase::Insert(depth[cur]^depth[to]^v[cur][i].y);
        }
    }
}
 
int main ()
{
    int i,x,y;LL c;
    n=getint();e=getint();
    for (i=1;i<=e;i++)
    {
        x=getint();y=getint();c=getLL();
        v[x].pb(mp(y,c));v[y].pb(mp(x,c));
    }
    LinerBase::init();memset(visited,false,sizeof(visited));
    depth[1]=0;dfs(1);
    printf("%lld\n",LinerBase::query(depth[n]));
    return 0;
}
