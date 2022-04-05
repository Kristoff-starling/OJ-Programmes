// I'll always miss you like a darling.
#include <bits/stdc++.h>
using namespace std;

#define LL long long
#define LD long double
#define ull unsigned long long
#define uint unsigned int
#define x first
#define y second
#define pb push_back
#define pf push_front
#define mp make_pair
#define Pair pair<int,int>
#define pLL pair<LL,LL>
#define pii pair<double,double>
#define LOWBIT(x) ((x) & (-x))
#define rep(i,l,r) for (register int i=int(l);i<=int(r);i++)
#define REP(i,l,r) for (register int i=int(r);i>=int(l);i--)

const int INF=2e9;
const LL LINF=2e16;
const int magic=348;
const int MOD=1e9+7;
const double eps=1e-10;
const double pi=acos(-1);

template<typename T> inline void Get(T &x)
{
	bool f;char ch;T res;
	while (!isdigit(ch=getchar()) && ch!='-') {}
	if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
	while (isdigit(ch=getchar())) res=res*10+ch-'0';
	x=(f?res:(-res));
}

template<typename T1,typename ...T2> inline void Get(T1 &x,T2 &...y) {Get(x);Get(y...);}

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
    template<typename T> inline void Get(T &x)
    {
        char ch;bool f;T res;
        while (!isdigit(ch=Getchar()) && ch!='-') {}
        if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
        while (isdigit(ch=Getchar())) res=res*10+ch-'0';
        x=(f?res:(-res));
    }
    template<typename T1,typename ...T2> inline void Get(T1 &x,T2 &...y) {Get(x);Get(y...);}
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
    template<typename T> inline void Print(T x,char ch)
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
	template<typename T1,typename ...T2> inline void Print(T1 &x,T2 &...y) {Print(x,' ');Print(y...,' ');Writechar('\n');}
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
template<typename T> inline T add(T x) {if (x>=MOD) x-=MOD;return x;}
template<typename T> inline T add(T x,int MO) {if (x>=MO) x-=MO;return x;}
template<typename T> inline T sub(T x) {if (x<0) x+=MOD;return x;}
template<typename T> inline T sub(T x,int MO) {if (x<0) x+=MO;return x;}
template<typename T> inline T mul(T x,T y) {return 1ll*x*y%MOD;}
template<typename T> inline T mul(T x,T y,int MO) {return 1ll*x*y%MO;}
template<typename T> inline void Add(T &x,T y) {x=add(x+y);}
template<typename T> inline void Add(T &x,T y,int MO) {x=add(x+y,MO);}
template<typename T> inline void Sub(T &x,T y) {x=sub(x-y);}
template<typename T> inline void Sub(T &x,T y,int MO) {x=sub(x-y,MO);}
template<typename T> inline void Mul(T &x,T y) {x=mul(x,y);}
template<typename T> inline void Mul(T &x,T y,int MO) {x=mul(x,y,MO);}
template<typename T> inline int quick_pow(int x,T y) {int res=1;while (y) {if (y&1) res=1ll*res*x%MOD;x=1ll*x*x%MOD;y>>=1;}return res;}
template<typename T> inline int quick_pow(int x,T y,int MO) {int res=1;while (y) {if (y&1) res=1ll*res*x%MO;x=1ll*x*x%MO;y>>=1;}return res;}

int n;
double dist[48][48],ga[48][48];
double dp[300048][21],prob[300048];
int comp[21];

inline double getdist(double x1,double y1,double x2,double y2) {return sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));}

class RandomFlights
{
	public:
		inline double expectedDistance(vector<int> X,vector<int> Y,vector<string> flight)
		{
			n=int(X.size());
			rep(i,1,n) rep(j,1,n) dist[i][j]=getdist(X[i-1],Y[i-1],X[j-1],Y[j-1]);
			rep(i,1,n) rep(j,1,n) ga[i][j]=(flight[i-1][j-1]=='1'?dist[i][j]:INF);
			rep(i,1,n) ga[i][i]=0;
			rep(k,1,n) rep(i,1,n) rep(j,1,n) check_min(ga[i][j],ga[i][k]+ga[k][j]);
			rep(i,1,n)
			{
				comp[i]=0;
				rep(j,1,n) if (ga[i][j]<INF) comp[i]|=(1<<(j-1));
			}
			rep(Mask,0,(1<<n)-1) rep(i,1,n) dp[Mask][i]=0;
			rep(Mask,0,(1<<n)-1) prob[Mask]=0;
			prob[comp[1]]=1;
			rep(i,1,n) dp[comp[1]][i]=ga[1][i];
			rep(Mask,0,(1<<n)-1)
				if (prob[Mask])
				{
					int cnt1=__builtin_popcount(Mask),cnt2=n-cnt1;
					double nxtprob=prob[Mask]/cnt1/cnt2;
					rep(i,1,n)
						if (Mask&(1<<(i-1)))
							rep(j,1,n)
								if (!(Mask&(1<<(j-1))))
								{
									int nMask=(Mask|comp[j]);prob[nMask]+=nxtprob;
									rep(k,1,n)
										if (Mask&(1<<(k-1)))
											dp[nMask][k]+=dp[Mask][k]/cnt1/cnt2;
										else if (comp[j]&(1<<(k-1)))
											dp[nMask][k]+=(dp[Mask][i]/prob[Mask]+dist[i][j]+ga[j][k])*nxtprob;
								}
				}
			return dp[(1<<n)-1][2];
		}
};

/*--- Debug Part ---*/
/*
int main ()
{
#ifndef ONLINE_JUDGE
	double TIME=clock();
	freopen ("a.in","r",stdin);
	freopen ("a.out","w",stdout);
	cerr<<"Running..."<<endl;
#endif
	int nn;
	string s;vector<string> ss;
	vector<int> aa,bb;int x;
	RandomFlights A;
	while (cin>>nn)
	{
		aa.clear();bb.clear();ss.clear();
		rep(i,1,nn) cin>>x,aa.pb(x);
		rep(i,1,nn) cin>>x,bb.pb(x);
		rep(i,1,nn) cin>>s,ss.pb(s);
		printf("%.10lf\n",A.expectedDistance(aa,bb,ss));
	}
	io.flush();
#ifndef ONLINE_JUDGE
	cerr<<"Exec Time: "<<(clock()-TIME)/CLOCKS_PER_SEC<<endl;
#endif
	return 0;
}
*/
