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
#define pb push_back
#define pf push_front
#define mp make_pair
#define LOWBIT(x) x & (-x)
using namespace std;

const int MOD=1e9+7;
const LL LINF=2e16;
const int INF=2e9;
const int magic=348;
const double eps=1e-10;

inline int getint()
{
	char ch;int res;bool f;
	while (!isdigit(ch=getchar()) && ch!='-') {}
	if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
	while (isdigit(ch=getchar())) res=res*10+ch-'0';
	return f?res:-res;
}

int n,m,bx,by,xx,tot=0;
Pair a[48],Rope[10048];
bool used[48];int b[48];
int s[10048],tt=0;
int ans=INF;

void init()
{
	tot=0;
	for (int i=1;i<=n;i++)
		if (used[i]) b[++tot]=a[i].y;
	b[0]=-1;b[++tot]=1e9;
}

int find_pos(int x1,int y1,int x2,int y2)
{
	if (x1>xx && x2>xx) return -1;
	if (x1<=xx && x2<=xx) return -1;
	if (x1==x2) return -1;
	double k=double(y1-y2)*1.0/double(x1-x2);
	double bb=double(y1)-k*x1;
	double yy=k*xx+bb;
	int l=1,r=tot,mid;
	while (l<=r)
	{
		mid=(l+r)>>1;
		if (yy>b[mid-1] && b[mid]>yy) return mid;
		if (yy<b[mid-1]) r=mid-1; else l=mid+1;
	}
	return -1;
}

bool ff=false;
bool judge()
{
	int i,pos;
	tt=0;
	for (i=1;i<=m;i++)
	{
		pos=find_pos(Rope[i].x,Rope[i].y,Rope[i+1].x,Rope[i+1].y);
		if (pos==-1) continue;
		if (tt && s[tt]==pos) tt--; else s[++tt]=pos;
	}
	if (!tt) return true; else return false;
}

void dfs(int cur,int cnt)
{
	if (cur==n+1)
	{
		init();
		if (cnt==0) ff=true;
		if (judge()) ans=min(ans,n-cnt);
		return;
	}
	used[cur]=true;
	dfs(cur+1,cnt+1);
	used[cur]=false;
	dfs(cur+1,cnt);
}

int main ()
{
	int i;
	n=getint();m=getint();bx=getint();by=getint();
	for (i=1;i<=n;i++) a[i].x=getint(),a[i].y=getint();
	xx=a[1].x;
	sort(a+1,a+n+1);
	for (i=1;i<=m+1;i++) Rope[i].x=getint(),Rope[i].y=getint();
	dfs(1,0);
	printf("%d\n",ans);
	return 0;
}

