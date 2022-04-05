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

const int MOD=123456789;
const LL LINF=2e16;
const int INF=2e9;
const int magic=348;
const double eps=1e-10;
const double pi=3.14159265;

inline int getint()
{
    char ch;int res;bool f;
    while (!isdigit(ch=getchar()) && ch!='-') {}
    if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
    while (isdigit(ch=getchar())) res=res*10+ch-'0';
    return f?res:-res;
}

int n,m;
char s1[248][248],s2[248][248];
bool exist[200048];
int d[200048],cnt[200048];

inline int myabs(int x) {return x>=0?x:-x;}

namespace DSU
{
	int pre[200048];
	inline void init() {for (register int i=1;i<=(n+1)*(m+1)*2;i++) pre[i]=i;}
	inline int find_anc(int x) {if (pre[x]!=x) pre[x]=find_anc(pre[x]);return pre[x];}
	inline void update(int x,int y) {x=find_anc(x);y=find_anc(y);pre[x]=y;}
}

inline int getind(int x,int y,int t)
{
	int res=(x-1)*(m+1)+y;
	if (t==2) res+=(n+1)*(m+1);
	return res;
}

inline void doit1(int x,int y)
{
	exist[getind(x+1,y,1)]=true;exist[getind(x+1,y,2)]=true;
	exist[getind(x,y+1,1)]=true;exist[getind(x,y+1,2)]=true;
	DSU::update(getind(x+1,y,1),getind(x,y+1,2));
	DSU::update(getind(x+1,y,2),getind(x,y+1,1));
	d[getind(x+1,y,1)]++;d[getind(x,y+1,1)]++;
	d[getind(x+1,y,2)]--;d[getind(x,y+1,2)]--;
}

inline void doit2(int x,int y)
{
	exist[getind(x+1,y,1)]=true;exist[getind(x+1,y,2)]=true;
	exist[getind(x,y+1,1)]=true;exist[getind(x,y+1,2)]=true;
	DSU::update(getind(x+1,y,1),getind(x,y+1,2));
	DSU::update(getind(x+1,y,2),getind(x,y+1,1));
	d[getind(x+1,y,1)]--;d[getind(x,y+1,1)]--;
	d[getind(x+1,y,2)]++;d[getind(x,y+1,2)]++;
}

inline void doit3(int x,int y)
{
	exist[getind(x,y,1)]=true;exist[getind(x,y,2)]=true;
	exist[getind(x+1,y+1,1)]=true;exist[getind(x+1,y+1,2)]=true;
	DSU::update(getind(x,y,1),getind(x+1,y+1,2));
	DSU::update(getind(x,y,2),getind(x+1,y+1,1));
	d[getind(x,y,1)]++;d[getind(x+1,y+1,1)]++;
	d[getind(x,y,2)]--;d[getind(x+1,y+1,2)]--;
}

inline void doit4(int x,int y)
{
	exist[getind(x,y,1)]=true;exist[getind(x,y,2)]=true;
	exist[getind(x+1,y+1,1)]=true;exist[getind(x+1,y+1,2)]=true;
	DSU::update(getind(x,y,1),getind(x+1,y+1,2));
	DSU::update(getind(x,y,2),getind(x+1,y+1,1));
	d[getind(x,y,1)]--;d[getind(x+1,y+1,1)]--;
	d[getind(x,y,2)]++;d[getind(x+1,y+1,2)]++;
}

inline void getxy(int ind)
{
	if (ind>(n+1)*(m+1)) ind-=(n+1)*(m+1);
	int r=ind/(m+1);if (ind%(m+1)!=0) r++;
}

int main ()
{
	int i,j,x,y;n=getint();m=getint();
	for (i=1;i<=n;i++) scanf("%s",s1[i]+1);
	for (i=1;i<=n;i++) scanf("%s",s2[i]+1);
	DSU::init();
	for (i=1;i<=n;i++)
		for (j=1;j<=m;j++)
		{
			if (s1[i][j]=='/' || s1[i][j]=='X') doit1(i,j);
			if (s1[i][j]==92 || s1[i][j]=='X') doit3(i,j);
			if (s2[i][j]=='/' || s2[i][j]=='X') doit2(i,j);
			if (s2[i][j]==92 || s2[i][j]=='X') doit4(i,j);
		}
	for (i=1;i<=(n+1)*(m+1)*2;i++)
		if (exist[i]) getxy(i);
	for (i=1;i<=(n+1)*(m+1)*2;i++)
		if (exist[i]) cnt[DSU::find_anc(i)]+=myabs(d[i]);
	int ans=0;
	for (i=1;i<=(n+1)*(m+1)*2;i++)
		if (exist[i] && i==DSU::find_anc(i))
			if (cnt[i]==0) ans++; else ans+=cnt[i]/2;
	printf("%d\n",ans/2);
	return 0;	
}
