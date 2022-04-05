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

const int MAXN=1e5;

char s[MAXN+48];

int pos[MAXN+48],n,N;
int ans[MAXN+48];

namespace BIT
{
	int c[MAXN+48];
	inline void init() {memset(c,0,sizeof(c));}
	inline void modify(int x,int delta) {while (x<=N) c[x]+=delta,x+=LOWBIT(x);}
	inline int query(int x) {int res=0;while (x) res+=c[x],x^=LOWBIT(x);return res;}
	inline int calc(int l,int r) {return query(r)-query(l-1);}
}

namespace AC_Automaton
{
	int nxt[MAXN+48][27],fa[MAXN+48],fail[MAXN+48],tot,Root;
	vector<int> v[MAXN+48];int L[MAXN+48],R[MAXN+48],ind;
	vector<Pair> Q[MAXN+48];
	inline int Create(int f) {++tot;memset(nxt[tot],0,sizeof(nxt[tot]));fa[tot]=f;fail[tot]=0;return tot;}
	inline void init() {tot=0;Root=Create(0);ind=0;}
	inline void construct_trie(char s[])
	{
		int len=strlen(s+1),cur=Root;n=0;
		for (register int i=1;i<=len;i++)
			if ('a'<=s[i] && s[i]<='z')
			{
				int w=s[i]-'a'+1;
				if (!nxt[cur][w]) nxt[cur][w]=Create(cur);
				cur=nxt[cur][w];
			}
			else if (s[i]=='B') cur=fa[cur];
			else pos[++n]=cur;
		N=tot;
	}
	int q[MAXN+48],head,tail;
	inline void construct_fail()
	{
		head=tail=1;q[1]=Root;fail[Root]=0;
		while (head<=tail)
		{
			int cur=q[head++];v[fail[cur]].pb(cur);
			for (register int i=1;i<=26;i++)
				if (nxt[cur][i])
				{
					int tmp=fail[cur];
					while (tmp && !nxt[tmp][i]) tmp=fail[tmp];
					fail[nxt[cur][i]]=((!tmp)?Root:nxt[tmp][i]);
					q[++tail]=nxt[cur][i];
				}
		}
	}
	inline void dfs(int cur)
	{
		L[cur]=++ind;
		for (auto y : v[cur]) dfs(y);
		R[cur]=ind;
	}
	inline void solve(int cur)
	{
		BIT::modify(L[cur],1);
		for (register int i=0;i<int(Q[cur].size());i++)
		{
			int id=Q[cur][i].y,x=Q[cur][i].x;
			ans[id]=BIT::calc(L[x],R[x]);
		}
		for (register int i=1;i<=26;i++) if (nxt[cur][i]) solve(nxt[cur][i]);
		BIT::modify(L[cur],-1);
	}
}

int main ()
{
#ifndef ONLINE_JUDGE
	double TIME=clock();
	freopen ("a.in","r",stdin);
	freopen ("a.out","w",stdout);
	cerr<<"Running..."<<endl;
#endif
	scanf("%s",s+1);int q,x,y;
	AC_Automaton::init();AC_Automaton::construct_trie(s);
	AC_Automaton::construct_fail();AC_Automaton::dfs(1);
	scanf("%d",&q);
	for (register int i=1;i<=q;i++)
	{
		scanf("%d%d",&x,&y);
		AC_Automaton::Q[pos[y]].pb(mp(pos[x],i));
	}
	AC_Automaton::solve(1);
	for (register int i=1;i<=q;i++) printf("%d\n",ans[i]);
	io.flush();
#ifndef ONLINE_JUDGE
	cerr<<"Exec Time: "<<(clock()-TIME)/CLOCKS_PER_SEC<<endl;
#endif
	return 0;
}
