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

const int INF=1e9;
const LL LINF=2e16;
const int magic=100;
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

int n,m,q;

struct Matrix
{
	int b[58][58];
	inline void clear()
	{
		for (register int i=1;i<=n;i++)
			for (register int j=1;j<=n;j++)
				b[i][j]=INF;
	}
	inline Matrix operator * (Matrix ma)
	{
		Matrix res;res.clear();
		for (register int i=1;i<=n;i++)
			for (register int j=1;j<=n;j++)
				for (register int k=1;k<=n;k++)
					res.b[i][j]=min(res.b[i][j],b[i][k]+ma.b[k][j]);
		return res;
	}
	inline Matrix operator = (Matrix ma)
	{
		for (register int i=1;i<=n;i++)
			for (register int j=1;j<=n;j++)
				b[i][j]=ma.b[i][j];
		return (*this);
	}
	inline void print()
	{
		for (register int i=1;i<=n;i++)
		{
			for (register int j=1;j<=n;j++)
				printf("%d ",b[i][j]);
			puts("");
		}
	}
}trans,Trans,A[148],B[148];

int dist[58][58];
inline void floyd()
{
	for (register int k=1;k<=n;k++)
		for (register int i=1;i<=n;i++)
			for (register int j=1;j<=n;j++)
				if (i!=j && i!=k && j!=k) dist[i][j]=min(dist[i][j],dist[i][k]+dist[k][j]);
}

int main ()
{
	int i,j,k,ca,s,t,x,y,c;ca=getint();
	while (ca--)
	{
		n=getint();m=getint();trans.clear();
		for (i=1;i<=m;i++)
		{
			x=getint();y=getint();c=getint();
			trans.b[x][y]=min(trans.b[x][y],c);
		}
		Trans=trans;B[1]=Trans;
		for (i=1;i<=magic-1;i++) Trans=Trans*trans,B[i+1]=Trans;
		A[1]=Trans;
		for (i=2;i<=magic;i++) A[i]=A[i-1]*Trans;
		for (i=1;i<=n;i++)
			for (j=1;j<=n;j++)
				dist[i][j]=trans.b[i][j];
		floyd();
		for (register int num=1;num<=magic;num++)
			for (k=1;k<=n;k++)
				for (i=1;i<=n;i++)
					for (j=1;j<=n;j++)
						B[num].b[i][j]=min(B[num].b[i][j],B[num].b[i][k]+dist[k][j]); 
		q=getint();
		while (q--)
		{
			s=getint();t=getint();k=getint();
			int p1=k/magic,p2=k%magic;
			if (!p2) p1--,p2+=magic;
			int ans=INF;
			if (!p1)
			{
				if (B[p2].b[s][t]<INF) printf("%d\n",B[p2].b[s][t]); else puts("-1");
				continue;
			}
			for (i=1;i<=n;i++) ans=min(ans,A[p1].b[s][i]+B[p2].b[i][t]);
			if (ans<INF) printf("%d\n",ans); else puts("-1");
		}
	}
	return 0;
}
