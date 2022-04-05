#include <cstdio>
#include <iostream>
#include <cstring>
#include <string>
#include <cstdlib>
#include <utility>
#include <cmath>
#include <algorithm>
#include <vector>
#include <queue>
#include <deque>
#include <stack>
#define pb push_back
using namespace std;

int n,k;

char s[48];

struct node
{
    int nxt[10];
    int fail;bool isdanger;
    inline void clear() {memset(nxt,0,sizeof(nxt));fail=0;isdanger=false;}
}trie[2000048];int tot=1;

inline int Create()
{
    ++tot;
    trie[tot].clear();
    return tot;
}

inline void insert()
{
    int len=strlen(s+1),cur=1;
    for (register int i=1;i<=len;i++)
    {
        int w=s[i]-'a'+1;
        if (!trie[cur].nxt[w]) trie[cur].nxt[w]=Create();
        cur=trie[cur].nxt[w];
    }
    trie[cur].isdanger=true;
}

int head,tail,q[2000048];
inline void construct_fail()
{
    q[1]=1;head=tail=1;
    while (head<=tail)
    {
        int cur=q[head++];
        int tmp=cur;
        while (tmp && !trie[cur].isdanger) tmp=trie[tmp].fail,trie[cur].isdanger|=trie[tmp].isdanger;
        for (register int i=1;i<=k;i++)
            if (trie[cur].nxt[i])
            {
                int tmp=trie[cur].fail;
                while (tmp && !trie[cur].nxt[i]) tmp=trie[cur].fail;
                trie[trie[cur].nxt[i]].fail=((!tmp)?1:trie[tmp].nxt[i]);
                q[++tail]=trie[cur].nxt[i];
            }
            else
                trie[cur].nxt[i]=(cur==1?1:trie[trie[cur].fail].nxt[i]);
    }
}

int id=0;
bool type[2000048];
vector<int> v[2000048];

int bel[2000048],cntedge[2000048],cntv[2000048];
int dfn[2000048],low[2000048],ind;
int sta[2000048],stot;
bool visited[2000048];

inline void tarjan(int cur)
{
    sta[++stot]=cur;
    dfn[cur]=low[cur]=++ind;
    visited[cur]=true;
    for (register int i=1;i<=k;i++)
    {
        register int y=trie[cur].nxt[i];
        if (!dfn[y] && !trie[y].isdanger)
        {
            tarjan(y);
            low[cur]=min(low[cur],low[y]);
        }
        else if (visited[y]) {low[cur]=min(low[cur],low[y]);}
    }
    if (dfn[cur]==low[cur])
    {
        ++id;int vv;
        do
        {
            vv=sta[stot--];
            bel[vv]=id;
            visited[vv]=false;

            cntv[id]++;
        }
        while (vv!=cur);
        if (cntv[id]==1)
        {
            type[id]=false;
            for (register int i=1;i<=k;i++) if (trie[cur].nxt[i]==cur) {type[id]=true;break;}
        }
        else
        {
        	type[id]=true;
        }
    }    
}

int depth[2000048];
inline int solve_dist(int cur)
{
    if (depth[cur]!=-1) return depth[cur];
    depth[cur]=(type[cur]?1:0);int add=0;
    for (register int i=0;i<int(v[cur].size());i++) add=max(add,solve_dist(v[cur][i]));
    depth[cur]+=add;return depth[cur];
}

int dp[2000048];
inline int solve(int cur)
{
    if (dp[cur]!=-1) return dp[cur];
    dp[cur]=0;
    for (register int i=0;i<int(v[cur].size());i++)
        dp[cur]+=solve(v[cur][i]);
    return dp[cur];
}

int main ()
{
    scanf("%d%d",&k,&n);trie[1].clear();
    for (register int i=1;i<=n;i++)
    {
        scanf("%s",s+1);
        insert();
    }
    construct_fail();
    ind=0;
    for (register int i=1;i<=tot;i++)
        if (!dfn[i] && !trie[i].isdanger) tarjan(i);
    for (register int i=1;i<=tot;i++)
    {
        if (trie[i].isdanger) continue;
        for (register int j=1;j<=k;j++)
        {
            if (trie[trie[i].nxt[j]].isdanger) continue;
            int x=bel[i],y=bel[trie[i].nxt[j]];
            if (x!=y) v[x].pb(y); else cntedge[x]++;
        }
    }
    for (register int i=1;i<=id;i++)
        if (cntedge[i]>cntv[i]) {printf("-1\n");return 0;}
    memset(depth,-1,sizeof(dp));
    for (register int i=1;i<=id;i++)
    {
        depth[i]=solve_dist(i);
        if (depth[i]>2) {printf("-1\n");return 0;}
    }
    int ans=0;
    for (register int i=1;i<=id;i++) if (type[i] && depth[i]==2) ans++;
    memset(dp,-1,sizeof(dp));
    for (register int i=1;i<=id;i++) if (type[i] && depth[i]==1) dp[i]=1;
    for (register int i=1;i<=id;i++)
    {
        dp[i]=solve(i);
        if (type[i]) ans+=dp[i];
    }
    printf("%d\n",ans);
    return 0;
}