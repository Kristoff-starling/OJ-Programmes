#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=a;i<=b;i++)
#define Pair pair<int,int>
#define pb push_back
#define mp make_pair
#define x first
#define y second
#define ll long long
using namespace std;

int n,m,a,b,c,d,p;

const int MAXN=5000;

namespace DSU
{
    int pre[MAXN*2+48];
    void init() {rep(i,1,n+m) pre[i]=i;}
    int find_anc(int x) {if (pre[x]!=x) pre[x]=find_anc(pre[x]);return pre[x];}
    bool issame(int x,int y) {return find_anc(x)==find_anc(y);}
    void update(int x,int y) {x=find_anc(x);y=find_anc(y);pre[x]=y;}
}

int A[MAXN*MAXN+48];

int calc(int x,int y) {return A[(x-1)*m+y];}

vector<Pair> v[100048];

int main ()
{
    scanf("%d%d%d%d%d%d%d",&n,&m,&a,&b,&c,&d,&p);
    A[0]=a;
	for (int i=1;i<=n*m;i++) {
		ll tmp=A[i-1];
		A[i]=(tmp*tmp%p*b%p+tmp*c%p+d)%p;
	}
    rep(i,1,n) rep(j,1,m) v[calc(i,j)].pb(mp(i,j));
    int ans=0,cnt=0;
    DSU::init();
    rep(i,0,p-1) for (auto item : v[i])
    {
        if (!DSU::issame(item.x,n+item.y))
        {
            cnt++;
            ans+=i;
            DSU::update(item.x,item.y+n);
        }
        if (cnt==n+m-1) break;
    }
    printf("%d\n",ans);
    return 0;
}