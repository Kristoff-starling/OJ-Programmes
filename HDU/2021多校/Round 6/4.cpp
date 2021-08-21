#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=a;i<=b;i++)
#define pb push_back
using namespace std;

const int MAXN=1000;

int n,k;
int len[MAXN+48],cnt[MAXN+48];
int seq[MAXN*MAXN+48],tot;

struct node
{
    int len,id;
    node () {}
    node (int _len,int _id) {len=_len;id=_id;}
    bool operator < (const node &other) const {return len>other.len;}
}t[MAXN+48];

bool visited[MAXN+48][MAXN+48];
vector<int> v[MAXN+48];

int Map[MAXN+48][MAXN+48];

int main ()
{
    int ca;scanf("%d",&ca);
    rep(Case,1,ca)
    {
        printf("Case #%d:\n",Case);
        scanf("%d%d",&n,&k);rep(i,1,k) scanf("%d",len+i),t[i]=node(len[i],i);
        rep(i,1,(n-1)/2) Map[i][1]=1;
        rep(i,2,n)
        {
            int yy=i;
            bool f;
            if (i&1) f=true; else f=false;
            rep(j,1,(n-1)/2)
            {
                Map[j][yy]=i;
                if (f) yy-=2; else yy+=2;
                if (yy==1) yy=2,f=false;
                if (yy==n+1) yy=n,f=true;
            }
        }
        rep(i,1,(n-1)/2) rep(j,1,n) seq[(i-1)*n+j]=Map[i][j];
        seq[n*(n-1)/2+1]=1;
        rep(i,1,k) v[i].clear();
        int pt=1;
        rep(i,1,k)
        {
            rep(j,pt,pt+len[i]) v[i].pb(seq[j]);
            pt=pt+t[i].len;
        }
        rep(i,1,k)
        {
            for (int j=0;j<=int(v[i].size())-1;j++)
            {
                printf("%d",v[i][j]);
                if (j==int(v[i].size())-1) puts(""); else printf(" ");
            }
        }
    }
    return 0;
}