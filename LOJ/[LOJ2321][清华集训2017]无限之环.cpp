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

template<typename T> inline void Get(T &x)
{
	bool f;char ch;T res;
	while (!isdigit(ch=getchar()) && ch!='-') {}
	if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
	while (isdigit(ch=getchar())) res=res*10+ch-'0';
	x=(f?res:(-res));
}

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

int n,m;
int a[2048][2048];

int ind;
inline int getind(int x,int y) {return (x-1)*m+y;}
inline int getrow(int x,int y) {return n*m+(x-1)*m+y;}
inline int getcol(int x,int y) {return n*m+(n+1)*m+(x-1)*(m+1)+y;}

namespace flow
{
	int head[100048],cur[100048],to[100048],nxt[100048],f[100048],cost[100048],tot=1,t;
	bool visited[100048];int D[100048],maxflow,mincost;
	inline void addedge(int s,int t,int cap,int cc)
	{
		to[++tot]=t;nxt[tot]=head[s];head[s]=tot;f[tot]=cap;cost[tot]=cc;
		to[++tot]=s;nxt[tot]=head[t];head[t]=tot;f[tot]=0;cost[tot]=-cc;
	}
	inline int aug(int x,int maxf)
	{
		if (x==t) {maxflow+=maxf;mincost+=(-D[0])*maxf;return maxf;}
		visited[x]=true;int y,minf,now,ans=0;
		for (register int &i=cur[x];i;i=nxt[i])
		{
			y=to[i];
			if (f[i] && !visited[y] && D[x]+cost[i]-D[y]==0)
			{
				minf=min(maxf-ans,f[i]);
				now=aug(y,minf);
				f[i]-=now;f[i^1]+=now;ans+=now;
			}
			if (ans>=maxf) return ans;
		}
		return ans;
	}
	inline bool relabel()
	{
		int d=INF;
		for (register int cur=0;cur<=t;cur++)
			if (visited[cur])
				for (register int i=head[cur];i;i=nxt[i])
				{
					int y=to[i];
					if (!visited[y] && f[i]) check_min(d,D[cur]+cost[i]-D[y]);
				}
		if (d>=INF) return false;
		for (register int cur=0;cur<=t;cur++) if (visited[cur]) D[cur]-=d;
		return true;
	}
	inline Pair zkw()
	{
		maxflow=mincost=0;
		do
		{
			for (register int i=0;i<=t;i++) cur[i]=head[i];
			do
				for (register int i=0;i<=t;i++) visited[i]=false;
			while (aug(0,INF));
		}
		while (relabel());
		return mp(maxflow,mincost);
	}
}

inline void add_line_black(int x,int y,int type)
{
	flow::addedge(0,getind(x,y),2,0);
	if (type==5) flow::addedge(getind(x,y),getrow(x,y),1,0),flow::addedge(getind(x,y),getrow(x+1,y),1,0);
	else flow::addedge(getind(x,y),getcol(x,y),1,0),flow::addedge(getind(x,y),getcol(x,y+1),1,0);
}

inline void add_point_black(int x,int y,int type)
{
	flow::addedge(0,getind(x,y),1,0);int w[5];
	for (register int i=1;i<=4;i++) w[i]=1;
	for (register int i=1;i<=4;i++) if (type&(1<<(i-1))) w[i]--,w[(i<=2)?(i+2):(i-2)]++;
	flow::addedge(getind(x,y),getrow(x,y),1,w[1]);flow::addedge(getind(x,y),getcol(x,y+1),1,w[2]);
	flow::addedge(getind(x,y),getrow(x+1,y),1,w[3]);flow::addedge(getind(x,y),getcol(x,y),1,w[4]);
}

inline void add_double_black(int x,int y,int type)
{
	flow::addedge(0,getind(x,y),2,0);int w[5];
	for (register int i=1;i<=4;i++) w[i]=((type&(1<<(i-1)))?0:1);
	++ind;flow::addedge(getind(x,y),ind,1,0);flow::addedge(ind,getrow(x,y),1,w[1]);flow::addedge(ind,getrow(x+1,y),1,w[3]);
	++ind;flow::addedge(getind(x,y),ind,1,0);flow::addedge(ind,getcol(x,y),1,w[4]);flow::addedge(ind,getcol(x,y+1),1,w[2]);
}

inline void add_triple_black(int x,int y,int type)
{
	flow::addedge(0,getind(x,y),3,0);int w[5];
	for (register int i=1;i<=4;i++) w[i]=1;
	for (register int i=1;i<=4;i++) if (!(type&(1<<(i-1)))) w[i]++,w[(i<=2)?(i+2):(i-2)]--;
	flow::addedge(getind(x,y),getrow(x,y),1,w[1]);flow::addedge(getind(x,y),getcol(x,y+1),1,w[2]);
	flow::addedge(getind(x,y),getrow(x+1,y),1,w[3]);flow::addedge(getind(x,y),getcol(x,y),1,w[4]);
}

inline void add_beautiful_black(int x,int y,int type)
{
	flow::addedge(0,getind(x,y),4,0);
	flow::addedge(getind(x,y),getrow(x,y),1,0);flow::addedge(getind(x,y),getrow(x+1,y),1,0);
	flow::addedge(getind(x,y),getcol(x,y),1,0);flow::addedge(getind(x,y),getcol(x,y+1),1,0);
}

inline void add_line_white(int x,int y,int type)
{
	flow::addedge(getind(x,y),flow::t,2,0);
	if (type==5) flow::addedge(getrow(x,y),getind(x,y),1,0),flow::addedge(getrow(x+1,y),getind(x,y),1,0);
	else flow::addedge(getcol(x,y),getind(x,y),1,0),flow::addedge(getcol(x,y+1),getind(x,y),1,0);
}

inline void add_point_white(int x,int y,int type)
{
	flow::addedge(getind(x,y),flow::t,1,0);int w[5];
	for (register int i=1;i<=4;i++) w[i]=1;
	for (register int i=1;i<=4;i++) if (type&(1<<(i-1))) w[i]--,w[(i<=2)?(i+2):(i-2)]++;
	flow::addedge(getrow(x,y),getind(x,y),1,w[1]);flow::addedge(getcol(x,y+1),getind(x,y),1,w[2]);
	flow::addedge(getrow(x+1,y),getind(x,y),1,w[3]);flow::addedge(getcol(x,y),getind(x,y),1,w[4]);
}

inline void add_double_white(int x,int y,int type)
{
	flow::addedge(getind(x,y),flow::t,2,0);int w[5];
	for (register int i=1;i<=4;i++) w[i]=((type&(1<<(i-1)))?0:1);
	++ind;flow::addedge(ind,getind(x,y),1,0);flow::addedge(getrow(x,y),ind,1,w[1]);flow::addedge(getrow(x+1,y),ind,1,w[3]);
	++ind;flow::addedge(ind,getind(x,y),1,0);flow::addedge(getcol(x,y),ind,1,w[4]);flow::addedge(getcol(x,y+1),ind,1,w[2]);
}

inline void add_triple_white(int x,int y,int type)
{
	flow::addedge(getind(x,y),flow::t,3,0);int w[5];
	for (register int i=1;i<=4;i++) w[i]=1;
	for (register int i=1;i<=4;i++) if (!(type&(1<<(i-1)))) w[i]++,w[(i<=2)?(i+2):(i-2)]--;
	flow::addedge(getrow(x,y),getind(x,y),1,w[1]);flow::addedge(getcol(x,y+1),getind(x,y),1,w[2]);
	flow::addedge(getrow(x+1,y),getind(x,y),1,w[3]);flow::addedge(getcol(x,y),getind(x,y),1,w[4]);
}

inline void add_beautiful_white(int x,int y,int type)
{
	flow::addedge(getind(x,y),flow::t,4,0);
	flow::addedge(getrow(x,y),getind(x,y),1,0);flow::addedge(getrow(x+1,y),getind(x,y),1,0);
	flow::addedge(getcol(x,y),getind(x,y),1,0);flow::addedge(getcol(x,y+1),getind(x,y),1,0);
}

int main ()
{
#ifdef LOCAL
	double TIME=clock();
	freopen ("a.in","r",stdin);
	freopen ("a.out","w",stdout);
	cerr<<"Running..."<<endl;
#endif
	Get(n);Get(m);int cnt=0,sum=0;
	ind=n*m+(n+1)*m+n*(m+1);flow::t=(n+1)*(m+1)*6;
	for (register int i=1;i<=n;i++)
		for (register int j=1;j<=m;j++)
		{
			Get(a[i][j]);
			if (a[i][j]==0) continue;
			if (a[i][j]==5 || a[i][j]==10 || a[i][j]==3 || a[i][j]==6 || a[i][j]==9 || a[i][j]==12) sum+=2;
			if (a[i][j]==7 || a[i][j]==11 || a[i][j]==13 || a[i][j]==14) cnt++,sum+=3;
			if (a[i][j]==1 || a[i][j]==2 || a[i][j]==4 || a[i][j]==8) sum++;
			if (a[i][j]==15) sum+=4;
			if ((i+j)&1)
			{
				if (a[i][j]==5 || a[i][j]==10) add_line_black(i,j,a[i][j]);
				if (a[i][j]==1 || a[i][j]==2 || a[i][j]==4 || a[i][j]==8) add_point_black(i,j,a[i][j]);
				if (a[i][j]==3 || a[i][j]==6 || a[i][j]==9 || a[i][j]==12) add_double_black(i,j,a[i][j]);
				if (a[i][j]==7 || a[i][j]==11 || a[i][j]==13 || a[i][j]==14) add_triple_black(i,j,a[i][j]);
				if (a[i][j]==15) add_beautiful_black(i,j,a[i][j]);
			}
			else
			{
				if (a[i][j]==5 || a[i][j]==10) add_line_white(i,j,a[i][j]);
				if (a[i][j]==1 || a[i][j]==2 || a[i][j]==4 || a[i][j]==8) add_point_white(i,j,a[i][j]);
				if (a[i][j]==3 || a[i][j]==6 || a[i][j]==9 || a[i][j]==12) add_double_white(i,j,a[i][j]);
				if (a[i][j]==7 || a[i][j]==11 || a[i][j]==13 || a[i][j]==14) add_triple_white(i,j,a[i][j]);
				if (a[i][j]==15) add_beautiful_white(i,j,a[i][j]);
			}
		}
	if (sum&1) {puts("-1");return 0;}
	sum>>=1;Pair res=flow::zkw();
	if (res.x!=sum) puts("-1"); else printf("%d\n",res.y-cnt*2);
	io.flush();
#ifdef LOCAL
	cerr<<"Exec Time: "<<(clock()-TIME)/CLOCKS_PER_SEC<<endl;
#endif
}
