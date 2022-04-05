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

const int INF=2e9;
const LL LINF=2e16;
const int magic=348;
const int MOD=998244353;
const double eps=1e-10;
const double pi=acos(-1);

struct fastio
{
	static const int S=1e6;
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
		for (;ch>32;ch=Getchar()) *++s=ch;
		*(s+1)='\0';
	}
	inline void flush() {fwrite(wbuf,1,wpos,stdout);fflush(stdout);wpos=0;}
	inline void Writechar(char ch)
	{
		if (wpos==S) flush();
		wbuf[wpos++]=ch;
	}
	template <class T> inline void Print(T x)
	{
		char s[20];int pt=0;
		if (x==0) s[++pt]='0'; else while (x) s[++pt]='0'+x%10,x/=10;
		while (pt) Writechar(s[pt--]);
		Writechar('\n');
	}
	inline void printstring(char *s)
	{
		int pt=1;
		while (s[pt]!='\0') Writechar(s[pt++]);
	}
}io;

const int MAXN=1e5;

int n,q;
vector<int> v[MAXN+48];
int depth[MAXN+48],anc[MAXN+48][21];
int val[MAXN+48];

inline void dfs(int cur,int father)
{
	int i,j;
	for (auto y : v[cur])
		if (y!=father)
		{
			depth[y]=depth[cur]+1;
			anc[y][0]=cur;
			for (j=1;j<=20;j++)
				anc[y][j]=anc[anc[y][j-1]][j-1];
			dfs(y,cur);
		}
}

inline int jump(int u,int dist)
{
	for (register int i=20;i>=0;i--)
		if (dist>=(1<<i)) u=anc[u][i],dist-=(1<<i);
	return u;
}

namespace LCT
{
	struct node
	{
		int ch[2],val,father;
		int flip,xsum;
	}tree[MAXN*2];int tot;
	inline void init()
	{
		for (register int i=1;i<=n;i++)
			tree[i].ch[0]=tree[i].ch[1]=tree[i].val=tree[i].father=tree[i].flip=tree[i].xsum=0;
	}
	inline void pushup(int cur)
	{
		if (!cur) return;
		tree[cur].xsum=(tree[cur].val+tree[tree[cur].ch[0]].xsum+tree[tree[cur].ch[1]].xsum);
	}
	inline void pushdown(int cur)
	{
		if (tree[cur].flip)
		{
			tree[tree[cur].ch[0]].flip^=1;
			tree[tree[cur].ch[1]].flip^=1;
			swap(tree[cur].ch[0],tree[cur].ch[1]);
			tree[cur].flip=0;
		}
	}
	inline bool isroot(int cur) {return !tree[cur].father || (tree[tree[cur].father].ch[0]!=cur && tree[tree[cur].father].ch[1]!=cur);}
	inline void rotate(int x)
	{
		int y=tree[x].father,z=tree[y].father;
		pushdown(y);pushdown(x);
		int k=(tree[y].ch[1]==x);
		if (!isroot(y)) tree[z].ch[tree[z].ch[1]==y]=x;
		tree[y].ch[k]=tree[x].ch[k^1];
		tree[x].ch[k^1]=y;
		tree[tree[y].ch[k]].father=y;tree[y].father=x;tree[x].father=z;
		pushup(y);pushup(x);
	}
	inline void splay(int x)
	{
		pushdown(x);
		while (!isroot(x))
		{
			int y=tree[x].father,z=tree[y].father;
			if (!isroot(y))
				((tree[y].ch[1]==x)^(tree[z].ch[1]==y))?rotate(x):rotate(y);
			rotate(x);
		}
	}
	inline void access(int cur)
	{
		for (int pre=0;cur;pre=cur,cur=tree[cur].father)
		{
			splay(cur);
			tree[cur].ch[1]=pre;
			pushup(cur);
		}
	}
	inline void makeroot(int x)
	{
		access(x);splay(x);
		tree[x].flip^=1;
	}
	inline int find(int x)
	{
		access(x);splay(x);
		while (tree[x].ch[0]) x=tree[x].ch[0];
		return x;
	}
	inline void link(int u,int v) // u is v's son
	{
		//makeroot(u);
		access(u);splay(u);
		tree[u].father=v;
	}
	inline void cut(int u)
	{
		//makeroot(u);
		access(u);splay(u);
		tree[tree[u].ch[0]].father=0;
		tree[u].ch[0]=0;pushup(u);
	}
	inline void update(int x,int val)
	{
		makeroot(x);
		tree[x].val=val;
		pushup(x);
	}
}

int main ()
{
	int ca,i,x,nv,op;io.Get(ca);
	while (ca--)
	{
		io.Get(n);LCT::init();
		for (i=1;i<=n;i++) v[i].clear();
		for (i=2;i<=n;i++)
		{
			io.Get(x);
			v[x].pb(i);v[i].pb(x);
		}
		depth[1]=0;dfs(1,-1);
		for (i=1;i<=n;i++) LCT::update(i,1);
		for (i=1;i<=n;i++)
		{
			io.Get(val[i]);
			if (depth[i]>=val[i])
			{
				int u=jump(i,val[i]);
				LCT::link(i,u);
			}
		}
		io.Get(q);
		while (q--)
		{
			io.Get(op);
			if (op==1)
			{
				io.Get(x);
				LCT::access(x);LCT::splay(x);
				io.Print(LCT::tree[x].xsum);
			}
			else
			{
				io.Get(x);io.Get(nv);
				if (depth[x]>=val[x])
					LCT::cut(x);
				val[x]=nv;
				if (depth[x]>=val[x])
				{
					int u=jump(x,val[x]);
					LCT::link(x,u);
				}
			}
		}
	}
	io.flush();return 0;
}
