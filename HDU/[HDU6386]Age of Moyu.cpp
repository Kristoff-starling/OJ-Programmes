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
		if (x==0) s[++pt]='0';
		else
		{
			if (x<0) Writechar('-'),x=-x;
			while (x) s[++pt]='0'+x%10,x/=10;
		}
		while (pt) Writechar(s[pt--]);
		Writechar('\n');
	}
	inline void printstring(char *s)
	{
		int pt=1;
		while (s[pt]!='\0') Writechar(s[pt++]);
	}
}io;

const int MAXN=2e5;

int n,e;

namespace DSU
{
	int pre[MAXN+48];
	inline void init() {for (register int i=1;i<=e;i++) pre[i]=i;}
	inline int find_anc(int x) {if (pre[x]!=x) pre[x]=find_anc(pre[x]);return pre[x];}
	inline void update(int x,int y) {x=find_anc(x);y=find_anc(y);pre[x]=y;}
}

struct Edge
{
	int u,v,type;
	inline void input () {scanf("%d%d%d",&u,&v,&type);}
}edge[MAXN*5+48];

vector<int> v[MAXN*5+48];
inline bool cmp(int x,int y)
{
	return edge[x].type<edge[y].type;
}

vector<int> vv[MAXN*5+48];

inline void Clear()
{
	for (register int i=1;i<=n;i++) v[i].clear();
	for (register int i=1;i<=e+n;i++) vv[i].clear();
}

int q[MAXN*5+48],head,tail;
int dist[MAXN*5+48];

int main ()
{
	int i,j;
	while (scanf("%d%d",&n,&e)!=EOF)
	{
		Clear();
		for (i=1;i<=e;i++) edge[i].input(),v[edge[i].u].pb(i),v[edge[i].v].pb(i);
		DSU::init();
		for (i=1;i<=n;i++)
		{
			sort(v[i].begin(),v[i].end(),cmp);
			for (j=0;j<int(v[i].size())-1;j++)
				if (edge[v[i][j]].type==edge[v[i][j+1]].type)
					DSU::update(v[i][j],v[i][j+1]);
		}
		for (i=1;i<=n;i++)
			for (j=0;j<int(v[i].size());j++)
			{
				vv[DSU::find_anc(v[i][j])].pb(e+i);
				vv[e+i].pb(DSU::find_anc(v[i][j]));
			}
		for (i=1;i<=e+n;i++) dist[i]=INF;
		head=1;tail=1;q[1]=e+1;dist[e+1]=0;
		while (head<=tail)
		{
			int cur=q[head++];
			for (i=0;i<int(vv[cur].size());i++)
				if (dist[cur]+1<dist[vv[cur][i]])
				{
					dist[vv[cur][i]]=dist[cur]+1;
					q[++tail]=vv[cur][i];
				}
		}
		int ans=dist[e+n];
		if (ans>=INF) printf("-1\n"); else printf("%d\n",ans/2);
	}
	return 0;
}
