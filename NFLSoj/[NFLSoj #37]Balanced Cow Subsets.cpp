#include <cstdio>
#include <iostream>
#include <cstring>
#include <string>
#include <cstdlib>
#include <utility>
#include <vector>
#include <algorithm>
#include <queue>
#include <cmath>
#include <deque>
#include <stack>
#include <cmath>
#include <set>
#include <map>
#define LL long long
#define LB long double
#define Pair pair<int,int>
#define x first
#define y second
#define pb push_back
#define mp make_pair
#define LOWBIT(x) x & (-x)
using namespace std;
 
const int INF=2e9;
const LL LINF=2e16;
const int MOD=19999663;
const int magic=348;
const double eps=1e-10;
 
inline int getint()
{
    char ch;int res=0;bool f;
    while (!isdigit(ch=getchar()) && ch!='-') {}
    if (ch=='-') f=false,res=0; else res=ch-'0',f=true;
    while (isdigit(ch=getchar())) res=res*10+ch-'0';
    return f?res:-res;
}

int n;
int a[48];
int v[20000048],nxt[1000048],tot=0;int info[1000048];

inline int myabs(int x)
{
	return x>=0?x:-x;
}

LL ans=0;
int cnt=0;

const int p1=999169;
const int p2=997793;
//1968 lover

int ind[20000048],Nxt[1000048],Tot=0,Ind=0;Pair Info[1000048];
int hsh1[20000048],nnxt[1000048],ttot=0;Pair iinfo[1000048];
bool visited[2000048];

inline int h1(int x,int y)
{
	return ((long long)x*p1+(long long)y*p2)%MOD;
}
inline int h2(int x,int y)
{
	return ((long long)x*p2+(long long)y*p1)%MOD;
}

void add_ind(int num,int x,int y)
{
	++Tot;
	Nxt[Tot]=ind[num];
	ind[num]=Tot;
	Info[Tot]=mp(x,y);
}
void add_hsh(int num,int x,int y)
{
	++ttot;
	nnxt[ttot]=hsh1[num];
	hsh1[num]=ttot;
	iinfo[ttot]=mp(x,y);
}
void add_v(int num,int x)
{
	++tot;
	nxt[tot]=v[num];
	v[num]=tot;
	info[tot]=x;
}
	

inline int hh(LL x)
{
	int num=((long long)x*p2+p1)%MOD;
	for (int i=ind[num];i;i=Nxt[i])
		if (Info[i].x==x) return Info[i].y;
	add_ind(num,x,++Ind);
	return Ind;
}

bool judge(int x,int y)
{
	int i,num=h1(x,y);
	for (i=hsh1[num];i;i=nnxt[i])
		if (iinfo[i]==mp(x,y)) return false;
	return true;
}

void update(int x,int y)
{
	add_hsh(h1(x,y),x,y);
}

void dfs(int cur,int cnt,int delta,int Mask)
{
	if (cur>n/2)
	{
		if (judge(delta,Mask))
		{
			add_v(hh(delta),Mask);
			update(delta,Mask);
		}
		return;
	}
	dfs(cur+1,cnt,delta,Mask);
	dfs(cur+1,cnt+1,delta+a[cur],Mask|(1<<(cur-1)));
	dfs(cur+1,cnt+1,myabs(delta-a[cur]),Mask|(1<<(cur-1)));
}

void dfss(int cur,int cnt,int delta,int Mask)
{
	if (cur>n/2)
	{
		if (judge(delta,Mask))
		{
			add_v(hh(delta),Mask);
			update(delta,Mask);
		}
		return;
	}
	dfss(cur+1,cnt,delta,Mask);
	dfss(cur+1,cnt+1,delta+a[cur],Mask|(1<<(cur-1)));
	dfss(cur+1,cnt+1,myabs(delta-a[cur]),Mask|(1<<(cur-1)));
}

void dfs2(int cur,int cnt,int delta,int Mask)
{
	int i;
	if (cur>n)
	{
		int dd=hh(delta);
		for (i=v[dd];i;i=nxt[i])
			if (!visited[info[i]|Mask])
			{
				ans++;
				visited[info[i]|Mask]=true;
			}
		return;	
	}
	dfs2(cur+1,cnt,delta,Mask);
	dfs2(cur+1,cnt+1,delta+a[cur],Mask|(1<<(cur-1)));
	dfs2(cur+1,cnt+1,myabs(delta-a[cur]),Mask|(1<<(cur-1)));
}

void ddfs(int cur,int cnt,int delta,int Mask)
{
	if (cur==n+1)
	{
		if (!visited[Mask] && delta==0)
		{
			visited[Mask]=true;
			ans++;
		}
		return;
	}
	ddfs(cur+1,cnt,delta,Mask);
	ddfs(cur+1,cnt+1,delta+a[cur],Mask|(1<<(cur-1)));
	ddfs(cur+1,cnt+1,myabs(delta-a[cur]),Mask|(1<<(cur-1)));
}

int main ()
{
	int i,j;
	n=getint();
	for (i=1;i<=n;i++) a[i]=getint();
	dfs(1,0,0,0);
	dfs2(n/2+1,0,0,0);
	cout<<ans-1<<endl;
	return 0;
}
