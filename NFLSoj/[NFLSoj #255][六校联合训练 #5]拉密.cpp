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
#define LOWBIT(x) (x & (-x))
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
template<typename T> inline int quick_pow(int x,T y) {int res=1;while (y) {if (y&1) res=1ll*res*x%MOD;x=1ll*x*x%MOD;y>>=1;}return res;}
template<typename T> inline int quick_pow(int x,T y,int MO) {int res=1;while (y) {if (y&1) res=1ll*res*x%MO;x=1ll*x*x%MO;y>>=1;}return res;}

const int MAXN=1100000;

int n,r;

struct Card
{
	int type,num,ind;
	inline void input()
	{
		string tmp;cin>>tmp;
		type=tmp[0];num=tmp[1]-'0';
		if (int(tmp.size())==3) num=num*10+(tmp[2]-'0');
	}
	inline bool operator < (const Card &other) const {return num<other.num;}
}card[48];int pos[48];

int inv[48],ifac[48],fac[48],cnt[MAXN+48],val[MAXN+48],table[MAXN+48];
inline void init()
{
	for (register int i=1;i<=n;i++) table[1<<(i-1)]=i;
	for (register int i=1;i<=n;i++) inv[i]=quick_pow(i,MOD-2);
	ifac[0]=ifac[1]=1;
	for (register int i=2;i<=n;i++) ifac[i]=1ll*ifac[i-1]*inv[i]%MOD;
	fac[0]=fac[1]=1;
	for (register int i=2;i<=n;i++) fac[i]=1ll*fac[i-1]*i%MOD;
	cnt[0]=0;
	for (register int Mask=1;Mask<=(1<<n)-1;Mask++) cnt[Mask]=cnt[Mask^LOWBIT(Mask)]+1;
	val[0]=0;
	for (register int Mask=1;Mask<=(1<<n)-1;Mask++) val[Mask]=card[table[LOWBIT(Mask)]].num+val[Mask^LOWBIT(Mask)];
}

inline bool check_bomb(int Mask)
{
	if (cnt[Mask]!=3 && cnt[Mask]!=4) return false;
	int pre=0;
	for (register int cur=Mask;cur;cur^=LOWBIT(cur))
	{
		int cp=card[table[LOWBIT(cur)]].num;
		if (!pre) {pre=cp;continue;}
		if (cp!=pre) return false;
	}
	return true;
}

inline bool check_seq(int Mask)
{
	if (cnt[Mask]<3) return false;
	int pre=0,pt=0;
	for (register int cur=Mask;cur;cur^=LOWBIT(cur))
	{
		int cp=card[table[LOWBIT(cur)]].num,ct=card[table[LOWBIT(cur)]].type;
		if (!pre) {pre=cp;pt=ct;continue;}
		if (cp!=pre+1 || ct!=pt) return false;
		pre=cp;pt=ct;
	}
	return true;
}

vector<int> method[MAXN+48];
int valid[MAXN+48];

inline int solve(int Mask)
{
	if (valid[Mask]!=-1) return valid[Mask];
	for (register int i=0;i<int(method[Mask].size());i++)
		if (solve(Mask^method[Mask][i])==1) {valid[Mask]=1;return 1;}
	valid[Mask]=0;return 0;
}

inline void init_valid()
{
	for (register int Mask=1;Mask<=(1<<n)-1;Mask++)
		if (check_bomb(Mask) || check_seq(Mask))
		{
			int rev=((1<<n)-1)^Mask;
			for (register int sub=rev;;sub=(sub-1)&rev)
			{
				method[Mask|sub].pb(Mask);
				if (!sub) break;
			}
		}
	for (register int Mask=0;Mask<=(1<<n)-1;Mask++) valid[Mask]=-1;
	valid[0]=1;
	for (register int Mask=1;Mask<=(1<<n)-1;Mask++) valid[Mask]=solve(Mask);
}

int dp[MAXN+48],sMask,k,Rev;
inline int Solve(int Mask)
{
	if (dp[Mask]!=-1) return dp[Mask];
	if (valid[sMask|Mask]) {dp[Mask]=1ll*fac[n-k-cnt[Mask]]*val[Rev^Mask]%MOD;return dp[Mask];}
	int vv=Rev^Mask;dp[Mask]=0;
	for (register int i=1;i<=n;i++)
		if (vv&(1<<(i-1))) Add(dp[Mask],Solve(Mask|(1<<(i-1))));
	return dp[Mask];
}

int main ()
{
#ifdef LOCAL
	double TIME=clock();
	freopen ("a.in","r",stdin);
	freopen ("a.out","w",stdout);
	cerr<<"Running..."<<endl;
#endif
	cin>>n>>r;
	for (register int i=1;i<=n;i++) card[i].input(),card[i].ind=i;
	sort(card+1,card+n+1);init();
	for (register int i=1;i<=n;i++) pos[card[i].ind]=i;
	init_valid();
	while (r--)
	{
		io.Get(k);sMask=0;
		for (register int i=1;i<=k;i++)
		{
			int x;io.Get(x);
			sMask|=(1<<(pos[x]-1));
		}
		int rev=((1<<n)-1)^sMask;Rev=rev;
		for (register int sub=rev;;sub=(sub-1)&rev)
		{
			dp[sub]=-1;
			if (!sub) break;
		}
		dp[rev]=0;
		for (register int sub=rev;;sub=(sub-1)&rev)
		{
			dp[sub]=Solve(sub);
			if (!sub) break;
		}
		int ans=dp[0];ans=1ll*ans*ifac[n-k]%MOD;
		io.Print(ans,'\n');
	}
	io.flush();
#ifdef LOCAL
	cerr<<"Exec Time: "<<(clock()-TIME)/CLOCKS_PER_SEC<<endl;
#endif
	return 0;
}