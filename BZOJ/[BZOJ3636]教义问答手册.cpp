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
inline int add(int x,int MO) {if (x>=MO) x-=MO;return x;}
inline int sub(int x) {if (x<0) x+=MOD;return x;}
inline int sub(int x,int MO) {if (x<0) x+=MO;return x;}
inline void Add(int &x,int y) {x=add(x+y);}
inline void Add(int &x,int y,int MO) {x=add(x+y,MO);}
inline void Sub(int &x,int y) {x=sub(x-y);}
inline void Sub(int &x,int y,int MO) {x=sub(x-y,MO);}
template<typename T> inline int quick_pow(int x,T y) {int res=1;while (y) {if (y&1) res=1ll*res*x%MOD;x=1ll*x*x%MOD;y>>=1;}return res;}
template<typename T> inline int quick_pow(int x,T y,int MO) {int res=1;while (y) {if (y&1) res=1ll*res*x%MO;x=1ll*x*x%MO;y>>=1;}return res;}

const int MAXN=1e5;

int n,L,Q;
int a[MAXN+48],sum[MAXN+48];
int ans[MAXN+48];

inline int calc(int left,int right) {return sum[right]-sum[left-1];}

struct Query
{
	int l,r,ind;
	inline void input() {io.Get(l);io.Get(r);}
}q[MAXN+48],tmp1[MAXN+48],tmp2[MAXN+48],tmp3[MAXN+48];
int tot1,tot2,tot3;

int dp1[51][MAXN+48],dp2[51][MAXN+48];

inline void solve(int l,int r,int ql,int qr)
{
	if (l>r) return;
	if (l==r)
	{
		for (register int i=ql;i<=qr;i++)
			ans[q[i].ind]=((a[l]>=0 && L<=1)?a[l]:0);
		return;
	}
	int mid=(l+r)>>1;tot1=tot2=tot3=0;
	for (register int i=ql;i<=qr;i++)
	{
		if (q[i].r<=mid) {tmp1[++tot1]=q[i];continue;}
		if (q[i].l>=mid+1) {tmp2[++tot2]=q[i];continue;}
		tmp3[++tot3]=q[i];
	}
	int pt=ql,ll=ql+tot1-1,rr=qr-tot2+1;
	for (register int i=1;i<=tot1;i++) q[pt++]=tmp1[i];
	for (register int i=1;i<=tot3;i++) q[pt++]=tmp3[i];
	for (register int i=1;i<=tot2;i++) q[pt++]=tmp2[i];
	for (register int gap=0;gap<=L-1;gap++)
	{
		dp1[gap][mid-gap+1]=0;
		for (register int i=mid-gap;i>=l;i--)
		{
			dp1[gap][i]=dp1[gap][i+1];
			if (mid-gap-i+1>=L) check_max(dp1[gap][i],dp1[gap][i+L]+calc(i,i+L-1));
		}
	}
	for (register int gap=0;gap<=L-1;gap++)
	{
		dp2[gap][mid+gap]=0;
		for (register int i=mid+1+gap;i<=r;i++)
		{
			dp2[gap][i]=dp2[gap][i-1];
			if (i-(mid+1+gap)+1>=L) check_max(dp2[gap][i],dp2[gap][i-L]+calc(i-L+1,i));
		}
	}
	for (register int i=1;i<=tot3;i++)
	{
		ans[tmp3[i].ind]=dp1[0][tmp3[i].l]+dp2[0][tmp3[i].r];
		for (register int j=mid;j>=mid-(L-1)+1;j--)
			if (j>=tmp3[i].l && j+L-1<=tmp3[i].r)
				check_max(ans[tmp3[i].ind],calc(j,j+L-1)+dp1[mid-j+1][tmp3[i].l]+dp2[j+L-1-(mid+1)+1][tmp3[i].r]);
	}
	for (register int gap=0;gap<=L-1;gap++)
		for (register int i=mid-gap+1;i>=l;i--)
			dp1[gap][i]=0;
	for (register int gap=0;gap<=L-1;gap++)
		for (register int i=mid+gap;i<=r;i++)
			dp2[gap][i]=0;
	solve(l,mid,ql,ll);solve(mid+1,r,rr,qr);
}

int main ()
{
#ifdef LOCAL
	double TIME=clock();
	freopen ("a.in","r",stdin);
	freopen ("a.out","w",stdout);
	cerr<<"Running..."<<endl;
#endif
	io.Get(n);io.Get(L);
	for (register int i=1;i<=n;i++) io.Get(a[i]),sum[i]=sum[i-1]+a[i];
	io.Get(Q);
	for (register int i=1;i<=Q;i++) q[i].input(),q[i].ind=i;
	solve(1,n,1,Q);
	for (register int i=1;i<=Q;i++) io.Print(ans[i],'\n');
	io.flush();
#ifdef LOCAL
	cerr<<"Exec Time: "<<(clock()-TIME)/CLOCKS_PER_SEC<<endl;
#endif
	return 0;
}