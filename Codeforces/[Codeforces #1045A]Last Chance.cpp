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

template <typename T> inline void check_max(T &x,T cmp) {x=max(x,cmp);}
template <typename T> inline void check_min(T &x,T cmp) {x=min(x,cmp);}
template <typename T> inline T myabs(T x) {return x>=0?x:-x;}

const int MAXN=5e4;
const int MAXM=1e6;

int n,m,t,ind;
int toid[MAXN+48],tonode[MAXN+48];
int L[MAXN+48],R[MAXN+48],type[MAXN+48];
bool visited[MAXN+48],chosen[MAXN+48];
int head[MAXM+48],cur[MAXM+48],to[MAXM+48],nxt[MAXM+48],f[MAXM+48],tot=1;
vector<Pair> ans;
int seq[MAXN+48],stot;
priority_queue<Pair> q;

inline bool cmp_l(int x,int y) {return L[x]<L[y];}
inline bool cmp_x(Pair x,Pair y) {return x.y<y.y;}

namespace flow
{
	inline void addedge(int s,int t,int cap)
	{
		to[++tot]=t;nxt[tot]=head[s];head[s]=tot;f[tot]=cap;
		to[++tot]=s;nxt[tot]=head[t];head[t]=tot;f[tot]=0;
	}
	int q[MAXM+48],Head,Tail,depth[MAXM+48];
	inline bool bfs()
	{
		for (register int i=0;i<=t;i++) depth[i]=-1;
		depth[0]=0;q[1]=0;Head=Tail=1;
		while (Head<=Tail)
		{
			register int x=q[Head++];
			for (register int i=head[x];i;i=nxt[i])
			{
				register int y=to[i];
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
		if (!maxf || x==t) return maxf;
		int minf,now,ans=0;
		for (register int &i=cur[x];i;i=nxt[i])
		{
			register int y=to[i];
			if (depth[y]==depth[x]+1 && f[i])
			{
				minf=min(maxf-ans,f[i]);
				now=dfs(y,minf);
				f[i]-=now;f[i^1]+=now;ans+=now;
				if (ans>=maxf) break;
			}
		}
		if (!ans) depth[x]=-1;
		return ans;
	}
	inline int dinic()
	{
		int ans=0;
		while (bfs())
		{
			for (register int i=0;i<=t;i++) cur[i]=head[i];
			ans+=dfs(0,INF);
		}
		return ans;
	}
}

namespace SegmentTree
{
	inline void build(int cur,int left,int right)
	{
		if (left==right)
		{
			++ind;
			toid[cur]=ind;tonode[ind]=cur;
			flow::addedge(ind,n+left,INF);
			return;
		}
		int mid=(left+right)>>1;
		build(cur<<1,left,mid);build(cur<<1|1,mid+1,right);
		++ind;toid[cur]=ind;tonode[ind]=cur;
		flow::addedge(ind,toid[cur<<1],INF);
		flow::addedge(ind,toid[cur<<1|1],INF);
	}
	inline void update(int cur,int left,int right,int l,int r,int id)
	{
		if (left<=l && r<=right)
		{
			flow::addedge(id,toid[cur],1);
			return;
		}
		int mid=(l+r)>>1;
		if (left<=mid) update(cur<<1,left,right,l,mid,id);
		if (mid+1<=right) update(cur<<1|1,left,right,mid+1,r,id);
	}
}

int main ()
{
#ifdef LOCAL
	double TIME=clock();
	freopen ("a.in","r",stdin);
	freopen ("a.out","w",stdout);
	cerr<<"Running..."<<endl;
#endif
	io.Get(n);io.Get(m);ind=n+m;
	SegmentTree::build(1,1,m);int num,x;
	for (register int i=1;i<=n;i++)
	{
		io.Get(type[i]);
		switch(type[i])
		{
			case 0:
			{
				io.Get(num);
				for (register int j=1;j<=num;j++) io.Get(x),flow::addedge(i,n+x,1);
				break;
			}
			case 1:
			{
				io.Get(L[i]);io.Get(R[i]);
				SegmentTree::update(1,L[i],R[i],1,m,i);
				break;
			}
			case 2:
			{
				for (register int j=1;j<=3;j++) io.Get(x),flow::addedge(i,n+x,1);
				break;
			}
		}
	}
	t=ind+1;
	for (register int i=1;i<=n;i++) if (type[i]!=2) flow::addedge(0,i,1); else flow::addedge(0,i,2);
	for (register int i=1;i<=m;i++) flow::addedge(n+i,t,1);
	io.Print(flow::dinic(),'\n');
	for (register int i=1;i<=m;i++)
		for (register int j=head[n+i];j;j=nxt[j])
			if (to[j]==t)
			{
				if (!f[j]) chosen[i]=true;
				break;
			}
	for (register int i=head[0];i;i=nxt[i])
	{
		register int y=to[i],cnt=0;
		if (type[y]==2 && f[i]<2)
		{
			for (register int j=head[y];j && cnt<2;j=nxt[j])
				if (n+1<=to[j] && to[j]<=n+m && !f[j])
				{
					cnt++;
					visited[to[j]-n]=true;
					ans.pb(mp(y,to[j]-n));
				}
			if (cnt<2)
				for (register int j=head[y];j && cnt<2;j=nxt[j])
					if (n+1<=to[j] && to[j]<=n+m && !visited[to[j]-n] && chosen[to[j]-n])
					{
						cnt++;
						visited[to[j]-n]=true;
						ans.pb(mp(y,to[j]-n));
					}
		}
	}
	for (register int i=head[0];i;i=nxt[i])
	{
		register int y=to[i];
		if (type[y]==0 && !f[i])
			for (register int j=head[y];j;j=nxt[j])
				if (n+1<=to[j] && to[j]<=n+m && !f[j])
				{
					if (!visited[to[j]-n]) visited[to[j]-n]=true,ans.pb(mp(y,to[j]-n));
					break;
				}
	}
	for (register int i=head[0];i;i=nxt[i])
	{
		register int y=to[i];
		if (type[y]==1 && !f[i]) seq[++stot]=y;
	}
	sort(seq+1,seq+stot+1,cmp_l);int pt=1;
	for (register int i=1;i<=m;i++)
		if (chosen[i] && !visited[i])
		{
			while (pt<=stot && L[seq[pt]]<=i) q.push(mp(-R[seq[pt]],seq[pt])),pt++;
			while (!q.empty() && -q.top().x<i) q.pop();
			assert(!q.empty());
			ans.pb(mp(q.top().y,i));q.pop();
		}
	sort(ans.begin(),ans.end(),cmp_x);
	for (auto y : ans) io.Print(y.x,' '),io.Print(y.y,'\n');
	io.flush();
#ifdef LOCAL	
	cerr<<"Exec Time: "<<(clock()-TIME)/CLOCKS_PER_SEC<<endl;
#endif
	return 0;
}