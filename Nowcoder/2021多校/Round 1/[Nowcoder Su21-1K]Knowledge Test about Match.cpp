#include <bits/stdc++.h>
#define LD long double
#define rep(i,a,b) for (int i=a;i<=b;i++)
#define REP(i,a,b) for (int i=a;i>=b;i--)
using namespace std;

const int MAXN=1000;
const int INF=1e9;
const LD eps=1e-6;

int n,a[MAXN+48];

int linkx[MAXN+48],linky[MAXN+48],pre[MAXN+48];
bool vx[MAXN+48],vy[MAXN+48];LD lx[MAXN+48],ly[MAXN+48],slack[MAXN+48];
LD ga[MAXN+48][MAXN+48];

bool smaller(LD x,LD y) {return x-y<-eps;}
bool larger(LD x,LD y) {return x-y>eps;}
bool equal(LD x,LD y) {return (!smaller(x,y)) && (!larger(x,y));}

LD table[MAXN+48][MAXN+48];
LD calc(int x,int y) {return table[x][y];}

inline void find_route(int &u)
{
	for (;u;swap(u,linkx[pre[u]]))
		linky[u]=pre[u];
}

int q[MAXN+48],head,tail;
inline void bfs(int u)
{
	head=tail=1;q[1]=u;vx[u]=true;LD t;
	for (;;)
	{
		while (head<=tail)
		{
			u=q[head++];
            rep(v,1,n)
			{
				if (vy[v] || (t=lx[u]+ly[v]-ga[u][v])>slack[v]) continue;
				pre[v]=u;
				if (equal(t,0))
				{
					if (!linky[v]) {find_route(v);return;}
					vy[v]=true;vx[linky[v]]=true;q[++tail]=linky[v];
				}
				else slack[v]=t;
			}
		}
		LD d=INF;
		rep(v,1,n) if (!vy[v] && slack[v]<d) d=slack[v],u=v;
        rep(i,1,n)
		{
			if (vx[i]) lx[i]-=d;
			if (vy[i]) ly[i]+=d; else slack[i]-=d;
		}
		if (!linky[u]) {find_route(u);return;}
		vy[u]=true;vx[linky[u]]=true;q[++tail]=linky[u];
	}
}

inline void KM()
{
	memset(linkx,0,sizeof(linkx));memset(linky,0,sizeof(linky));
    memset(vx,false,sizeof(vx));memset(vy,false,sizeof(vy));
	rep(i,1,n) lx[i]=-INF,ly[i]=0;
    rep(i,1,n) rep(j,1,n)
        lx[i]=max(lx[i],ga[i][j]);
    rep(i,1,n)
	{
		rep(j,1,n) vx[j]=vy[j]=false,slack[j]=INF;
		bfs(i);
	}
}

void doit_small()
{
    rep(i,1,n) rep(j,1,n) ga[i][j]=n*n-calc(i-1,a[j]);
    KM();
    rep(i,1,n) printf("%d ",a[linkx[i]]);puts("");
}

void doit_large()
{
    int t=2;
    sort(a+1,a+n+1);
    while (t--)
    {
        rep(i,1,n) rep(j,i+1,n)
            if (calc(i-1,a[i])+calc(j-1,a[j])>calc(i-1,a[j])+calc(j-1,a[i]))
                swap(a[i],a[j]);
    }
    rep(i,1,n) printf("%d ",a[i]);puts("");
}

int main ()
{
    int ca;scanf("%d",&ca);
    rep(i,0,MAXN) rep(j,0,MAXN) table[i][j]=((i>=j)?sqrt(i-j):sqrt(j-i));
    while (ca--)
    {
        scanf("%d",&n);rep(i,1,n) scanf("%d",a+i);
        if (n<=100) doit_small(); else doit_large();
    }
}