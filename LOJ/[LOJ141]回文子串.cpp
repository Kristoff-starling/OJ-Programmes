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
#define rep(i,l,r) for (register int i=int(l);i<=int(r);i++)
#define Rep(i,l,r) for (register int i=int(l);i<int(r);i++)
#define REP(i,r,l) for (register int i=int(r);i>=int(l);i--)

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
    template<typename T> inline void Get(T &x)
    {
        char ch;bool f;T res;
        while (!isdigit(ch=Getchar()) && ch!='-') {}
        if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
        while (isdigit(ch=Getchar())) res=res*10+ch-'0';
        x=(f?res:(-res));
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
    template<typename T> inline void Print(T x,char ch)
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
	template<typename T1,typename ...T2> inline void Print(T1 &x,T2 &...y) {Print(x,' ');Print(y...,' ');Writechar('\n');}
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
template<typename T> inline T add(T x) {if (x>=MOD) x-=MOD;return x;}
template<typename T> inline T add(T x,int MO) {if (x>=MO) x-=MO;return x;}
template<typename T> inline T sub(T x) {if (x<0) x+=MOD;return x;}
template<typename T> inline T sub(T x,int MO) {if (x<0) x+=MO;return x;}
template<typename T> inline T mul(T x,T y) {return 1ll*x*y%MOD;}
template<typename T> inline T mul(T x,T y,int MO) {return 1ll*x*y%MO;}
template<typename T> inline void Add(T &x,T y) {x=add(x+y);}
template<typename T> inline void Add(T &x,T y,int MO) {x=add(x+y,MO);}
template<typename T> inline void Sub(T &x,T y) {x=sub(x-y);}
template<typename T> inline void Sub(T &x,T y,int MO) {x=sub(x-y,MO);}
template<typename T> inline void Mul(T &x,T y) {x=mul(x,y);}
template<typename T> inline void Mul(T &x,T y,int MO) {x=mul(x,y,MO);}
template<typename T> inline int quick_pow(int x,T y) {int res=1;while (y) {if (y&1) res=1ll*res*x%MOD;x=1ll*x*x%MOD;y>>=1;}return res;}
template<typename T> inline int quick_pow(int x,T y,int MO) {int res=1;while (y) {if (y&1) res=1ll*res*x%MO;x=1ll*x*x%MO;y>>=1;}return res;}

const int MAXN=4e5;

char s[1000048],ss[MAXN+48];LL ans=0;int l,r;

namespace PAM
{
	struct node
	{
		int nxt[27],len,fail,depth;
	}tree[MAXN*2];int tot,llast,rlast;
	inline void init() {tree[0].len=0;tree[1].len=-1;tree[0].fail=1;tree[0].depth=tree[1].depth=0;tot=1;llast=rlast=0;memset(tree[0].nxt,0,sizeof(tree[0].nxt));memset(tree[1].nxt,0,sizeof(tree[1].nxt));}
	inline void Create()
	{
		++tot;memset(tree[tot].nxt,0,sizeof(tree[tot].nxt));
		tree[tot].len=tree[tot].fail=tree[tot].depth=0;
	}
	inline void extend_back(int pos)
	{
		int w=s[pos]-'a'+1;
		while (s[pos-tree[rlast].len-1]!=s[pos]) rlast=tree[rlast].fail;
		if (!tree[rlast].nxt[w])
		{
			Create();tree[tot].len=tree[rlast].len+2;
			int tmp=tree[rlast].fail;
			while (s[pos-tree[tmp].len-1]!=s[pos]) tmp=tree[tmp].fail;
			tree[tot].fail=tree[tmp].nxt[w];tree[tot].depth=tree[tree[tot].fail].depth+1;
			tree[rlast].nxt[w]=tot;
		}
		rlast=tree[rlast].nxt[w];
		ans+=tree[rlast].depth;
		if (tree[rlast].len==r-l+1) llast=rlast;
	}
	inline void extend_front(int pos)
	{
		int w=s[pos]-'a'+1;
		while (s[pos+tree[llast].len+1]!=s[pos]) llast=tree[llast].fail;
		if (!tree[llast].nxt[w])
		{
			Create();tree[tot].len=tree[llast].len+2;
			int tmp=tree[llast].fail;
			while (s[pos+tree[tmp].len+1]!=s[pos]) tmp=tree[tmp].fail;
			tree[tot].fail=tree[tmp].nxt[w];tree[tot].depth=tree[tree[tot].fail].depth+1;
			tree[llast].nxt[w]=tot;
		}
		llast=tree[llast].nxt[w];
		ans+=tree[llast].depth;
		if (tree[llast].len==r-l+1) rlast=llast;
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
	memset(s,'%',sizeof(s));l=450000;r=l-1;PAM::init();
	scanf("%s",ss+1);int len=strlen(ss+1);rep(i,1,len) s[++r]=ss[i],PAM::extend_back(r);
	int op,q;scanf("%d",&q);
	while (q--)
	{
		scanf("%d",&op);
		if (op==1 || op==2) scanf("%s",ss+1),len=strlen(ss+1);
		if (op==1) rep(i,1,len) s[++r]=ss[i],PAM::extend_back(r);
		if (op==2) rep(i,1,len) s[--l]=ss[i],PAM::extend_front(l);
		if (op==3) printf("%lld\n",ans);
	}
#ifndef ONLINE_JUDGE
	cerr<<"Exec Time: "<<(clock()-TIME)/CLOCKS_PER_SEC<<endl;
#endif
	return 0;
}
