#include <bits/stdc++.h>
using namespace std;

#define LL long long
#define LB long double
#define uint unsigned int 
#define ull unsigned long long
#define x first
#define y second
#define pb push_back
#define pf push_front
#define mp make_pair
#define Pair pair<int,int>
#define pLL pair<LL,LL>
#define pii pair<double,double>

const int INF=2e9;
const LL LINF=2e16;
const int magic=348;
const int MOD=998244353;
const double eps=1e-10;
const double pi=acos(-1);

struct fastio
{
	static const int S=1e7;
	char rbuf[S+48],wbuf[S+48];int rlen,wlen;
	fastio () {rlen=wlen=0;}
	inline char Getchar()
	{
		if (rlen==S) rlen=0,fread(rbuf,1,S,stdin);
		return rbuf[rlen++];
	}
	template <class T> inline void Get(T &x)
	{
		T res=0;char ch;bool f;
		while (!isdigit(ch=Getchar()) && ch!='-') {}
		if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
		while (isdigit(ch=Getchar())) res=res*10+ch-'0';
		x=res;
	}
	inline void flush() {fwrite(wbuf,1,wlen,stdout);rlen=0;}
	inline void Writechar(char ch)
	{
		wbuf[wlen++]=ch;
		if (wlen==S) flush();
	}
	template <class T> inline void Print(T res,char ch)
	{
		char s[48];int pt;
		if (res==0)
		{
			pt=1;
			s[1]='0';
		}
		else
		{
			bool f=true;if (res<0) f=false,res=-res;
			pt=0;while (res) s[++pt]=res%10+'0',res/=10;
			if (!f) s[++pt]='-';
		}
		while (pt>=1) Writechar(s[pt--]);
		Writechar(ch);
	}
	inline void printstring(string s)
	{
		int len=int(s.size());
		for (register int i=0;i<len;i++) Writechar(s[i]);
		Writechar('\n');
	}
}io;

const int MAXN=5e5;

int n,e,q;
vector<Pair> v[MAXN+48];
int depth[MAXN+48];

struct Edge
{
	int u,v;
	Edge () {}
	inline Edge (int uu,int vv) {u=uu;v=vv;}
}edge[MAXN+48];
bool intree[MAXN+48];
int xsum[MAXN+48],faedge[MAXN+48];
int val[MAXN+48];

inline void dfs(int cur,int father)
{
	for (register int i=0;i<int(v[cur].size());i++)
		if (!depth[v[cur][i].x])
		{
			intree[v[cur][i].y]=true;depth[v[cur][i].x]=depth[cur]+1;
			faedge[v[cur][i].x]=v[cur][i].y;
			dfs(v[cur][i].x,cur);
		}
}

inline void Dfs(int cur,int father)
{
	for (register int i=0;i<int(v[cur].size());i++)
		if (v[cur][i].x!=father && intree[v[cur][i].y]) Dfs(v[cur][i].x,cur);
	for (register int i=0;i<int(v[cur].size());i++)
		if (v[cur][i].x!=father && intree[v[cur][i].y]) xsum[faedge[cur]]^=xsum[v[cur][i].y];
}

namespace LinerBase
{
	int b[48];
	inline void init() {memset(b,0,sizeof(b));}
	inline bool insert(int x)
	{
		for (register int i=30;i>=0;i--)
			if ((x>>i)&1)
			{
				if (!b[i]) {b[i]=x;return true;}
				else x^=b[i];
			}
		return false;
	}
}

int main ()
{
	srand(time(NULL));
	io.Get(n);io.Get(e);int x,y;
	for (register int i=1;i<=e;i++)
	{
		io.Get(x);io.Get(y);edge[i]=Edge(x,y);
		v[x].pb(mp(y,i));v[y].pb(mp(x,i));
	}
	depth[1]=1;dfs(1,-1);
	for (register int i=1;i<=e;i++)
		if (!intree[i])
		{
			x=edge[i].u;y=edge[i].v;
			if (depth[x]>depth[y]) swap(x,y);			
			val[i]=rand();
			xsum[faedge[y]]^=val[i];
			if (faedge[x]) xsum[faedge[x]]^=val[i];
		}
	Dfs(1,-1);
	for (register int i=1;i<=e;i++) if (intree[i]) val[i]=xsum[i];
	io.Get(q);int cnt=0,k;
	while (q--)
	{
		LinerBase::init();
		io.Get(k);bool f=true;
		while (k--)
		{
			io.Get(x);x^=cnt;
			assert(1<=x && x<=e);
			if (!LinerBase::insert(val[x])) f=false;
		}
		if (f) io.printstring("Connected"),cnt++; else io.printstring("Disconnected");
	}
	io.flush();return 0;
}
