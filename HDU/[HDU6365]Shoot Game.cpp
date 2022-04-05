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

const int MAXN=300;

inline double myabs(double x) {if (x>eps) return x;if (x<-eps) return -x;return 0;}
inline bool islarger(double x,double y) {return x-y>eps;}
inline bool issmaller(double x,double y) {return x-y<-eps;}
inline bool isequal(double x,double y) {return myabs(x-y)<eps;}

struct point
{
	int x,y;
	double ang;
	bool type;int from;
	point () {}
	inline void calc_ang() {ang=atan2(x,y);}
	inline point (int xx,int yy,int tt,int ff) {x=xx;y=yy;type=tt;from=ff;calc_ang();}
	inline bool operator < (const point &other) const
	{
		if (!isequal(ang,other.ang)) return issmaller(ang,other.ang);
		if (type!=other.type) return !type;
		return true;
	}
}b[MAXN*2+48];int tot;

int n;

Pair a[MAXN+48];
int val[MAXN+48];

int maxind[MAXN*2+48][MAXN*2+48];
LL dp[MAXN*2+48][MAXN*2+48];
int toleft[MAXN*2+48],toright[MAXN*2+48];

inline LL solve(int left,int right)
{
	if (left>right) return 0;
	if (dp[left][right]!=-1) return dp[left][right];
	if (maxind[left][right]==-1) {dp[left][right]=0;return 0;}
	dp[left][right]=LINF;
	int L=a[maxind[left][right]].x,R=a[maxind[left][right]].y;
	for (register int i=toleft[L];i<=toright[R];i++)
		dp[left][right]=min(dp[left][right],solve(left,i-1)+solve(i+1,right));
	dp[left][right]+=val[maxind[left][right]];
	return dp[left][right];
}

int main ()
{
//	freopen ("a.in","r",stdin);
//	freopen ("a.out","w",stdout);
	int i,j,k,ca,x,y,z;io.Get(ca);
//	cerr<<atan2(1,1)<<endl;
	while (ca--)
	{
		io.Get(n);
		for (i=1;i<=n;i++)
		{
			io.Get(z);io.Get(x);io.Get(y);io.Get(val[i]);
			b[i*2-1]=point(x,z,false,i);b[i*2]=point(y,z,true,i);
		}
		sort(b+1,b+n*2+1);
		for (i=2,toleft[1]=1;i<=n*2;i++) if (isequal(b[i-1].ang,b[i].ang)) toleft[i]=toleft[i-1]; else toleft[i]=i;
		for (i=n*2-1,toright[n*2]=n*2;i>=1;i--) if (isequal(b[i+1].ang,b[i].ang)) toright[i]=toright[i+1]; else toright[i]=i;
//		for (i=1;i<=n*2;i++) cerr<<b[i].x<<' '<<b[i].y<<endl;
//		cerr<<"-----"<<endl;
		for (i=1;i<=n*2;i++) if (!b[i].type) a[b[i].from].x=i; else a[b[i].from].y=i;
		for (i=1;i<=n*2;i++)
			for (j=i;j<=n*2;j++)
			{
				maxind[i][j]=-1;int maxn=-1;
				for (k=1;k<=n;k++)
					if (a[k].x>=i && a[k].y<=j && val[k]>maxn) maxind[i][j]=k,maxn=val[k];
			}
		for (i=1;i<=n*2;i++)
			for (j=i;j<=n*2;j++)
				dp[i][j]=-1;
		io.Print(solve(1,n*2),'\n');
	}
	io.flush();return 0;
}
