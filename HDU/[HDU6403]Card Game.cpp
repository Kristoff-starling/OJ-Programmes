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

const int MAXN=2e5;

inline int add(int x) {if (x>=MOD) x-=MOD;return x;}
inline int sub(int x) {if (x<0) x+=MOD;return x;}

int n;
vector<int> v[MAXN+48];

bool incir[MAXN+48];

struct Edge
{
	int u,v;
	inline void input() {io.Get(u);io.Get(v);}
}edge[MAXN+48];

inline int getanother(int id,int u)
{
	return edge[id].u==u?edge[id].v:edge[id].u;
}

int cid,cnt;
int depth[MAXN+48],fa[MAXN+48],vis[MAXN+48],exist[MAXN+48];
//fa didn't store his father but the id of the edge to his father

inline void dfs(int cur,int father)
{
	fa[cur]=father;int i,id,y;
	for (i=0;i<int(v[cur].size());i++)
	{
		id=v[cur][i];y=getanother(id,cur);
		if (!depth[y])
		{
			depth[y]=depth[cur]+1;
			dfs(y,id);
		}
		else if (id!=father && depth[y]<=depth[cur])
		{
			cnt++;
			cid=id;
		}
	}
}

int minn,minmethod;

namespace cycle
{
	int cirlist[MAXN+48],ctot;
	inline void dfs(int cur,int father)
	{
		int i,id,y;
		for (i=0;i<int(v[cur].size());i++)
		{
			id=v[cur][i];y=getanother(id,cur);
			if (id!=father && !incir[y])
			{
				if (cur==edge[id].u) minn++;
				dfs(y,id);
			}
		}
	}
	inline void solve()
	{
		ctot=0;int u=edge[cid].u,v=edge[cid].v;
		if (depth[u]<depth[v]) swap(u,v);
		for (register int cur=u;cur!=v;cur=getanother(fa[cur],cur)) cirlist[++ctot]=cur,incir[cur]=true;
		cirlist[++ctot]=v;incir[v]=true;
		for (register int i=1;i<=ctot;i++) dfs(cirlist[i],-1);
		if (ctot==1) return;
		int cnt1=0,cnt2=0;
		//from down to up
		for (register int i=1;i<=ctot-1;i++)
			if (edge[fa[cirlist[i]]].u==cirlist[i]) cnt1++;
		if (edge[cid].u==cirlist[ctot]) cnt1++;
		//from up to down
		for (register int i=1;i<=ctot-1;i++)
			if (edge[fa[cirlist[i]]].v==cirlist[i]) cnt2++;
		if (edge[cid].u==cirlist[1]) cnt2++;
		minn+=min(cnt1,cnt2);
		if (cnt1==cnt2) minmethod=add(minmethod+minmethod);
	}
}

namespace tree
{
	int Minn,Cnt,ans;
	inline void update(int curans)
	{
		if (curans<Minn) Minn=curans,Cnt=1;
		else if (curans==Minn) Cnt++;
	}
	inline void dfs(int cur,int father)
	{
		int i,id,y;
		for (i=0;i<int(v[cur].size());i++)
		{
			id=v[cur][i];y=getanother(id,cur);
			if (id!=father)
			{
				if (edge[id].u==cur) ans++;
				dfs(y,id);
			}
		}
	}
	inline void Dfs(int cur,int father)
	{
		update(ans);int i,id,y,delta;
		for (i=0;i<int(v[cur].size());i++)
		{
			id=v[cur][i];y=getanother(id,cur);
			if (id==father) continue;
			if (edge[id].u==cur) delta=1; else delta=-1;
			ans-=delta;Dfs(y,id);
			ans+=delta;
		}
	}
	inline void solve(int root)
	{
		Minn=INF;Cnt=0;
		ans=0;dfs(root,-1);
		Dfs(root,-1);
		minn+=Minn;minmethod=(1ll*minmethod*Cnt)%MOD;
	}
}

inline void Clear()
{
	for (register int i=1;i<=n*2;i++) depth[i]=0,v[i].clear(),incir[i]=false,vis[i]=false;
	minn=0;minmethod=1;
}

int main ()
{
	int ca;io.Get(ca);int i;
	while (ca--)
	{
		io.Get(n);Clear();
		bool f=true;
		for (i=1;i<=n;i++)
		{
			edge[i].input();
			if (edge[i].u!=edge[i].v) v[edge[i].u].pb(i),v[edge[i].v].pb(i); else v[edge[i].u].pb(i);
			exist[edge[i].u]=true;exist[edge[i].v]=true;
			if (edge[i].u==edge[i].v)
			{
				if (vis[edge[i].u]) f=false;
				vis[edge[i].u]=true;
			}
		}
		if (!f) {io.Print(-1,' ');io.Print(-1,'\n');continue;}
		for (i=1;i<=n*2;i++)
			if (!depth[i] && exist[i])
			{
				cnt=0;cid=0;
				depth[i]=1;dfs(i,-1);
				if (cnt>1) {f=false;break;}
				if (cnt==1) cycle::solve(); else tree::solve(i);
			}
		if (!f) {io.Print(-1,' ');io.Print(-1,'\n');continue;}
		io.Print(minn,' ');io.Print(minmethod,'\n');
	}
	io.flush();return 0;
}
