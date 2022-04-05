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

namespace flow
{
	const int MAXN=1e5;
	int head[MAXN+48],cur[MAXN+48],to[MAXN+48],nxt[MAXN+48],f[MAXN+48],tot,t;
	inline void init(int _t) {t=_t;tot=1;rep(i,0,t) head[i]=0;}
	inline void addedge(int s,int t,int cap)
	{
		to[++tot]=t;nxt[tot]=head[s];head[s]=tot;f[tot]=cap;
		to[++tot]=s;nxt[tot]=head[t];head[t]=tot;f[tot]=0;
	}
	int q[MAXN+48],Head,Tail,depth[MAXN+48];
	inline bool bfs()
	{
		rep(i,0,t) depth[i]=-1;
		depth[0]=0;Head=Tail=1;q[1]=0;
		while (Head<=Tail)
		{
			int x=q[Head++];
			for (register int i=head[x];i;i=nxt[i])
			{
				int y=to[i];
				if (depth[y]==-1 && f[i])
				{
					depth[y]=depth[x]+1;
					q[++Tail]=y;
				}
			}
		}
		return depth[t]!=-1;
	}
	inline int dfs(int x,int maxf)
	{
		if (x==t) return maxf;
		int y,minf,now,ans=0;
		for (register int &i=cur[x];i;i=nxt[i])
		{
			int y=to[i];
			if (depth[y]==depth[x]+1 && f[i])
			{
				minf=min(maxf-ans,f[i]);
				now=dfs(y,minf);
				f[i]-=now;f[i^1]+=now;ans+=now;
			}
			if (ans>=maxf) break;
		}
		if (!ans) depth[x]=0;
		return ans;
	}
	inline int dinic()
	{
		int ans=0;
		while (bfs())
		{
			rep(i,0,t) cur[i]=head[i];
			ans+=dfs(0,INF);
		}
		return ans;
	}
}

class RatingProgressAward
{
	public:
		inline int maximalProgress(vector<int> change,vector<int> a,vector<int> b)
		{
			int n=int(change.size()),m=int(a.size()),sum=0;flow::init(n*2+1);
			rep(i,0,m-1) a[i]++,b[i]++;
			rep(i,1,n)
				if (change[i-1]>0) sum+=change[i-1],flow::addedge(0,i,change[i-1]),flow::addedge(i+n,flow::t,change[i-1]);
				else flow::addedge(i,i+n,-change[i-1]);
			rep(i,0,m-1) flow::addedge(a[i],b[i],INF),flow::addedge(a[i]+n,b[i]+n,INF);
			return sum-flow::dinic();
		}
};

/*--- Debug Part ---*/
/*
int main ()
{
#ifndef ONLINE_JUDGE
	double TIME=clock();
	freopen ("a.in","r",stdin);
	freopen ("a.out","w",stdout);
	cerr<<"Running..."<<endl;
#endif
	vector<int> aa,bb,cc;int x;
	RatingProgressAward A;
	int n,m;
	while (cin>>n>>m)
	{
		aa.clear();bb.clear();cc.clear();
		rep(i,1,n) cin>>x,cc.pb(x);
		rep(i,1,m) cin>>x,aa.pb(x);
		rep(i,1,m) cin>>x,bb.pb(x);
		cout<<A.maximalProgress(cc,aa,bb)<<endl;
	}
	io.flush();
#ifndef ONLINE_JUDGE
	cerr<<"Exec Time: "<<(clock()-TIME)/CLOCKS_PER_SEC<<endl;
#endif
	return 0;
}
*/
