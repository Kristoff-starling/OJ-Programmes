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

int L,q;
int A[48];

int a[48][48],sum[48][48];

inline int calc(int x,int y)
{
	int pos=(1ll*(x+y+1)*(x+y)/2+x)%L;
	return A[pos];
}

inline int query(int x1,int y1,int x2,int y2)
{
	return sum[x2][y2]-(x1?sum[x1-1][y2]:0)-(y1?sum[x2][y1-1]:0)+((x1 && y1)?sum[x1-1][y1-1]:0);
}

int main ()
{
//	freopen ("e.in","r",stdin);
//	freopen ("e.out","w",stdout);
	int i,j,ca,x1,y1,x2,y2;ca=getint();
	while (ca--)
	{
		L=getint();for (i=0;i<=L-1;i++) A[i]=getint();
		for (i=0;i<=L*4;i++)
			for (j=0;j<=L*4;j++)
				a[i][j]=calc(i,j);
		for (i=0;i<=L*4;i++)
		{
			sum[i][0]=0;
			for (j=0;j<=L*4;j++)
				sum[i][j]=sum[i][j-1]+a[i][j];
		}
		for (i=1;i<=L*4;i++)
			for (j=0;j<=L*4;j++)
				sum[i][j]+=sum[i-1][j];
		q=getint();
		while (q--)
		{
			x1=getint();y1=getint();x2=getint();y2=getint();
			int xx=x1%(L*2),yy=y1%(L*2),xl=(x2-x1+1)%(L*2),yl=(y2-y1+1)%(L*2);
			
			int xnum=(x2-x1+1)/(L*2),ynum=(y2-y1+1)/(L*2);
			LL ans=1ll*query(xx,yy,xx+L*2-1,yy+L*2-1)*xnum*ynum;
//			if (x1==24685260) cerr<<ans<<' '<<xx<<' '<<yy<<' '<<L<<' '<<xnum<<' '<<ynum<<' '<<query(xx,yy,xx+L*2-1,yy+L*2-1)<<endl;
			if (xl) ans+=1ll*query(xx,yy,xx+xl-1,yy+L*2-1)*ynum;
			if (yl) ans+=1ll*query(xx,yy,xx+L*2-1,yy+yl-1)*xnum;
			if (xl && yl) ans+=query(xx,yy,xx+xl-1,yy+yl-1);
//			if (ans<0) cerr<<x1<<' '<<y1<<' '<<x2<<' '<<y2<<endl;
			printf("%lld\n",ans);
		}
	}
	return 0;
}
