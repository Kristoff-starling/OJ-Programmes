#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=a;i<=b;i++)
#define pb push_back
using namespace std;

const int MAXN=2e6;
const int MOD=1e9+7;

int n,m,N;
vector<int> v[MAXN+48][10];
bool visited[MAXN+48];int dist[MAXN+48];
int bits[48],btot;

void addedge(int cur,int to,int b)
{
    if (b==1) {v[cur][bits[b]].pb(to);return;}
    v[cur][bits[b]].pb(++N);
    addedge(N,to,b-1);
}

struct node
{
    int val;
    vector<int> nodes;
};

node q[MAXN+48];int head,tail;

int main ()
{
    scanf("%d%d",&n,&m);N=n;int x,y,w;
    rep(i,1,m)
    {
        scanf("%d%d%d",&x,&y,&w);
        btot=0;while (w) bits[++btot]=w%10,w/=10;
        addedge(x,y,btot);addedge(y,x,btot);
    }
    head=tail=1;q[1].val=0;q[1].nodes.pb(1);visited[1]=true;
    while (head<=tail)
    {
        node info=q[head++];
        rep(nxt,0,9)
        {
            node ins;ins.val=(1ll*info.val*10%MOD+nxt)%MOD;ins.nodes.clear();
            for (auto cur : info.nodes)
                for (auto to : v[cur][nxt])
                    if (!visited[to])
                    {
                        visited[to]=true;dist[to]=ins.val;
                        ins.nodes.pb(to);
                    }
            if (int(ins.nodes.size())) q[++tail]=ins;
        }
    }
    rep(i,2,n) if (visited[i]) printf("%d\n",dist[i]); else puts("-1");
    return 0;
}