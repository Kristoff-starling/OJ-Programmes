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
inline int add(int x) {if (x>=MOD) x-=MOD;return x;}
inline int sub(int x) {if (x<0) x+=MOD;return x;}
inline void add(int &x,int y) {x=add(x+y);}
inline void sub(int &x,int y) {x=sub(x-y);}

const int MAXN=1e5;

int n;
int a[MAXN+48],id[MAXN+48];
int pos[21][MAXN+48];bool isleft[MAXN+48];LL dp[MAXN+48];
int q[MAXN+48];

inline void mergesort(int l,int r,int d)
{
	if (l==r) {pos[d][l]=id[l];return;}
	int mid=(l+r)>>1;
	mergesort(l,mid,d+1);mergesort(mid+1,r,d+1);
	for (register int k1=l,k2=mid+1,pt=l;k1<=mid || k2<=r;pt++)
	{
		if (k1>mid) {pos[d][pt]=pos[d+1][k2++];continue;}
		if (k2>r) {pos[d][pt]=pos[d+1][k1++];continue;}
		if (pos[d+1][k1]<pos[d+1][k2]) pos[d][pt]=pos[d+1][k1++]; else pos[d][pt]=pos[d+1][k2++];
	}
}

inline double calc(int id1,int id2)
{
	LL x1=id1,x2=id2,y1=-dp[id1]+1ll*id1*(id1+1)/2,y2=-dp[id2]+1ll*id2*(id2+1)/2;
	return double(y2-y1)/double(x2-x1);
}

inline void solve(int l,int r,int d)
{
	if (l==r) {dp[pos[d][l]]+=a[pos[d][l]];return;}
	int mid=(l+r)>>1,head=1,tail=0;
	solve(l,mid,d+1);
	for (register int i=l;i<=mid;i++) isleft[pos[d+1][i]]=true;
	for (register int i=l;i<=r;i++)
	{
		int cur=pos[d][i];
		if (isleft[cur])
		{
			while (head<tail && calc(q[tail-1],q[tail])>=calc(q[tail],cur)) tail--;
			q[++tail]=cur;
		}
		else
		{
			while (head<tail && calc(q[head],q[head+1])<cur) head++;
			if (head<=tail) check_max(dp[cur],dp[q[head]]-1ll*(cur-q[head]-1)*(cur-q[head])/2);
		}
	}
	for (register int i=l;i<=mid;i++) isleft[pos[d+1][i]]=false;
	solve(mid+1,r,d+1);
}

int main ()
{
#ifdef LOCAL
	double TIME=clock();
	freopen ("a.in","r",stdin);
	freopen ("a.out","w",stdout);
	cerr<<"Running..."<<endl;
#endif
	io.Get(n);
	for (register int i=1;i<=n;i++) io.Get(a[i]),id[i]=i;
	sort(id+1,id+n+1,[&](const int &x,const int &y) {if (a[x]!=a[y]) return a[x]<a[y];return x<y;});
	for (register int i=1;i<=n;i++) dp[i]=-1ll*i*(i-1)/2;
	mergesort(1,n,1);solve(1,n,1);
	LL ans=-1ll*n*(n+1)/2;
	for (register int i=1;i<=n;i++) check_max(ans,dp[i]-1ll*(n-i+1)*(n-i)/2);
	io.Print(ans,'\n');
	io.flush();
#ifdef LOCAL
	cerr<<"Exec Time: "<<(clock()-TIME)/CLOCKS_PER_SEC<<endl;
#endif
	return 0;
}