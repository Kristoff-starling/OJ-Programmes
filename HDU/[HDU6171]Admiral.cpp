#include <bits/stdc++.h>
using namespace std;

#define LL long long
#define LB long double
#define ull unsigned long long
#define x first
#define y second
#define pb push_back
#define pf push_front
#define mp make_pair
#define Pair pair<int,int>
#define pLL pair<LL,LL>
#define pii pair<double,double>

const int INF=2e9;
const LL LINF=2e16;
const int magic=348;
const int MOD=998244353;
const double eps=1e-10;
const double pi=acos(-1);

inline int getint()
{
	bool f;char ch;int res;
	while (!isdigit(ch=getchar()) && ch!='-') {}
	if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
	while (isdigit(ch=getchar())) res=res*10+ch-'0';
	return f?res:-res;
}

int ca,sx,sy;
int a[48],tar[48];

map<ull,int> Mp;
ull Tar;

const int hp=19260817;
inline ull gethash(int cur[])
{
	ull res=0;
	for (register int i=1;i<=21;i++) res=res*hp+cur[i];
	return res;
}

inline int getind(int i,int j) {return i*(i-1)/2+j;}

int dx[]={-1,-1,1,1},dy[]={-1,0,0,1};

inline void dfs(int x,int y,int px,int py,int step)
{
	if (step)
	{
		ull ci=gethash(a);
		if (!Mp[ci]) Mp[ci]=step;
	}
	if (step>=10) return;
	int nx,ny;
	for (register int i=0;i<=3;i++)
	{
		nx=x+dx[i];ny=y+dy[i];
		if (1<=nx && nx<=6 && 1<=ny && ny<=nx && !(nx==px && ny==py))
		{
			swap(a[getind(x,y)],a[getind(nx,ny)]);
			dfs(nx,ny,x,y,step+1);
			swap(a[getind(x,y)],a[getind(nx,ny)]);
		}
	}
}

int ans;

inline void dfs2(int x,int y,int px,int py,int step)
{
	ull ci=gethash(tar);int res=Mp[ci];
	if (res) ans=min(ans,step+res);
	if (step>=10) return;
	int nx,ny;
	for (register int i=0;i<=3;i++)
	{
		nx=x+dx[i];ny=y+dy[i];
		if (1<=nx && nx<=6 && 1<=ny && ny<=nx && !(nx==px && ny==py))
		{
			swap(tar[getind(x,y)],tar[getind(nx,ny)]);
			dfs2(nx,ny,x,y,step+1);
			swap(tar[getind(x,y)],tar[getind(nx,ny)]);
		}
	}
}

int main ()
{
	ca=getint();int i,j;
	for (i=1;i<=6;i++)
		for (j=1;j<=i;j++)
			tar[getind(i,j)]=i-1;
	Tar=gethash(tar);
	while (ca--)
	{
		for (i=1;i<=21;i++) a[i]=getint();
		if (gethash(a)==Tar) {puts("0");continue;}
		for (i=1;i<=6;i++)
			for (j=1;j<=i;j++)
				if (!a[getind(i,j)]) {sx=i;sy=j;break;}
		Mp.clear();
		dfs(sx,sy,0,0,0);
		ans=21;
		dfs2(1,1,0,0,0);
		if (ans>20) puts("too difficult"); else printf("%d\n",ans);
	}
	return 0;
}
