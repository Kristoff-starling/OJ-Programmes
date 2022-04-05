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
inline int quick_pow(int x,int y) {int res=1;while (y) {if (y&1) res=1ll*res*x%MOD;x=1ll*x*x%MOD;y>>=1;}return res;}
inline int quick_pow(int x,int y,int MO) {int res=1;while (y) {if (y&1) res=1ll*res*x%MO;x=1ll*x*x%MO;y>>=1;}return res;}

const int MAXN=1e5;

int n,q;
vector<int> v[MAXN*4];int tot;
int pos[MAXN+48];Pair interval[MAXN*4+48];
int L[MAXN*4+48],R[MAXN*4+48];

int anc[MAXN*4+48][21],depth[MAXN*4+48];
int seq[MAXN*10+48],stot;int sp[MAXN*4+48];
int ST[MAXN*10+48][21],ind[MAXN*10+48][21],Log[MAXN*10+48];
inline void construct(int l,int r,int father)
{
	int cur=++tot;interval[tot]=mp(l,r);sp[cur]=++stot;seq[stot]=cur;
	depth[tot]=depth[father]+1;anc[tot][0]=father;
	for (register int i=1;i<=20;i++) anc[tot][i]=anc[anc[tot][i-1]][i-1];
	if (l<r)
	{
		int mid;io.Get(mid);
		construct(l,mid,cur);seq[++stot]=cur;
		construct(mid+1,r,cur);seq[++stot]=cur;
	}
	else
	{
		pos[l]=cur;
		int u=cur;
		for (register int i=20;i>=0;i--)
			if (interval[anc[u][i]].x==l) u=anc[u][i];
		L[cur]=u;u=cur;
		for (register int i=20;i>=0;i--)
			if (interval[anc[u][i]].y==l) u=anc[u][i];
		R[cur]=u;
	}
}

inline void init_ST()
{
	Log[0]=Log[1]=0;for (register int i=2;i<=stot;i++) Log[i]=Log[i>>1]+1;
	for (register int i=1;i<=stot;i++) ST[i][0]=depth[seq[i]],ind[i][0]=seq[i];
	for (register int j=1;j<=20;j++)
		for (register int i=1;i<=stot;i++)
		{
			ST[i][j]=ST[i][j-1];ind[i][j]=ind[i][j-1];
			if (i+(1<<(j-1))<=stot && ST[i+(1<<(j-1))][j-1]<ST[i][j])
			{
				ST[i][j]=ST[i+(1<<(j-1))][j-1];
				ind[i][j]=ind[i+(1<<(j-1))][j-1];
			}
		}
}

inline int getlca(int u,int v)
{
	if (sp[u]>sp[v]) swap(sp[u],sp[v]);
	u=sp[u];v=sp[v];int k=v-u+1;
	int res=ind[u][Log[k]];
	if (ST[v-(1<<Log[k])+1][Log[k]]<ST[u][Log[k]]) res=ind[v-(1<<Log[k])+1][Log[k]];
	return res;
}

int main ()
{
#ifdef LOCAL
	double TIME=clock();
	freopen ("a.in","r",stdin);
	freopen ("a.out","w",stdout);
	cerr<<"Running..."<<endl;
#endif
	io.Get(n);io.Get(q);
	construct(1,n,0);init_ST();
	int x,y,xx,yy,ans;
	while (q--)
	{
		io.Get(x);io.Get(y);xx=x;yy=y;x=pos[x];y=pos[y];
		int LCA=getlca(x,y);
		if (interval[LCA].x==xx && interval[LCA].y==yy) LCA=anc[LCA][0];
		ans=max(depth[L[x]]-1,depth[LCA])+max(depth[R[y]]-1,depth[LCA])-depth[LCA];
		io.Print(ans,'\n');
	}
	io.flush();
#ifdef LOCAL
	cerr<<"Exec Time: "<<(clock()-TIME)/CLOCKS_PER_SEC<<endl;
#endif
	return 0;
}