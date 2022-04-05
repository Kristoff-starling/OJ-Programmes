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
#define Pair pair<int,int>
#define pLL pair<LL,LL>
#define pii pair<double,double>
#define pb push_back
#define pf push_front
#define mp make_pair
#define LOWBIT(x) x & (-x)
using namespace std;

const int MOD=1e9+9;
const LL LINF=2e16;
const int INF=2e9;
const int magic=348;
const double eps=1e-10;
const double pi=acos(-1);
const int T=100;
const double Tmin=1;
const double delta=0.89;

inline int getint()
{
    char ch;int res;bool f;
    while (!isdigit(ch=getchar()) && ch!='-') {}
    if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
    while (isdigit(ch=getchar())) res=res*10+ch-'0';
    return f?res:-res;
}

double ans,fans=INF;
inline double calc_dist(double x1,double y1,double x2,double y2) {return sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));}

int n,R,N;
pii a[248];

int head[648],cur[648],to[800048],nxt[800048],f[800048],tot;
inline void addedge(int s,int t,int cap)
{
	to[++tot]=t;nxt[tot]=head[s];head[s]=tot;f[tot]=cap;
	to[++tot]=s;nxt[tot]=head[t];head[t]=tot;f[tot]=0;
}

int q[100048],Head,Tail;int depth[648];
inline bool bfs()
{
	int i,x,y;
	for (i=0;i<=N;i++) depth[i]=-1;
	depth[0]=0;Head=Tail=1;q[1]=0;
	while (Head<=Tail)
	{
		x=q[Head++];
		for (i=head[x];i;i=nxt[i])
		{
			y=to[i];
			if (depth[y]==-1 && f[i])
			{
				depth[y]=depth[x]+1;
				q[++Tail]=y;
			}
		}
	}
	if (depth[N]==-1) return false; else return true;
}

inline int dfs(int x,int maxf)
{
	if (!maxf || x==N) return maxf;
	int y,minf,now,ans=0;
	for (int &i=cur[x];i;i=nxt[i])
	{
		y=to[i];
		if (depth[y]==depth[x]+1 && f[i])
		{
			minf=min(maxf-ans,f[i]);
			now=dfs(y,minf);
			f[i]-=now;f[i^1]+=now;ans+=now;
		}
	}
	if (!ans) depth[x]=0;
	return ans;
}

pii point[248];
struct Edge
{
	int pt1,pt2;double len;
	inline bool operator < (const Edge &x) const {return len<x.len;}
}edge[60048];int etot=0;

inline bool check(int ind)
{
	int i;
	memset(head,0,sizeof(head));tot=1;
	for (i=1;i<=n;i++) addedge(0,i,1);
	for (i=n+1;i<=n*2;i++) addedge(i,N,1);
	for (i=1;i<=ind;i++) addedge(edge[i].pt1,edge[i].pt2,1);
	int ans=0;
	while (bfs())
	{
		for (i=0;i<=N;i++) cur[i]=head[i];
		ans+=dfs(0,2e9);
	}
	if (ans>=n) return true; else return false;
}

inline double getans(double angle)
{
	memset(head,0,sizeof(head));tot=1;
	double gap=pi*2.0/n,cg;int cnt,i,j;
	for (cg=angle,cnt=1;cnt<=n;cnt++)
	{
		point[cnt]=mp(cos(cg)*R,sin(cg)*R);
		cg+=gap;while (cg>=pi*2) cg-=pi*2;
	}
	N=n*2+1;etot=0;
	for (i=1;i<=n;i++)
		for (j=1;j<=n;j++)
		{
			edge[++etot]=Edge{i,n+j,calc_dist(a[i].x,a[i].y,point[j].x,point[j].y)};
		}
	sort(edge+1,edge+etot+1);
	int l=1,r=etot,mid;double res=INF;
	while (r && edge[r].len>fans) r--;
	if (!r) return INF;
	while (l<=r)
	{
		mid=(l+r)>>1;
		if (check(mid)) res=edge[mid].len,r=mid-1; else l=mid+1;
	}
	return res;
}

int main ()
{
	srand(time(NULL));
	n=getint();R=getint();int i;
	for (i=1;i<=n;i++) a[i].x=getint(),a[i].y=getint();
	double end=0.9*(CLOCKS_PER_SEC);
	double range,angle,t,dd;
	while (clock()<=end)
	{
		t=T;
		range=pi*2.0/n;angle=double(rand())*1.0/RAND_MAX;
		ans=getans(range*angle);fans=min(ans,fans);dd=0.5;
		while (t>Tmin)
		{
			double newangle=angle+dd;
			if (0<=newangle && newangle<1)
			{
				double newres=getans(range*newangle);
				if (newres<=ans)
				{
					ans=newres;
					angle=newangle;
					fans=min(fans,newres);
				}
				else
				{
					double p=exp((ans-newres)/t);
					if (double(rand())/RAND_MAX<p)
					{
						ans=newres;
						angle=newangle;
					}
				}
			}
			newangle=angle-dd;
			if (0<=newangle && newangle<1)
			{
				double newres=getans(range*newangle);
				if (newres<=ans)
				{
					ans=newres;
					angle=newangle;
					fans=min(fans,newres);
				}
				else
				{
					double p=exp((ans-newres)/t);
					if (double(rand())/RAND_MAX<p)
					{
						ans=newres;
						angle=newangle;
					}
				}
			}
			t*=delta;dd*=0.5;
			if (clock()>end) break;
		}
	}
	printf("%.10lf\n",fans);
	return 0;
}
