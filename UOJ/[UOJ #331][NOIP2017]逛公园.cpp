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
inline int quick_pow(int x,int y) {int res=1;while (y) {if (y&1) res=1ll*res*x%MOD;x=1ll*x*x%MOD;y>>=1;}return res;}
inline int quick_pow(int x,int y,int MO) {int res=1;while (y) {if (y&1) res=1ll*res*x%MO;x=1ll*x*x%MO;y>>=1;}return res;}

const int MAXN=1e5;

int n,m,k,p;

int dp[MAXN+48][58];

vector<Pair> v[MAXN+48],vv[MAXN+48];
vector<int> vzero[MAXN+48];
bool inzero[MAXN+48];

int dist1[MAXN+48],dist2[MAXN+48];
priority_queue<Pair> q;
inline void init_dist()
{
	for (register int i=1;i<=n;i++) dist1[i]=INF;
	dist1[1]=0;q.push(mp(0,1));
	while (!q.empty())
	{
		int dd=-q.top().x,cur=q.top().y;q.pop();
		if (dd>dist1[cur]) continue;
		for (register int i=0;i<int(v[cur].size());i++)
		{
			register int y=v[cur][i].x;
			if (dist1[cur]+v[cur][i].y<dist1[y])
			{
				dist1[y]=dist1[cur]+v[cur][i].y;
				q.push(mp(-dist1[y],y));
			}
		}
	}
	for (register int i=1;i<=n;i++) dist2[i]=INF;
	dist2[n]=0;q.push(mp(0,n));
	while (!q.empty())
	{
		int dd=-q.top().x,cur=q.top().y;q.pop();
		if (dd>dist2[cur]) continue;
		for (register int i=0;i<int(vv[cur].size());i++)
		{
			register int y=vv[cur][i].x;
			if (dist2[cur]+vv[cur][i].y<dist2[y])
			{
				dist2[y]=dist2[cur]+vv[cur][i].y;
				q.push(mp(-dist2[y],y));
			}
		}
	}
}

int dlist[MAXN+48],tot;

int dfn[MAXN+48],low[MAXN+48];bool visited[MAXN+48];int ind;
int sta[MAXN+48],stot;
bool superf;

inline void tarjan(int cur)
{
	dfn[cur]=low[cur]=++ind;
	sta[++stot]=cur;visited[cur]=true;
	for (register int i=0;i<int(vzero[cur].size());i++)
	{
		register int y=vzero[cur][i];
		if (!dfn[y])
		{
			tarjan(y);
			check_min(low[cur],low[y]);
		}
		else if (visited[y]) check_min(low[cur],low[y]);
	}
	if (dfn[cur]==low[cur])
	{
		int cnt=0,v1,v2,md=INF;
		do
		{
			v2=v1;v1=sta[stot--];
			visited[v1]=false;
			md=min(md,dist1[v1]+dist2[v1]);
			cnt++;
			if (cnt>=2) inzero[v2]=true,inzero[v1]=true;
		}
		while (v1!=cur);
		if (cnt>1 && md<=dist1[n]+k) superf=true;
	}
}

inline bool check_INF()
{
	memset(dfn,0,sizeof(dfn));memset(visited,false,sizeof(visited));
	superf=false;stot=0;ind=0;
	for (register int i=1;i<=n;i++)
		if (!dfn[i]) tarjan(i);
	return superf;
}

vector<int> medge[MAXN+48];int cnt[MAXN+48];
int head,tail,qq[MAXN+48];
inline void getorder()
{
	memset(cnt,0,sizeof(cnt));
	for (register int i=1;i<=n;i++)
		if (!inzero[i])
			for (register int j=0;j<int(v[i].size());j++)
			{
				register int y=v[i][j].x;
				if (!inzero[y])
					if (dist2[y]+v[i][j].y==dist2[i])
					// if (dist1[i]+v[i][j].y==dist1[y])
						medge[i].pb(y),cnt[y]++;
			}
	head=1;tail=0;
	for (register int i=1;i<=n;i++)
		if (!inzero[i] && !cnt[i]) qq[++tail]=i;
	tot=0;
	while (head<=tail)
	{
		register int cur=qq[head++];dlist[++tot]=cur;
		for (register int i=0;i<int(medge[cur].size());i++)
		{
			register int y=medge[cur][i];
			cnt[y]--;if (!cnt[y]) qq[++tail]=y;
		}
	}
}

inline void Clear()
{
	for (register int i=1;i<=n;i++) v[i].clear(),vv[i].clear(),vzero[i].clear(),medge[i].clear();
	memset(inzero,false,sizeof(inzero));
	memset(dp,0,sizeof(dp));
}

int main ()
{
#ifdef LOCAL
	double TIME=clock();
	freopen ("a.in","r",stdin);
	freopen ("a.out","w",stdout);
	cerr<<"Running..."<<endl;
#endif
	int ca;io.Get(ca);int x,y,c;
	while (ca--)
	{
		io.Get(n);io.Get(m);io.Get(k);io.Get(p);
		Clear();
		for (register int i=1;i<=m;i++)
		{
			io.Get(x);io.Get(y);io.Get(c);
			v[x].pb(mp(y,c));vv[y].pb(mp(x,c));
			if (!c) vzero[x].pb(y);
		}
		init_dist();
		if (dist1[n]>=INF) {io.Print(0,'\n');continue;}
		if (check_INF()) {io.Print(-1,'\n');continue;}
		getorder();
		dp[1][0]=1;
		for (register int d=0;d<=k;d++)
			for (register int i=1;i<=tot;i++)
			{
				register int cur=dlist[i];
				if (dp[cur][d])
					for (register int j=0;j<int(v[cur].size());j++)
					{
						if (inzero[v[cur][j].x]) continue;
						// int newd=dist1[cur]+d+v[cur][j].y-dist1[v[cur][j].x];
						int newd=dist1[n]+d-dist2[cur]+v[cur][j].y+dist2[v[cur][j].x]-dist1[n];
						if (newd<=k) Add(dp[v[cur][j].x][newd],dp[cur][d],p);
					}	
			}
		int ans=0;
		for (register int i=0;i<=k;i++) Add(ans,dp[n][i],p);
		io.Print(ans,'\n');
	}
	io.flush();
#ifdef LOCAL
	cerr<<"Exec Time: "<<(clock()-TIME)/CLOCKS_PER_SEC<<endl;
#endif
	return 0;
}
