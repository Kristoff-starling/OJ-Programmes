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
#define Rep(i,l,r) for (register int i=int(l);i<int(r);i++)
#define REP(i,r,l) for (register int i=int(r);i>=int(l);i--)

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

const int MAXN=1e5;

char s[MAXN+48];int pre[MAXN+48][27];
int g[MAXN+48][27];int pos[48];

inline bool cmp(int x,int y) {return x>y;}

class TreasureOfWinedag
{
	inline string gen(int N,int M,int c0,vector<int> c1,vector<int> c2,vector<int> c3,vector<int> c4,string s)
	{
		string str=s;
		rep(i,int(s.size()),N-1)
		{
			int t=(1ll*i*c0)%M;
			char newChar='z';
			rep(j,0,24)
				if (t>=c3[j] && t<=c4[j] && (t%c1[j]==c2[j]))
				{
					newChar='a'+j;
					break;
				}
			str+=string(1,newChar);
		}
		return str;
	}
	public:
		inline int solvePuzzle(int N,int K,int M,int c0,vector<int> c1,vector<int> c2,vector<int> c3,vector<int> c4,string S)
		{
			string str=gen(N,M,c0,c1,c2,c3,c4,S);rep(i,1,N) s[i]=str[i-1];
			rep(i,1,26) pre[0][i]=0;
			rep(i,1,N)
			{
				rep(j,1,26) pre[i][j]=pre[i-1][j];
				pre[i][s[i]-'a'+1]=i;
			}
			rep(i,0,N) rep(j,0,25) g[i][j]=K+1;
			rep(i,0,25) g[0][i]=0;
			rep(i,1,N) rep(j,0,25)
			{
				rep(m,1,26) pos[m]=pre[i][m];pos[27]=0;
				sort(pos+1,pos+28,cmp);
				int pt=27;while (pt && pos[pt]==0) pt--;pt++;
				rep(m,2,pt)
				{
					int w=m-1;
					if (j-w+1>=0) check_min(g[i][j],g[pos[m]][j-w+1]+1);
				}
			}
			rep(i,0,25) if (g[N][i]<=K) return K+i;
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
	int nn,kk,mm,c0,x;vector<int> c1,c2,c3,c4;string s;
	TreasureOfWinedag A;
	while (cin>>nn>>kk>>mm>>c0)
	{
		c1.clear();c2.clear();c3.clear();c4.clear();
		rep(i,1,25) cin>>x,c1.pb(x);
		rep(i,1,25) cin>>x,c2.pb(x);
		rep(i,1,25) cin>>x,c3.pb(x);
		rep(i,1,25) cin>>x,c4.pb(x);
		cin>>s;s="";
		cout<<A.solvePuzzle(nn,kk,mm,c0,c1,c2,c3,c4,s)<<endl;
	}
	io.flush();
#ifndef ONLINE_JUDGE
	cerr<<"Exec Time: "<<(clock()-TIME)/CLOCKS_PER_SEC<<endl;
#endif
	return 0;
}
*/
