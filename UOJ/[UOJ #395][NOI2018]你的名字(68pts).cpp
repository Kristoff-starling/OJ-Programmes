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

const int MAXN=5e5;

struct SAM
{
	int nxt[MAXN*2][27],par[MAXN*2],maxn[MAXN*2],occ[MAXN*2],root,last,tot;
	inline void init() {root=last=tot=1;memset(nxt[1],0,sizeof(nxt[1]));}
	inline int Create() {++tot;memset(nxt[tot],0,sizeof(nxt[tot]));maxn[tot]=0;occ[tot]=0;par[tot]=0;return tot;}
	Pair ord[MAXN*2];
	inline void extend(char ch,int ind)
	{
		int p=last,np=Create(),w=ch-'a'+1;occ[np]=ind;maxn[np]=maxn[p]+1;
		while (p && !nxt[p][w]) nxt[p][w]=np,p=par[p];
		if (!p) {par[np]=root;last=np;return;}
		int q=nxt[p][w];if (maxn[q]==maxn[p]+1) {par[np]=q;last=np;return;}
		int nq=Create();maxn[nq]=maxn[p]+1;memcpy(nxt[nq],nxt[q],sizeof(nxt[q]));
		par[nq]=par[q];par[q]=par[np]=nq;
		while (p && nxt[p][w]==q) nxt[p][w]=nq,p=par[p];
		last=np;
	}
	inline void construct(char s[])
	{
		init();int len=strlen(s+1);
		for (register int i=1;i<=len;i++) extend(s[i],i);
	}
	inline void update()
	{
		for (register int i=1;i<=tot;i++) ord[i]=mp(maxn[i],i);
		sort(ord+1,ord+tot+1);
		for (register int i=tot;i>=2;i--) if (occ[ord[i].y]) occ[par[ord[i].y]]=occ[ord[i].y];
	}
}s1,s2;

char s[MAXN+48],t[MAXN+48];int len1,len2;
int d[MAXN+48];

inline LL solve1()
{
	len2=strlen(t+1);int cur=s1.root,cnt=0;
	s2.construct(t);s2.update();
	for (register int i=1;i<=len2;i++)
	{
		int w=t[i]-'a'+1;
		while (cur && !s1.nxt[cur][w]) cur=s1.par[cur],cnt=s1.maxn[cur];
		if (!cur) cur=s1.root,cnt=0; else cur=s1.nxt[cur][w],cnt++;
		d[i]=cnt;
	}
	LL ans=0;
	for (register int i=2;i<=s2.tot;i++) ans+=max(0,s2.maxn[i]-max(s2.maxn[s2.par[i]],d[s2.occ[i]]));
	return ans;
}

int main ()
{
#ifdef LOCAL
	double TIME=clock();
	freopen ("a.in","r",stdin);
	freopen ("a.out","w",stdout);
	cerr<<"Running..."<<endl;
#endif
	scanf("%s",s+1);s1.construct(s);len1=strlen(s+1);
	int q,l,r;scanf("%d",&q);
	while (q--)
	{
		scanf("%s",t+1);scanf("%d%d",&l,&r);
		if (l==1 && r==len1) printf("%lld\n",solve1());
	}
	io.flush();
#ifdef LOCAL
	cerr<<"Exec Time: "<<(clock()-TIME)/CLOCKS_PER_SEC<<endl;
#endif
}
