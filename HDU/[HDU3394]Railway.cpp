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

int n,m;
vector<int> v[MAXN+48];

int sta[MAXN+48],stot;
int bel[MAXN+48],dfn[MAXN+48],low[MAXN+48],ind,cnt;
Pair edge[MAXN+48];

int bridge,Cnt;

inline void Clear()
{
	ind=cnt=stot=0;bridge=Cnt=0;
	for (register int i=1;i<=n;i++) bel[i]=0,v[i].clear(),dfn[i]=0;
}

inline bool check(int id,Pair E)
{
	if (edge[id]==E) return true;
	swap(E.x,E.y);if (edge[id]==E) return true;
	return false;
}

inline int getanother(int id,int x)
{
	if (x==edge[id].x) return edge[id].y; else return edge[id].x;
}

inline void tarjan(int cur,int father)
{
	dfn[cur]=low[cur]=++ind;
	for (auto id : v[cur])
	{
		int y=getanother(id,cur);
		if (!dfn[y])
		{
			sta[++stot]=id;tarjan(y,cur);
			check_min(low[cur],low[y]);
			if (low[y]>dfn[cur]) bridge++;
			if (low[y]>=dfn[cur])
			{
				int node_cnt=0,edge_cnt=0;++cnt;
				while (stot)
				{
					int tmp=sta[stot--];++edge_cnt;
					if (bel[edge[tmp].x]!=cnt) bel[edge[tmp].x]=cnt,node_cnt++;
					if (bel[edge[tmp].y]!=cnt) bel[edge[tmp].y]=cnt,node_cnt++;
					if (check(tmp,mp(cur,y))) break;
				}
				if (edge_cnt>node_cnt) Cnt+=edge_cnt;
			}
		}
		else if (y!=father && dfn[y]<dfn[cur])
		{
			sta[++stot]=id;
			check_min(low[cur],dfn[y]);
		}
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
	int x,y;
	while (scanf("%d%d",&n,&m) && (n || m))
	{
		Clear();
		for (register int i=1;i<=m;i++)
		{
			scanf("%d%d",&x,&y);++x;++y;edge[i]=mp(x,y);
			v[x].pb(i);v[y].pb(i);
		}
		for (register int i=1;i<=n;i++) if (!dfn[i]) tarjan(i,0);
		printf("%d %d\n",bridge,Cnt);
	}
	io.flush();
#ifndef ONLINE_JUDGE
	cerr<<"Exec Time: "<<(clock()-TIME)/CLOCKS_PER_SEC<<endl;
#endif
	return 0;
}
