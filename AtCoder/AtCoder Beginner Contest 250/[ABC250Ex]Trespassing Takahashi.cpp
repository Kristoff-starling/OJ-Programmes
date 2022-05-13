#include <bits/stdc++.h>
#define LL long long
#define Pair pair<int,int>
#define pLL pair<LL,LL>
#define x first
#define y second
#define mp make_pair
#define pb push_back
#define rep(i,a,b) for (int i=(a);i<=(b);i++)
using namespace std;

const int MAXN=2e5;
const LL LINF=2e16;

int n,m,k,Q;

vector<Pair> v[MAXN+48];

struct edge
{
    int x,y;LL c;
    bool operator < (const edge &other) const {return c<other.c;}
}edge[MAXN+48];

struct query
{
    int x,y,id;LL t;
    bool operator < (const query &other) const {return t<other.t;}
}query[MAXN+48];
bool ans[MAXN+48];

LL dist[MAXN+48];
priority_queue<pLL> q;

void dijkstra()
{
    rep(i,0,n) dist[i]=LINF;
    dist[0]=0;q.push(mp(0,0));
    while (!q.empty())
    {
        int cur=q.top().y;LL dd=-q.top().x;q.pop();
        if (dd!=dist[cur]) continue;
        for (auto item : v[cur])
            if (dist[cur]+item.y<dist[item.x])
            {
                dist[item.x]=dist[cur]+item.y;
                q.push(mp(-dist[item.x],item.x));
            }
    }
}

namespace DSU
{
    int pre[MAXN+48];
    void init() {rep(i,1,n) pre[i]=i;}
    int find_anc(int x) {if (pre[x]!=x) pre[x]=find_anc(pre[x]);return pre[x];}
    void update(int x,int y) {x=find_anc(x);y=find_anc(y);pre[x]=y;}
    bool issame(int x,int y) {return find_anc(x)==find_anc(y);}
}

int main ()
{
    scanf("%d%d%d",&n,&m,&k);int x,y,c;
    rep(i,1,m)
    {
        scanf("%d%d%d",&x,&y,&c);
        edge[i]=(struct edge){.x=x,.y=y,.c=c};
        v[x].pb(mp(y,c));v[y].pb(mp(x,c));
    }
    rep(i,1,k) v[0].pb(mp(i,0)),v[i].pb(mp(0,0));
    dijkstra();
    rep(i,1,m) edge[i].c+=dist[edge[i].x]+dist[edge[i].y];
    sort(edge+1,edge+m+1);
    DSU::init();
    scanf("%d",&Q);
    rep(i,1,Q) scanf("%d%d%lld",&query[i].x,&query[i].y,&query[i].t),query[i].id=i;
    sort(query+1,query+Q+1);int ptr=1;
    rep(i,1,Q)
    {
        while (ptr<=m && edge[ptr].c<=query[i].t)
        {
            DSU::update(edge[ptr].x,edge[ptr].y);
            ptr++;
        }
        ans[query[i].id]=DSU::issame(query[i].x,query[i].y);
    }
    rep(i,1,Q) puts(ans[i]?"Yes":"No");
    return 0;
}