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
    template <class T> inline void Get(T &x)
    {
        char ch;bool f;T res;
        while (!isdigit(ch=Getchar()) && ch!='-') {}
        if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
        while (isdigit(ch=Getchar())) res=res*10+ch-'0';
        x=(f?res:-res);
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

int n;
vector<int> v[MAXN+48];
int depth[MAXN+48],d[MAXN+48];
int anc[MAXN+48][21];

int sa[MAXN+48];

const int p1=100003,p2=100019;
const int m1=19260817,m2=998244353;

LL hsh1[MAXN+48][21],hsh2[MAXN+48][21],pw1[MAXN+48],pw2[MAXN+48];

inline void init_hash()
{
	pw1[0]=pw2[0]=1;
	for (register int i=1;i<=n;i++) pw1[i]=pw1[i-1]*p1%m1,pw2[i]=pw2[i-1]*p2%m2;
}

inline void dfs(int cur,int father)
{
	anc[cur][0]=father;depth[cur]=depth[father]+1;
	hsh1[cur][0]=hsh2[cur][0]=d[cur];
	for (register int i=1;i<=17;i++)
	{
		anc[cur][i]=anc[anc[cur][i-1]][i-1];
		hsh1[cur][i]=(hsh1[cur][i-1]*pw1[1<<(i-1)]%m1+hsh1[anc[cur][i-1]][i-1])%m1;
		hsh2[cur][i]=(hsh2[cur][i-1]*pw2[1<<(i-1)]%m2+hsh2[anc[cur][i-1]][i-1])%m2;
	}
	for (auto y : v[cur]) if (y!=father) dfs(y,cur);
}

inline pair<int,bool> query_lcp(int u,int v)
{
	int res=0,minn=min(depth[u],depth[v]);
	if (d[u]!=d[v]) return mp(0,d[u]<d[v]);
	for (register int i=17;i>=0;i--)
	{
		if (res+(1<<i)>minn) continue;
		if (hsh1[u][i]==hsh1[v][i] && hsh2[u][i]==hsh2[v][i]) res+=(1<<i),u=anc[u][i],v=anc[v][i];
	}
	return mp(res,d[u]<d[v]);
}

inline bool cmp(int u,int v) {return query_lcp(u,v).y;}

int main ()
{
	Get(n);int x,y;
	for (register int i=1;i<=n-1;i++) Get(x,y),v[x].pb(y),v[y].pb(x),d[x]++,d[y]++;
	init_hash();dfs(1,0);
	for (register int i=1;i<=n;i++) sa[i]=i;
	sort(sa+1,sa+n+1,cmp);
	LL ans=0;for (register int i=1;i<=n;i++) ans+=depth[i];
	for (register int i=1;i<=n-1;i++) ans-=query_lcp(sa[i],sa[i+1]).x;
	printf("%lld\n",ans);
	return 0;
}
