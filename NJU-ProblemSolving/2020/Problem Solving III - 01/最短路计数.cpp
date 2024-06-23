#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=a;i<=b;i++)
#define LL long long
#define pb push_back
#define Pair pair<int,int>
#define pLL pair<LL,LL>
#define x first
#define y second
#define mp make_pair
using namespace std;

const int MAXN=2e5;
const LL LINF=2e16;
const int MOD=100003;

int n,m;
vector<Pair> v[MAXN+48];
priority_queue<pLL> q;
LL dist[MAXN+48];int cnt[MAXN+48];
int seq[MAXN+48];

bool cmp_dist(int x,int y) {return dist[x]<dist[y];}

int main ()
{
    scanf("%d%d",&n,&m);int x,y,c;
    rep(i,1,m) scanf("%d%d%d",&x,&y,&c),v[x].pb(mp(y,c)),v[y].pb(mp(x,c));
    rep(i,1,n) dist[i]=LINF;dist[1]=0;q.push(mp(0,1));
    while (!q.empty())
    {
        int cur=q.top().y;LL dd=-q.top().x;q.pop();
        if (dd>dist[cur]) continue;
        for (auto item : v[cur]) if (dist[item.x]>dist[cur]+item.y) dist[item.x]=dist[cur]+item.y,q.push(mp(-dist[item.x],item.x));
    }
    rep(i,1,n) seq[i]=i;sort(seq+1,seq+n+1,cmp_dist);cnt[1]=1;
    rep(i,1,n)
    {
        int cur=seq[i];
        for (auto item : v[cur]) if (dist[cur]+item.y==dist[item.x]) cnt[item.x]+=cnt[cur]%=MOD;
    }
    rep(i,1,n) printf("%d\n",cnt[i]);return 0;
}