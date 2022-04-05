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
const int MOD=51123987;
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
inline int add(int x,int MO) {if (x>=MO) x-=MO;return x;}
inline int sub(int x) {if (x<0) x+=MOD;return x;}
inline int sub(int x,int MO) {if (x<0) x+=MO;return x;}
inline void Add(int &x,int y) {x=add(x+y);}
inline void Add(int &x,int y,int MO) {x=add(x+y,MO);}
inline void Sub(int &x,int y) {x=sub(x-y);}
inline void Sub(int &x,int y,int MO) {x=sub(x-y,MO);}
template<typename T> inline int quick_pow(int x,T y) {int res=1;while (y) {if (y&1) res=1ll*res*x%MOD;x=1ll*x*x%MOD;y>>=1;}return res;}
template<typename T> inline int quick_pow(int x,T y,int MO) {int res=1;while (y) {if (y&1) res=1ll*res*x%MO;x=1ll*x*x%MO;y>>=1;}return res;}

const int MAXN=2e6;

int len;
char s[MAXN+48];

char ss[MAXN*2+48];int slen;
int RL[MAXN*2+48],maxright,pos;
int mark[MAXN+48],cnt[MAXN+48],sum[MAXN+48];
int rightmark[MAXN+48];int ans=0;

inline int getsum(int l,int r)
{
	int res=sum[r];
	if (l>1) Sub(res,sum[l-1]);
	return res;
}

inline void Manacher()
{
	for (register int i=1;i<=len;i++) ss[++slen]='#',ss[++slen]=s[i];
	ss[++slen]='#';maxright=pos=0;
	for (register int i=1;i<=slen;i++)
	{
		if (i<maxright) RL[i]=min(maxright-i,RL[2*pos-i]); else RL[i]=1;
		while (i-RL[i]>=1 && i+RL[i]<=slen && ss[i+RL[i]]==ss[i-RL[i]]) RL[i]++;
		if (i+RL[i]-1>maxright) maxright=i+RL[i]-1,pos=i;
	}
	for (register int i=2;i<=slen-1;i++)
		if (i&1)
		{
			//even len;
			int L=i/2+1,R=L+RL[i]/2-1;
			Add(mark[L],1);Sub(mark[R+1],1);
			Add(rightmark[L],1);Sub(rightmark[R+1],1);
		}
		else
		{
			//odd len;
			int L=i/2,R=L+RL[i]/2-1;
			Add(mark[L],1);Sub(mark[R+1],1);
			Add(rightmark[L],1);Sub(rightmark[R+1],1);
		}
	cnt[1]=mark[1];for (register int i=2;i<=len;i++) cnt[i]=add(cnt[i-1]+mark[i]);
	sum[1]=cnt[1];for (register int i=2;i<=len;i++) sum[i]=add(sum[i-1]+cnt[i]);
	for (register int i=2;i<=len;i++) Add(sum[i],sum[i-1]);
	for (register int i=2;i<=len;i++) Add(rightmark[i],rightmark[i-1]);
	for (register int i=2;i<=slen-1;i++)
		if (i&1)
		{
			//even len;
			int L=i/2+1,R=L+RL[i]/2-1;
			Add(ans,getsum(L,R));
			int delta=R-(L-2);L-=delta;R-=delta;
			Sub(ans,getsum(L,R));
		}
		else
		{
			//odd len;
			int L=i/2,R=L+RL[i]/2-1;
			Add(ans,getsum(L,R));
			int delta=R-(L-1);L-=delta;R-=delta;
			Sub(ans,getsum(L,R));
		}
	for (register int i=1;i<=len;i++) Sub(ans,add(rightmark[i]+1ll*rightmark[i]*(rightmark[i]-1)%MOD*((MOD+1)/2)%MOD));
}

int main ()
{
#ifdef LOCAL
	double TIME=clock();
	freopen ("a.in","r",stdin);
	freopen ("a.out","w",stdout);
	cerr<<"Running..."<<endl;
#endif
	io.Get(len);io.getstring(s+1);
	Manacher();io.Print(ans,'\n');
	io.flush();
#ifdef LOCAL
	cerr<<"Exec Time: "<<(clock()-TIME)/CLOCKS_PER_SEC<<endl;
#endif
	return 0;
}