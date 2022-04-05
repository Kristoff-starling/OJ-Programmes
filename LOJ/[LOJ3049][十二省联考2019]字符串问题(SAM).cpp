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

const int MAXN=2e5;

char s[MAXN+48];int len;
int na,nb,m;
int posa[MAXN+48],lena[MAXN+48],posb[MAXN+48],lenb[MAXN+48];
vector<int> bel[MAXN+48];

int tot;
vector<int> ta[MAXN*2],tb[MAXN*2];
vector<int> vv[MAXN*10+48];int d[MAXN*10+48],val[MAXN*10+48];

int head,tail,q[MAXN*10+48];
LL dp[MAXN*10+48];

inline void addedge(int x,int y) {vv[x].pb(y);d[y]++;}

inline bool cmp_lena(int x,int y) {return lena[x]<lena[y];}
inline bool cmp_lenb(int x,int y) {return lenb[x]<lenb[y];}

namespace SAM
{
	int nxt[MAXN*2][27],maxn[MAXN*2],minn[MAXN*2],par[MAXN*2],last,Root;
	vector<int> v[MAXN*2];int anc[MAXN*2][21],pos[MAXN+48];
	inline int Create() {++tot;maxn[tot]=0;memset(nxt[tot],0,sizeof(nxt[tot]));par[tot]=0;return tot;}
	inline void init() {tot=0;Root=last=Create();}
	inline void extend(char ch,int ind)
	{
		int p=last,np=Create(),w=ch-'a'+1;last=np;maxn[np]=maxn[p]+1;pos[ind]=np;
		while (p && !nxt[p][w]) nxt[p][w]=np,p=par[p];
		if (!p) {par[np]=Root;return;}
		int q=nxt[p][w];if (maxn[q]==maxn[p]+1) {par[np]=q;return;}
		int nq=Create();maxn[nq]=maxn[p]+1;memcpy(nxt[nq],nxt[q],sizeof(nxt[q]));
		par[nq]=par[q];par[np]=par[q]=nq;
		while (p && nxt[p][w]==q) nxt[p][w]=nq,p=par[p];
	}
	inline void construct()
	{
		init();
		for (register int i=1;i<=len;i++) extend(s[i],i);
	}
	inline void dfs(int cur)
	{
		if (cur!=Root) minn[cur]=maxn[par[cur]]+1;
		anc[cur][0]=par[cur];
		for (register int i=1;i<=20;i++) anc[cur][i]=anc[anc[cur][i-1]][i-1];
		for (auto y : v[cur]) dfs(y);
	}
	inline void build()
	{
		for (register int i=1;i<=tot;i++) v[i].clear();
		for (register int i=2;i<=tot;i++) v[par[i]].pb(i);
		dfs(Root);
	}
	inline int getnode(int cur,int len)
	{
		if (minn[cur]<=len && len<=maxn[cur]) return cur;
		for (register int i=20;i>=0;i--)
		{
			if (anc[cur][i]<=1) continue;
			if (minn[anc[cur][i]]>len) cur=anc[cur][i];
		}
		return par[cur];
	}
	inline void buildedge()
	{
		for (register int i=2;i<=tot;i++) addedge(tot+par[i],i);
		for (register int i=1;i<=tot;i++) addedge(i,tot+i);
	}
}

inline LL solve(int cur)
{
	if (dp[cur]!=-1) return dp[cur];
	dp[cur]=0;
	for (auto y : vv[cur]) check_max(dp[cur],solve(y));
	return dp[cur]+=val[cur];
}

bool ff;
inline void input()
{
	scanf("%s",s+1);len=strlen(s+1);
	for (register int i=1,j=len;i<j;i++,j--) swap(s[i],s[j]);
	Get(na);int l,r,x,y;
	for (register int i=1;i<=na;i++)
	{
		Get(l,r);
		posa[i]=len-l+1;lena[i]=r-l+1;
	}
	Get(nb);
	for (register int i=1;i<=nb;i++)
	{
		Get(l,r);
		posb[i]=len-l+1;lenb[i]=r-l+1;
	}
	for (register int i=1;i<=na;i++) bel[i].clear();
	Get(m);
	for (register int i=1;i<=m;i++) Get(x,y),bel[x].pb(y);
}

inline void Clear()
{
	for (register int i=1;i<=len*4+na*2+nb;i++) vv[i].clear(),d[i]=0,val[i]=0;	
	for (register int i=1;i<=len*2;i++) ta[i].clear(),tb[i].clear();
	head=1;tail=0;
	for (register int i=1;i<=len*4+na*2+nb;i++) dp[i]=-1;
}

inline void solve()
{
	SAM::construct();SAM::build();int x;
	for (register int i=1;i<=na;i++) x=SAM::getnode(SAM::pos[posa[i]],lena[i]),ta[x].pb(i);
	for (register int i=1;i<=nb;i++) x=SAM::getnode(SAM::pos[posb[i]],lenb[i]),tb[x].pb(i);
	SAM::buildedge();
	for (register int i=1;i<=tot;i++) sort(ta[i].begin(),ta[i].end(),cmp_lena),sort(tb[i].begin(),tb[i].end(),cmp_lenb);
	for (register int i=1;i<=na;i++) addedge(tot*2+i,tot*2+na+i),val[tot*2+na+i]=lena[i];
	for (register int i=1;i<=tot;i++)
	{
		for (register int j=0;j<int(tb[i].size());j++) addedge(tot*2+na*2+tb[i][j],tot+i);
		if (int(ta[i].size())) addedge(i,tot*2+ta[i][0]);
		for (register int j=0;j<int(ta[i].size())-1;j++) addedge(tot*2+ta[i][j],tot*2+ta[i][j+1]);
		int pt=0;
		for (register int j=0;j<int(tb[i].size());j++)
		{
			while (pt<int(ta[i].size()) && lenb[tb[i][j]]>lena[ta[i][pt]]) pt++;
			if (pt<=int(ta[i].size())-1) addedge(tot*2+na*2+tb[i][j],tot*2+ta[i][pt]);
		}
	}
	for (register int i=1;i<=na;i++)
		for (register int j=0;j<int(bel[i].size());j++)
			addedge(tot*2+na+i,tot*2+na*2+bel[i][j]);
	int T=tot*2+na*2+nb,cnt=0;
	for (register int i=1;i<=T;i++) if (!d[i]) q[++tail]=i;
	while (head<=tail)
	{
		int cur=q[head++];cnt++;
		for (auto y : vv[cur])
		{
			d[y]--;
			if (!d[y]) q[++tail]=y;
		}
	}
	if (cnt<T) {puts("-1");return;}
	LL ans=0;
	for (register int i=1;i<=T;i++) check_max(ans,solve(i));
	printf("%lld\n",ans);
}

int main ()
{
#ifndef ONLINE_JUDGE
	double TIME=clock();
	freopen ("a.in","r",stdin);
	freopen ("a.out","w",stdout);
	cerr<<"Running..."<<endl;
#endif
	int ca;Get(ca);
	while (ca--)
	{
		input();
		Clear();
		solve();
	}
	io.flush();
#ifndef ONLINE_JUDGE
	cerr<<"Exec Time: "<<(clock()-TIME)/CLOCKS_PER_SEC<<endl;
#endif
	return 0;
}
