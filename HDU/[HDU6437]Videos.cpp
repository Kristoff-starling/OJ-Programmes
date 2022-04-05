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

const int INF=1e8;
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

const int MAXN=10000;

int n,m,k,w;

namespace flow
{
	int head[200048],nxt[200048],to[200048],f[200048],w[200048],tot=1,t;
	inline void addedge(int s,int t,int l,int cost)
	{
		to[++tot]=t;nxt[tot]=head[s];head[s]=tot;f[tot]=l;w[tot]=cost;
		to[++tot]=s;nxt[tot]=head[t];head[t]=tot;f[tot]=0;w[tot]=-cost;
	}
	int prevv[200048],preve[200048];
	int h[200048];
	priority_queue<Pair> q;int dist[200048];
	inline void init()
	{
		t=n*2+2;
		for (register int i=0;i<=t;i++) head[i]=0;
		for (register int i=0;i<=t;i++) h[i]=0;
		tot=1;
	}
	bool dijkstra()
	{
		int i,x,y,dd;
		for (i=0;i<=t;i++) dist[i]=INF;
		dist[t]=0;q.push(mp(0,t));
		while (!q.empty())
		{
			x=q.top().y;dd=-q.top().x;q.pop();
			if (dd>dist[x]) continue;
			for (i=head[x];i;i=nxt[i])
			{
				y=to[i];
				if (f[i] && dist[x]+w[i]+h[x]-h[y]<dist[y])
				{
					dist[y]=dist[x]+w[i]+h[x]-h[y];
					prevv[y]=x;preve[y]=i;
					q.push(mp(-dist[y],y));
				}
			}
		}
		if (dist[n*2+1]>=INF) return false; else return true;
	}
	int qq[MAXN+48],Head,Tail;bool inq[MAXN+48];
	bool spfa()
	{
		int i,x,y;
		for (i=0;i<=t;i++) dist[i]=INF;
		dist[t]=0;qq[Head=Tail=1]=t;inq[t]=true;
		while (Head<=Tail)
		{
			x=qq[Head++];inq[x]=false;
			for (i=head[x];i;i=nxt[i])
			{
				y=to[i];
				if (f[i] && dist[x]+w[i]<dist[y])
				{
					dist[y]=dist[x]+w[i];
					prevv[y]=x;preve[y]=i;
					if (!inq[y]) inq[y]=true,qq[++Tail]=y;
				}
			}
		}
		if (dist[n*2+1]>=INF) return false; else return true;
	}
	inline int min_cost_flow()
	{
		int i,u,res,minf;
		for (i=0;i<=t;i++) h[i]+=dist[i];
		minf=INF;
		for (u=n*2+1;u!=t;u=prevv[u]) minf=min(minf,f[preve[u]]);
		res=minf*h[n*2+1];
		for (u=n*2+1;u!=t;u=prevv[u])
		{
			f[preve[u]]-=minf;
			f[preve[u]^1]+=minf;
		}
		return res;
	}
	inline int ek()
	{
		int ans=0;
		if (spfa())
		{
			do
			{
				ans+=min_cost_flow();
			}
			while (dijkstra());
		}
		return -ans;
	}
}

int main ()
{
	int i,ca,s,t,v,op;io.Get(ca);
	while (ca--)
	{
		io.Get(n);io.Get(m);io.Get(k);io.Get(w);
		flow::init();
		for (i=1;i<=n*2;i++) flow::addedge(0,i,INF,0),flow::addedge(i,n*2+1,INF,0);
		flow::addedge(n*2+2,0,k,0);
		for (i=1;i<=n;i++) flow::addedge(i,n+i,INF,w),flow::addedge(n+i,i,INF,w);
		for (i=1;i<=n-1;i++) flow::addedge(i,i+1,INF,0),flow::addedge(n+i,n+i+1,INF,0);
		for (i=1;i<=m;i++)
		{
			io.Get(s);io.Get(t);io.Get(v);io.Get(op);
			flow::addedge(op*n+s,(op^1)*n+t,1,-v);
		}
		io.Print(flow::ek(),'\n');
	}
	io.flush();return 0;
}
