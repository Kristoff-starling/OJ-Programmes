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
#define LOWBIT(x) x & (-x)
// #define LOCAL true

const int INF=2e9;
const LL LINF=2e16;
const int magic=348;
const int MOD=1e9+7;
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

template<typename T> inline void check_max(T &x,T cmp) {x=max(x,cmp);}
template<typename T> inline void check_min(T &x,T cmp) {x=min(x,cmp);}
template<typename T> inline T myabs(T x) {return x>=0?x:-x;}
template<typename T> inline T gcd(T x,T y) {return y==0?x:gcd(y,x%y);}
inline int add(int x) {if (x>=MOD) x-=MOD;return x;}
inline int sub(int x) {if (x<0) x+=MOD;return x;}
inline void add(int &x,int y) {x=add(x+y);}
inline void sub(int &x,int y) {x=sub(x-y);}

class SeatingPlan
{
	int n,m,k;
	ull dp[2][548][21];
	int vMask[10048],vtot;
	int cnt[10048];
	inline void init_Mask()
	{
		vtot=0;
		for (register int Mask=0;Mask<=(1<<m)-1;Mask++)
		{
			if (!(Mask&(Mask<<1))) vMask[++vtot]=Mask;
			cnt[Mask]=0;
			for (register int tmp=Mask;tmp;tmp-=LOWBIT(tmp)) cnt[Mask]++;
		}
	}
	vector<Pair> factor[148];bool isprime[148];
	int cc[148];
	inline void init_factor()
	{
		for (register int i=2;i<=80;i++) factor[i].clear();
			memset(isprime,true,sizeof(isprime));
		for (register int i=2;i<=80;i++)
			if (isprime[i])
			{
				factor[i].pb(mp(i,0));
				for (register int j=i+i;j<=80;j+=i) isprime[j]=false,factor[j].pb(mp(i,0));
			}
		for (register int i=2;i<=80;i++)
			for (register int j=0;j<int(factor[i].size());j++)
				for (register int tmp=i;tmp%factor[i][j].x==0;tmp/=factor[i][j].x) factor[i][j].y++;
	}
	template <typename T> inline string INT_TO_STRING(T x)
	{
		if (!x) return "0";
		string res="";
		while (x) res=string(1,'0'+x%10)+res,x/=10;
		return res;
	}
	public:
		inline string expectedTrial(int N,int M,int K)
		{
			n=N;m=M;k=K;if (n<m) swap(n,m);
			init_Mask();init_factor();
			memset(dp,0,sizeof(dp));
			dp[0][0][0]=1;int cur=0,nxt=1;
			for (register int i=0;i<=n-1;i++)
			{
				for (register int j=1;j<=vtot;j++)
					for (register int num=0;num<=k;num++)
					{
						register int Mask=vMask[j];
						if (dp[cur][Mask][num])
						{
							for (register int jj=1;jj<=vtot;jj++)
							{
								register int toMask=vMask[jj];
								if (!(Mask&toMask))
									dp[nxt][toMask][num+cnt[toMask]]=dp[nxt][toMask][num+cnt[toMask]]+dp[cur][Mask][num];
							}
							dp[cur][Mask][num]=0;
						}
					}
				cur^=1;nxt^=1;
			}
			ull ans=0;
			for (register int Mask=0;Mask<=(1<<m)-1;Mask++) ans+=dp[cur][Mask][k];
			if (!ans) return "Impossible!";
			memset(cc,0,sizeof(cc));
			for (register int i=n*m;i>=n*m-k+1;i--)
				for (register int j=0;j<int(factor[i].size());j++)
					cc[factor[i][j].x]+=factor[i][j].y;
			for (register int i=k;i>=2;i--)
				for (register int j=0;j<int(factor[i].size());j++)
					cc[factor[i][j].x]-=factor[i][j].y;
			ull mu=1;
			for (register int i=2;i<=80;i++)
				for (register int j=1;j<=cc[i];j++)
					mu*=i;
			ull g=gcd(mu,ans);mu/=g;ans/=g;
			return INT_TO_STRING(mu)+"/"+INT_TO_STRING(ans);
		}
};

#ifdef LOCAL
int main ()
{
	double TIME=clock();
	freopen ("a.in","r",stdin);
	freopen ("a.out","w",stdout);
	cerr<<"Running..."<<endl;
	int nn,mm,kk;SeatingPlan A;
	while (cin>>nn>>mm>>kk) cout<<A.expectedTrial(nn,mm,kk)<<endl;
	io.flush();
#ifdef LOCAL
	cerr<<"Exec Time: "<<(clock()-TIME)/CLOCKS_PER_SEC<<endl;
#endif
	return 0;
}
#endif