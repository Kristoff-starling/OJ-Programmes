#include <bits/stdc++.h>
#define Pair pair<int,int>
#define x first
#define y second
#define pb push_back
#define mp make_pair
#define rep(i,a,b) for (int i=(a);i<=(b);i++)
using namespace std;

int n;
char s[200][48];
int ga[200][200];
vector<Pair> v[200];

struct edge
{
    int x,y,c;
    bool operator < (const edge &other) const {return c<other.c;}
}b[100048];int tot;

int dp[48][48];
int calc(int id1,int id2)
{
    char *s1=s[id1],*s2=s[id2];
    int l1=strlen(s1+1),l2=strlen(s2+1);
    rep(i,0,l1) dp[i][0]=i;
    rep(j,0,l2) dp[0][j]=j;
    rep(i,1,l1) rep(j,1,l2)
    {
        dp[i][j]=dp[i-1][j]+1;
        dp[i][j]=min(dp[i][j],dp[i][j-1]+1);
        dp[i][j]=min(dp[i][j],dp[i-1][j-1]+(s1[i]==s2[j]?0:1));
    }
    return dp[l1][l2];
}

namespace DSU
{
    int pre[200];
    void init() {rep(i,1,n) pre[i]=i;}
    int find_anc(int x) {if (pre[x]!=x) pre[x]=find_anc(pre[x]);return pre[x];}
    void update(int x,int y) {x=find_anc(x);y=find_anc(y);pre[x]=y;}
    bool issame(int x,int y) {return find_anc(x)==find_anc(y);}
}

int ans,last;

void dfs(int cur,int father)
{
    if (last!=0) ans+=ga[last][cur];
    last=cur;
    for (auto item : v[cur]) if (item.x != father) dfs(item.x,cur);
}

int main ()
{
    int ca;scanf("%d",&ca);
    while (ca--)
    {
        scanf("%d",&n);
        rep(i,1,n) scanf("%s",s[i]+1);
        rep(i,1,n) v[i].clear();
        tot=0;
        rep(i,1,n-1) rep(j,i+1,n)
        {
            int c=calc(i,j);
            ga[i][j]=ga[j][i]=c;
            b[++tot].x=i;b[tot].y=j;b[tot].c=c;
        }
        sort(b+1,b+tot+1);
        DSU::init();int cnt=0;
        for (int i=1;i<=tot && cnt<n-1;i++)
        {
            if (!DSU::issame(b[i].x,b[i].y))
            {
                cnt++;
                DSU::update(b[i].x,b[i].y);
                v[b[i].x].pb(mp(b[i].y,b[i].c));
                v[b[i].y].pb(mp(b[i].x,b[i].c));
            }
        }
        ans=0;last=0;
        dfs(1,0);
        ans+=ga[last][1];
        printf("%d\n",ans);
    }
    return 0;
}