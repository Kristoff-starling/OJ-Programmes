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

const int MOD=1e9;
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

inline LL mod(LL x) {while (x>=MOD) x-=MOD;while (x<0) x+=MOD;return x;}

inline int getplug(int Mask,int pos) {return (Mask>>((pos-1)<<1))&3;}
inline int setplug(int Mask,int pos,int plug) {Mask|=(3<<((pos-1)<<1));Mask^=(plug<<((pos-1)<<1));Mask^=(3<<((pos-1)<<1));return Mask;}
inline int update(int Mask,int from,int to)
{
	for (register int i=1;i<=n+1;i++)
		if (getplug(Mask,i)==from) Mask=setplug(Mask,i,to);
	return Mask;
}
inline int modify(int Mask)
{
	int List[10];int ctot=0,plug;
	memset(List,0,sizeof(List));
	for (register int i=1;i<=n+1;i++)
	{
		plug=getplug(Mask,i);
		if (!plug) continue;
		if (List[plug]) {Mask=setplug(Mask,i,List[plug]);continue;}
		List[plug]=++ctot;Mask=setplug(Mask,i,ctot);
	}
	return Mask;
}

int valid[1048],vtot=0;
int table[10048];

inline void init_valid()
{
	int i,Mask;int cnt[10],sta[10];
	for (Mask=0;Mask<=(1<<(n<<1))-1;Mask++)
	{
		for (i=1;i<=n;i++) sta[i]=getplug(Mask,i);
		memset(cnt,0,sizeof(cnt));bool f=true;
		for (i=1;i<=n;i++)
		{
			if (!sta[i]) continue;
			if (sta[i]==1)
			{
				if (cnt[1]>=2 || cnt[2]%2==1) {f=false;break;}
				cnt[1]++;
			}
			if (sta[i]==2)
			{
				if (cnt[2]>=2 || cnt[1]==0) {f=false;break;}
				cnt[2]++;
			}
			if (sta[i]==3) {f=false;break;}
		}
		if (cnt[1]!=0 && cnt[1]!=2) f=false;
		if (cnt[2]!=0 && cnt[2]!=2) f=false;
		if (f) valid[++vtot]=Mask;
	}
}

struct Matrix
{
	LL b[148][148];
	inline void clear() {memset(b,0,sizeof(b));}
	inline void init_I() {clear();for (register int i=1;i<=vtot;i++) b[i][i]=1;}
	inline Matrix operator + (Matrix ma)
	{
		Matrix res;res.clear();
		for (register int i=1;i<=vtot;i++)
			for (register int j=1;j<=vtot;j++)
				res.b[i][j]=mod(res.b[i][j]+b[i][j]+ma.b[i][j]);
		return res;
	}
	inline Matrix operator * (Matrix ma)
	{
		Matrix res;res.clear();
		for (register int i=1;i<=vtot;i++)
			for (register int j=1;j<=vtot;j++)
				for (register int k=1;k<=vtot;k++)
					res.b[i][j]=mod(res.b[i][j]+(b[i][k]*ma.b[k][j])%MOD);
		return res;
	}
}trans,st;

inline Matrix quick_pow(Matrix ma,int y)
{
	Matrix res;res.init_I();
	while (y)
	{
		if (y&1) res=res*ma,y--;
		ma=ma*ma;y>>=1;
	}
	return res;
}

int dp[10][10048];
inline void init_matrix()
{
	trans.clear();
	int i,j,Mask,toMask,p1,p2;
	for (i=1;i<=vtot;i++)
	{
		memset(dp,0,sizeof(dp));
		dp[0][valid[i]<<2]=1;
		for (j=1;j<=n;j++)
			for (Mask=0;Mask<=(1<<(n*2+2));Mask++)
				if (dp[j-1][Mask])
				{
					p1=getplug(Mask,j);p2=getplug(Mask,j+1);
					if (p1 && p1==p2) continue;
					if (!p1 && !p2)
					{
						if (j==n) continue;
						toMask=Mask;toMask=setplug(toMask,j,3);toMask=setplug(toMask,j+1,3);
						toMask=modify(toMask);
						dp[j][toMask]=mod(dp[j][toMask]+dp[j-1][Mask]);
						continue;
					}
					if (!p1 || !p2)
					{
						int cc=max(p1,p2);
						toMask=Mask;toMask=setplug(toMask,j,cc);toMask=setplug(toMask,j+1,0);dp[j][toMask]=mod(dp[j][toMask]+dp[j-1][Mask]);
						if (j!=n) {toMask=Mask;toMask=setplug(toMask,j+1,cc);toMask=setplug(toMask,j,0);dp[j][toMask]=mod(dp[j][toMask]+dp[j-1][Mask]);}
						continue;
					}
					toMask=Mask;toMask=update(toMask,max(p1,p2),min(p1,p2));toMask=modify(toMask);
					toMask=setplug(toMask,j,0);toMask=setplug(toMask,j+1,0);
					dp[j][toMask]=mod(dp[j][toMask]+dp[j-1][Mask]);
				}
		for (Mask=0;Mask<=(1<<(n*2+2));Mask++)
			if (dp[n][Mask] && Mask)
				trans.b[i][table[Mask]]=dp[n][Mask];
	}
}

inline void lastline()
{
	int i,j,p1,p2,Mask,toMask;
	memset(dp,0,sizeof(dp));
	for (i=1;i<=vtot;i++) dp[0][valid[i]<<2]=st.b[1][i];
	for (j=1;j<=n;j++)
		for (Mask=0;Mask<=(1<<(n*2+2));Mask++)
			if (dp[j-1][Mask])
			{
				p1=getplug(Mask,j);p2=getplug(Mask,j+1);
				if (p1 && p1==p2)
				{
					if (j!=n) continue;
					toMask=Mask;toMask=setplug(toMask,j,0);toMask=setplug(toMask,j+1,0);
					dp[j][toMask]=mod(dp[j][toMask]+dp[j-1][Mask]);
					continue;
				}
				if (!p1 && !p2)
				{
					if (j==n) continue;
					toMask=Mask;toMask=setplug(toMask,j,3);toMask=setplug(toMask,j+1,3);
					toMask=modify(toMask);
					dp[j][toMask]=mod(dp[j][toMask]+dp[j-1][Mask]);
					continue;
				}
				if (!p1 || !p2)
				{
					int cc=max(p1,p2);
					toMask=Mask;toMask=setplug(toMask,j,cc);toMask=setplug(toMask,j+1,0);dp[j][toMask]=mod(dp[j][toMask]+dp[j-1][Mask]);
					if (j!=n) {toMask=Mask;toMask=setplug(toMask,j+1,cc);toMask=setplug(toMask,j,0);dp[j][toMask]=mod(dp[j][toMask]+dp[j-1][Mask]);}
					continue;
				}
				toMask=Mask;toMask=update(toMask,max(p1,p2),min(p1,p2));toMask=modify(toMask);
				toMask=setplug(toMask,j,0);toMask=setplug(toMask,j+1,0);
				dp[j][toMask]=mod(dp[j][toMask]+dp[j-1][Mask]);
			}
}

int main ()
{
	int i;
	n=getint();m=getint();
	init_valid();
	for (i=1;i<=vtot;i++) table[valid[i]]=i;
	init_matrix();
	st.clear();st.b[1][1]=1;st=st*quick_pow(trans,m-1);
	lastline();
	printf("%d\n",(dp[n][0]*2)%MOD);
	return 0;
}
