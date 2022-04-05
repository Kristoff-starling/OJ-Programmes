#include <cstdio>
#include <iostream>
#include <cstring>
#include <string>
#include <algorithm>
#include <ctime>
#include <set>
#include <queue>
#include <deque>
#include <cmath>
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
inline int add(int x,int MO) {if (x>=MO) x-=MO;return x;}
inline int sub(int x) {if (x<0) x+=MOD;return x;}
inline int sub(int x,int MO) {if (x<0) x+=MO;return x;}
inline void Add(int &x,int y) {x=add(x+y);}
inline void Add(int &x,int y,int MO) {x=add(x+y,MO);}
inline void Sub(int &x,int y) {x=sub(x-y);}
inline void Sub(int &x,int y,int MO) {x=sub(x-y,MO);}
inline int quick_pow(int x,int y) {int res=1;while (y) {if (y&1) res=1ll*res*x%MOD;x=1ll*x*x%MOD;y>>=1;}return res;}
inline int quick_pow(int x,int y,int MO) {int res=1;while (y) {if (y&1) res=1ll*res*x%MO;x=1ll*x*x%MO;y>>=1;}return res;}

const int MAXN=1e5;

int n;LL m;
int a[MAXN+48];LL dp[MAXN+48];

int ind[MAXN+48],sufval[MAXN+48];LL val[MAXN+48];
int head,tail;

LL needval[MAXN+48];
priority_queue<pair<LL,int> > q;

int main ()
{
#ifdef LOCAL
	double TIME=clock();
	freopen ("a.in","r",stdin);
	freopen ("a.out","w",stdout);
	cerr<<"Running..."<<endl;
#endif
	cin>>n>>m;
	for (register int i=1;i<=n;i++) scanf("%d",&a[i]);
	for (register int i=1;i<=n;i++) if (a[i]>m) {printf("-1\n");return 0;}
	dp[0]=0;
	head=tail=1;ind[1]=0;sufval[1]=0;val[1]=dp[0];LL presum=0;int pt=1;
	memset(needval,-1,sizeof(needval));
	needval[0]=0;q.push(mp(0,0));
	for (register int i=1;i<=n;i++)
	{
		presum+=a[i];
		while (presum>m) presum-=a[pt++];
		//range: (pt-1)~(i-1)
		while (ind[head]<pt-1)
		{
			if (head<tail && ind[head+1]<=pt-1)
			{
				needval[ind[head]]=-1;
				head++;continue;
			}
			needval[ind[head]]=-1;
			ind[head]=pt-1;val[head]=dp[pt-1];
			needval[ind[head]]=val[head]+sufval[head];
			q.push(mp(-(val[head]+sufval[head]),ind[head]));
			break;
		}
		while(sufval[tail]<a[i])
		{
			if (head<tail && sufval[tail-1]<a[i])
			{
				needval[ind[tail]]=-1;
				tail--;continue;
			}
			sufval[tail]=a[i];
			needval[ind[tail]]=val[tail]+sufval[tail];
			q.push(mp(-(val[tail]+sufval[tail]),ind[tail]));
			break;
		}
		int pos;LL vv;
		while (!q.empty())
		{
			vv=-q.top().x;pos=q.top().y;
			if (needval[pos]!=vv || needval[pos]==-1) {q.pop();continue;}
			dp[i]=vv;
			++tail;ind[tail]=i;sufval[tail]=0;val[tail]=dp[i];
			needval[ind[tail]]=dp[i];q.push(mp(-dp[i],ind[tail]));
			break;
		}
	}
	cout<<dp[n]<<endl;
	io.flush();
#ifdef LOCAL
	cerr<<"Exec Time: "<<(clock()-TIME)/CLOCKS_PER_SEC<<endl;
#endif
	return 0;
}
