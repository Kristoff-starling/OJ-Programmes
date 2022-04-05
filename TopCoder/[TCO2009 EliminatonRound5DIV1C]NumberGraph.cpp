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

int a[148],n;
bool visited[1000048];
int ga[148][148];

int A[148],B[148],atot,btot;

namespace flow
{
	int head[10048],cur[10048],to[20048],nxt[20048],f[20048],tot,t;
	inline void init(int _t) {tot=1;t=_t;for (register int i=0;i<=t;i++) head[i]=0;}
	inline void addedge(int s,int t,int cap)
	{
		to[++tot]=t;nxt[tot]=head[s];head[s]=tot;f[tot]=cap;
		to[++tot]=s;nxt[tot]=head[t];head[t]=tot;f[tot]=0;
	}
	int depth[10048],q[10048],Head,Tail;
	inline bool bfs()
	{
		for (register int i=0;i<=t;i++) depth[i]=-1;
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
			y=to[i];
			if (depth[y]==depth[x]+1 && f[i])
			{
				minf=min(maxf-ans,f[i]);
				now=dfs(y,minf);
				f[i]-=now;f[i^1]+=now;ans+=now;
			}
			if (ans>=maxf) return ans;
		}
		if (!ans) depth[x]=0;
		return ans;
	}
	inline int dinic()
	{
		int res=0;
		while (bfs())
		{
			for (register int i=0;i<=t;i++) cur[i]=head[i];
			res+=dfs(0,INF);
		}
		return res;
	}
}

class NumberGraph
{
	inline void doit_input(vector<string> graphSet)
	{
		string s="";
		for (auto item : graphSet) s+=item;
		s+=" ";
		n=0;int cur=0;
		for (register int i=0;i<int(s.size());i++)
			if (isdigit(s[i])) cur=cur*10+s[i]-'0'; else a[++n]=cur,cur=0;
	}
	inline int solve()
	{
		flow::init(n+1);
		for (register int i=1;i<=atot;i++) flow::addedge(0,A[i],1);
		for (register int j=1;j<=btot;j++) flow::addedge(B[j],n+1,1);
		for (register int i=1;i<=atot;i++)
			for (register int j=1;j<=btot;j++)
				if (!ga[A[i]][B[j]]) flow::addedge(A[i],B[j],1);
		return atot+btot-flow::dinic();
	}
	inline void Clear()
	{
		memset(ga,0,sizeof(ga));
		memset(visited,false,sizeof(visited));
	}
	public:
		inline int largestSet(vector<string> graphSet,vector<int> joiningSet)
		{
			doit_input(graphSet);int ans=1;Clear();
			for (auto item : joiningSet) visited[item]=true;
			for (register int i=1;i<=n;i++)
				for (register int j=1;j<=n;j++)
					if (i!=j && visited[myabs(a[i]-a[j])]) ga[i][j]=1;
			for (register int i=1;i<=n;i++)
				for (register int j=i+1;j<=n;j++)
					if (ga[i][j])
					{
						atot=0;for (register int k=1;k<=n;k++) if (ga[i][k] && k!=j) A[++atot]=k;
						btot=0;for (register int k=1;k<=n;k++) if (ga[j][k] && k!=i) B[++btot]=k;
						check_max(ans,2+solve());
					}
			return ans;
		}
};

/* --- Debug Part ---*/
/*
int main ()
{
#ifndef ONLINE_JUDGE
	double TIME=clock();
	freopen ("a.in","r",stdin);
	freopen ("a.out","w",stdout);
	cerr<<"Running..."<<endl;
#endif
	int nn,mm;string s;int x;vector<string> aa;vector<int> bb;
	NumberGraph A;
	while (cin>>nn>>mm)
	{
		aa.clear();bb.clear();getchar();
		while (nn--) getline(cin,s),aa.pb(s);
		while (mm--) cin>>x,bb.pb(x);
		cout<<A.largestSet(aa,bb)<<endl;
	}
	io.flush();
#ifndef ONLINE_JUDGE
	cerr<<"Exec Time: "<<(clock()-TIME)/CLOCKS_PER_SEC<<endl;
#endif
	return 0;
}
*/
