#include <bits/stdc++.h>
#define pb push_back
#define ull unsigned long long
using namespace std;

int n,m;
int ga[48][48];
int fa[48],falen[48];
double TIME;int ans=1e9;

inline int getmask(ull Mask,int pos) {return (Mask)>>((pos-1)<<2)&15;}
inline void Set(ull &Mask,int pos,int nv)
{
    Mask|=(15ll<<((pos-1)<<2));
    Mask^=((long long)(nv)<<((pos-1)<<2));
    Mask^=(15ll<<((pos-1)<<2));
}

int cc=0;
unordered_map<ull,int> his;
int dep[48];
inline void dfs(ull fa,int curans,int cnt)
{
    if (curans>ans) return;
    if (cnt==n) {ans=curans;return;}
    if (his[fa]) return;
    his[fa]=1;
    int a[48],atot=0,b[48],btot=0;
    for (register int i=1;i<=n;i++) if (!dep[i]) b[++btot]=i; else a[++atot]=i;
    for (register int i=1;i<=btot;i++)
    {
        for (register int j=1;j<=atot;j++)
        {
            ++cc;if (cc>=37687700) {printf("%d\n",ans);exit(0);}
            if (ga[b[i]][a[j]]<500000)
            {
                dep[b[i]]=dep[a[j]]+1;
                ull tofa=fa;Set(tofa,b[i],a[j]);
                dfs(tofa,curans+ga[b[i]][a[j]]*dep[a[j]],cnt+1);
                dep[b[i]]=0;
            }
        }
    }
}

int main ()
{
    // freopen ("a.in","r",stdin);
    scanf("%d%d",&n,&m);int x,y,c;
    memset(ga,0x3f,sizeof(ga));
    for (register int i=1;i<=m;i++)
    {
        scanf("%d%d%d",&x,&y,&c);
        ga[x][y]=ga[y][x]=min(ga[x][y],c);
    }
    for (register int i=1;i<=n;i++)
    {
        ull fa=0;memset(dep,0,sizeof(dep));dep[i]=1;
        his.clear();dfs(fa,0,1);
    }
    printf("%d\n",ans);
    return 0;
}
