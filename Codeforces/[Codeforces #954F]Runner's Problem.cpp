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
const double pi=3.14159265;

inline int getint()
{
    char ch;int res;bool f;
    while (!isdigit(ch=getchar()) && ch!='-') {}
    if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
    while (isdigit(ch=getchar())) res=res*10+ch-'0';
    return f?res:-res;
}

inline LL getLL()
{
    char ch;LL res;bool f;
    while (!isdigit(ch=getchar()) && ch!='-') {}
    if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
    while (isdigit(ch=getchar())) res=res*10+ch-'0';
    return f?res:-res;
}

struct Matrix
{
	LL b[10][10];
	inline void clear()
	{
		memset(b,0ll,sizeof(b));
	}
	inline void memset_Imatrix()
	{
		clear();
		for (int i=1;i<=3;i++) b[i][i]=1;
	}
	inline void memset1() {b[1][1]=1;b[2][1]=1;b[3][1]=0;}
	inline void memset2() {b[1][2]=1;b[2][2]=1;b[3][2]=1;}
	inline void memset3() {b[1][3]=0;b[2][3]=1;b[3][3]=1;}
	inline Matrix operator + (Matrix ma)
	{
		Matrix res;res.clear();
		int i,j;
		for (i=1;i<=3;i++)
			for (j=1;j<=3;j++)
				res.b[i][j]=(res.b[i][j]+b[i][j]+ma.b[i][j])%MOD;
		return res;
	}
	inline Matrix operator * (Matrix ma)
	{
		Matrix res;res.clear();
		int i,j,k;
		for (i=1;i<=3;i++)
			for (j=1;j<=3;j++)
				for (k=1;k<=3;k++)
					res.b[i][j]=(res.b[i][j]+(b[i][k]*ma.b[k][j])%MOD)%MOD;
		return res;
	}
}Ma,sMa;

inline Matrix quick_pow(Matrix ma,LL y)
{
	Matrix res;res.memset_Imatrix();
	while (y)
	{
		if (y&1)
		{
			res=res*ma;
			y--;
		}
		ma=ma*ma;
		y>>=1;
	}
	return res;
}

int n;LL m;
int cover[10];
vector<LL> p;

struct Edge
{
	LL pos;int row;
	int delta;
	inline bool operator < (const Edge &x) const
	{
		return pos<x.pos;
	}
}a[100048];int tot=0;

inline void doit(LL cur,LL to)
{
	LL need=to-cur;
	Ma.clear();
	if (!cover[1]) Ma.memset1();
	if (!cover[2]) Ma.memset2();
	if (!cover[3]) Ma.memset3();
	Ma=quick_pow(Ma,need);
	sMa=sMa*Ma;
}

int main ()
{
	int i,row;LL l,r;
	n=getint();m=getLL();
	for (i=1;i<=n;i++)
	{
		row=getint();l=getLL();r=getLL();
		a[++tot]=Edge{l,row,1};a[++tot]=Edge{r+1,row,-1};
		p.pb(l);p.pb(r+1);
	}
	sort(a+1,a+tot+1);
	sort(p.begin(),p.end());p.resize(unique(p.begin(),p.end())-p.begin());
	sMa.b[1][1]=sMa.b[1][3]=0;sMa.b[1][2]=1;LL curpos=1;
	int pt=1;memset(cover,0,sizeof(cover));
	for (i=0;i<int(p.size());i++)
	{
		doit(curpos,p[i]-1);
		while (pt<=tot && a[pt].pos==p[i]) cover[a[pt].row]+=a[pt].delta,pt++;
		curpos=p[i]-1;
	}
	doit(curpos,m);
	cout<<sMa.b[1][2]<<endl;
	return 0;
}
