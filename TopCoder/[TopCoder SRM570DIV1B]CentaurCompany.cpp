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
// #define LOCAL true

const int INF=2e9;
const LL LINF=2e16;
const int magic=348;
const int MOD=998244353;
const double eps=1e-10;
const double pi=acos(-1);

struct fastio
{
	static const int S=1e7;
	char rbuf[S+48],wbuf[S+48];int rpos,wpos,len;
	fastio() {rpos=len=wpos=0;}
	inline char Getchar()
	{
		if (rpos==len) rpos=0,len=fread(rbuf,1,S,stdin);
		if (!len) return EOF;
		return rbuf[rpos++];
	}
	template <class T> inline void Get(T &x)
	{
		char ch;bool f;T res;
		while (!isdigit(ch=Getchar()) && ch!='-') {}
		if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
		while (isdigit(ch=Getchar())) res=res*10+ch-'0';
		x=(f?res:-res);
	}
	inline void getstring(char *s)
	{
		char ch;
		while ((ch=Getchar())<=32) {}
		for (;ch>32;ch=Getchar()) *s++=ch;
		*s='\0';
	}
	inline void flush() {fwrite(wbuf,1,wpos,stdout);fflush(stdout);wpos=0;}
	inline void Writechar(char ch)
	{
		if (wpos==S) flush();
		wbuf[wpos++]=ch;
	}
	template <class T> inline void Print(T x,char ch)
	{
		char s[20];int pt=0;
		if (x==0) s[++pt]='0';
		else
		{
			if (x<0) Writechar('-'),x=-x;
			while (x) s[++pt]='0'+x%10,x/=10;
		}
		while (pt) Writechar(s[pt--]);
		Writechar(ch);
	}
	inline void printstring(char *s)
	{
		int pt=1;
		while (s[pt]!='\0') Writechar(s[pt++]);
	}
}io;

const int MAXN=36;

int n;

int head[MAXN+48],to[MAXN+48],nxt[MAXN+48],tot=1;
inline void addedge(int s,int t)
{
	to[++tot]=t;nxt[tot]=head[s];head[s]=tot;
	to[++tot]=s;nxt[tot]=head[t];head[t]=tot;
}

LL dp[37][37][37][2],dp2[37][37][37];

inline void dfs(int cur,int father)
{
	for (register int i=head[cur];i;i=nxt[i])
	{
		register int y=to[i];
		if (y!=father) dfs(y,cur);
	}
	int cc=0;
	memset(dp2,0,sizeof(dp2));
	//root is a hole
	dp2[0][0][0]=1;
	for (register int i=head[cur];i;i=nxt[i])
	{
		register int y=to[i];
		if (y!=father)
		{
			cc++;
			for (register int j=0;j<=n;j++)
				for (register int k=0;k<=n;k++)
					if (dp2[cc-1][j][k])
						for (register int l=0;l<=n;l++)
							for (register int m=0;m<=n;m++)
								for (register int type=0;type<=1;type++)
									if (dp[y][l][m][type])
										dp2[cc][j+l][k+m]+=dp2[cc-1][j][k]*dp[y][l][m][type];
		}
	}
	for (register int j=0;j<=n;j++)
		for (register int k=0;k<=n;k++)
			dp[cur][j][k][0]=dp2[cc][j][k];
	cc=0;memset(dp2,0,sizeof(dp2));
	//root is chosen
	dp2[0][1][1]=1;
	for (register int i=head[cur];i;i=nxt[i])
	{
		register int y=to[i];
		if (y!=father)
		{
			cc++;
			for (register int j=0;j<=n;j++)
				for (register int k=0;k<=n;k++)
					if (dp2[cc-1][j][k])
						for (register int l=0;l<=n;l++)
							for (register int m=0;m<=n;m++)
							{
								dp2[cc][j+l][k+m]+=dp2[cc-1][j][k]*dp[y][l][m][0];
								dp2[cc][j+l][k+m-1]+=dp2[cc-1][j][k]*dp[y][l][m][1];
							}
		}
	}
	for (register int j=0;j<=n;j++)
		for (register int k=0;k<=n;k++)
			dp[cur][j][k][1]=dp2[cc][j][k];
}

class CentaurCompany
{
	public:
		inline double getvalue(vector<int> A,vector<int> B)
		{
			n=int(A.size());
			memset(head,0,sizeof(head));tot=0;
			for (register int i=0;i<=n-1;i++) addedge(A[i],B[i]);
			n++;dfs(1,-1);
			double ans=0;
			for (register int j=0;j<=n;j++)
				for (register int k=0;k<=n;k++)
					ans+=(dp[1][j][k][0]+dp[1][j][k][1])*max(0,(k-1)*2-j);
			for (register int i=1;i<=n-1;i++) ans/=2;
			return ans;
		}
};

#ifdef LOCAL
int main ()
{
#ifdef LOCAL
	double t=clock();
	cerr<<"Running..."<<endl;
	freopen ("a.in","r",stdin);
	freopen ("a.out","w",stdout);
#endif
	int nn,xx;vector<int> aa,bb;
	CentaurCompany A;
	while (cin>>nn)
	{
		aa.clear();bb.clear();
		for (register int i=1;i<=nn;i++) cin>>xx,aa.pb(xx);
		for (register int i=1;i<=nn;i++) cin>>xx,bb.pb(xx);
		//cout<<A.getvalue(aa,bb)<<endl;
		printf("%.15lf\n",A.getvalue(aa,bb));
	}
#ifdef LOCAL
	cerr<<"Exec Time: "<<(clock()-t)/CLOCKS_PER_SEC<<endl;
#endif
	io.flush();return 0;
}
#endif