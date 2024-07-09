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
#define ull unsigned long long
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
const int INF=1e9;
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

Pair edge[200048];
vector<int> v[200048];
ull n,e,A,B,C;

inline bool cmp_x(Pair x,Pair y) {return x.x<y.x;}
inline bool cmp_y(Pair x,Pair y) {return x.y<y.y;}

int main ()
{
	int i,j,x,y,l,r,mid,pos,pt,y;ull ans=0,cnt;
	n=getint();e=getint();A=getint();B=getint();C=getint();
	for (i=1;i<=e;i++)
	{
		x=getint();y=getint();if (x>y) swap(x,y);
		edge[i]=mp(x,y);v[x].pb(y);v[y].pb(x);
	}
	for (i=1;i<=n;i++) sort(v[i].beging(),v[i].end());
	//for C
	sort(edge+1,edge+e+1,cmp_y);
	pt=0;
	for (i=1;i<=n;i++)
	{
		while (pt<n && edge[pt+1].y<i) pt++;
		cnt=(i-1)*(i-2)/2-pt;
		for (j=0;j<int(v[i].size()) && v[i][j]<i;j++)
		{
			y=v[i][j];
			l=0;r=int(v[y].size())-1;pos=-1;
			while (l<=r)
			{
				mid=(l+r)>>1;
				if (v[y][mid]<i) pos=mid,l=mid+1; else r=mid-1;
			}
			cnt-=(i-2-(pos+1));
		}
		cnt+=(ull)j*(j-1)/2;
		ans=ans+(ull)C*i*cnt;
	}
	//for A
	sort(edge+1,edge+e+1,cmp_x);
	pt=n+1;
	for (i=n;i>=1;i--)
	{
		while (pt>1 && edge[pt-1].x>i) pt--;
		cnt=(n-i)*(n-i-1)/2-(n-pt+1);
		for (j=int(v[i].size())-1;j>=0 && v[i][j]>i;j--)
		{
			y=v[i][j];
			l=0;r=int(v[y].size())-1;pos=int(v[y].size());
			while (l<=r)
			{
				mid=(l+r)>>1;
				if (v[y][mid]>i) pos=mid,r=mid-1; else l=mid+1;
			}
			cnt-=(n-i-1-(int(v[y].size())-pos));
		}
		cnt+=(ull)
	}
}
