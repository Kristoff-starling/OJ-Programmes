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

int n,L[248],R[248],val[448],tot;
int num[448][448],f[448][248],g[448][248],dp[448][448];

inline int calc(int i,int j,int x,int y)
{
	return min(max(x+y,f[i][x]+g[j][y]),min(x+y,f[i][x]+g[j][y])+num[i][j]);
}

int main ()
{
#ifndef ONLINE_JUDGE
	double TIME=clock();
	freopen ("a.in","r",stdin);
	freopen ("a.out","w",stdout);
	cerr<<"Running..."<<endl;
#endif
	Get(n);int s,t;
	rep(i,1,n) Get(s,t),L[i]=s,R[i]=s+t,val[++tot]=L[i],val[++tot]=R[i];
	sort(val+1,val+tot+1);tot=unique(val+1,val+tot+1)-(val+1);
	rep(i,1,n) L[i]=lower_bound(val+1,val+tot+1,L[i])-val,R[i]=lower_bound(val+1,val+tot+1,R[i])-val;
	rep(i,1,n) rep(j,1,L[i]) rep(k,R[i],tot) num[j][k]++;
	rep(i,0,tot+1) rep(j,0,n) f[i][j]=g[i][j]=-INF;
	f[0][0]=0;
	rep(i,1,tot) rep(j,0,n)
	{
		check_max(f[i][j],f[i-1][j]);
		rep(k,0,i)
		{
			if (j>=num[k][i]) check_max(f[i][j],f[k][j-num[k][i]]);
			check_max(f[i][j],f[k][j]+num[k][i]);
		}
	}
	g[tot+1][0]=0;
	REP(i,tot,1) rep(j,0,n)
	{
		check_max(g[i][j],g[i+1][j]);
		rep(k,i,tot+1)
		{
			if (j>=num[i][k]) check_max(g[i][j],g[k][j-num[i][k]]);
			check_max(g[i][j],g[k][j]+num[i][k]);
		}
	}
	rep(i,1,tot) rep(j,1,tot) dp[i][j]=-INF;
	rep(i,1,tot-1) rep(j,i+1,tot)
	{
		int y=n;while (g[j][y]<0) y--;
		rep(x,0,n)
		{
			if (f[i][x]<0) break;
			check_max(dp[i][j],calc(i,j,x,y));
			while (y && calc(i,j,x,y-1)>=dp[i][j]) y--,dp[i][j]=calc(i,j,x,y);
		}
	}
	int res=0;
	rep(i,0,n) check_max(res,min(i,f[tot][i]));
	printf("%d\n",res);
	rep(i,1,n)
	{
		res=0;
		rep(l,1,L[i]) rep(r,R[i],tot) check_max(res,dp[l][r]);
		printf("%d\n",res);
	}
	io.flush();
#ifndef ONLINE_JUDGE
	cerr<<"Exec Time: "<<(clock()-TIME)/CLOCKS_PER_SEC<<endl;
#endif
	return 0;
}
