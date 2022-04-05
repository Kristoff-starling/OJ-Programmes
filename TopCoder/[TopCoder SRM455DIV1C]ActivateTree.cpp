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

template <typename T> inline void check_min(T &x,T cmp) {x=min(x,cmp);}
template <typename T> inline void check_max(T &x,T cmp) {x=max(x,cmp);}

vector<int> v[48];
vector<int> valid[48][10];bool visited[48][10][48];
int ind[48][48],itot;Pair nd[48];
int cost[48];int fa[48][48],sz[48];
int dp[48][100048],need[48];
int d[48];

inline bool cmp_depth(int x,int y) {return d[x]<d[y];}

class ActivateTree
{
	int n,m;
	inline void dfs(int cur)
	{
		for (register int i=0;i<int(v[cur].size());i++) d[v[cur][i]]=d[cur]+1,dfs(v[cur][i]);
	}
	inline void doit_target(string s)
	{	
		int len=int(s.size()),pt;
		pt=0;bool f;int num,cnt=0;n=0;
		do
		{
			while (pt<=len-1 && s[pt]==' ') pt++;
			if (pt>=len) break;
			if (s[pt]=='-') f=false,num=0; else f=true,num=s[pt]-'0';
			pt++;cnt++;
			while (pt<=len-1 && isdigit(s[pt])) num=num*10+s[pt]-'0',pt++;
			if (!f) num=-num;
			num++;if (f) v[num].pb(cnt);
		}
		while (pt<=len-1);
		n=cnt;
		itot=0;
		for (register int i=1;i<=n;i++)
			for (register int j=0;j<int(v[i].size());j++)
				ind[i][v[i][j]]=++itot,nd[itot]=mp(i,v[i][j]);
		depth[1]=1;dfs(1);
	}
	int depth[10],cc[10];
	inline void doit_tree(string s,int id)
	{
		memset(depth,-1,sizeof(depth));
		int pt=0,len=int(s.size());int num,cnt=0;bool f;
		memset(cc,0,sizeof(cc));
		do
		{
			while (pt<=len-1 && s[pt]==' ') pt++;
			if (pt>=len) break;
			if (s[pt]=='-') f=false,num=0; else f=true,num=s[pt]-'0';
			pt++;cnt++;
			while (pt<=len-1 && isdigit(s[pt])) num=num*10+s[pt]-'0',pt++;
			if (!f) num=-num;
			num++;fa[id][cnt]=num;
		}
		while (pt<=len-1);
		sz[id]=cnt;
	}
	int pre[48];
	inline void init() {for (register int i=1;i<=n;i++) pre[i]=i;}
	inline int find_anc(int x) {if (pre[x]!=x) pre[x]=find_anc(pre[x]);return pre[x];}
	inline void update(int x,int y) {x=find_anc(x);y=find_anc(y);pre[x]=y;}
	vector<int> curnode;
	inline bool connected()
	{
		for (register int i=1;i<int(curnode.size());i++)
			if (find_anc(curnode[0])!=find_anc(curnode[i])) return false;
		return true;
	}
	inline bool isomorphic(int id,int Mask)
	{
		if (sz[id]!=int(curnode.size())) return false;
		int p[10],pp[10];
		for (register int i=1;i<=sz[id];i++) p[i]=i;
		do
		{
			for (register int i=1;i<=sz[id];i++) pp[p[i]]=curnode[i-1];
			bool f=true;
			for (register int i=1;i<=sz[id];i++)
				if (p[i]!=1)
				{
					int ff=fa[id][p[i]],ss=p[i];
					if (!(Mask&(1<<(ind[pp[ff]][pp[ss]]-1)))) {f=false;break;}
				}
			if (f) return true;
		}
		while (next_permutation(p+1,p+sz[id]+1));
		return false;
	}
	inline void doit_valid()
	{
		for (register int Mask=0;Mask<=(1<<(n-1))-1;Mask++)
		{
			init();curnode.clear();
			for (register int i=1;i<=n-1;i++)
				if (Mask&(1<<(i-1)))
				{
					update(nd[i].x,nd[i].y);
					curnode.pb(nd[i].x);curnode.pb(nd[i].y);
				}
			sort(curnode.begin(),curnode.end());
			curnode.resize(unique(curnode.begin(),curnode.end())-curnode.begin());
			sort(curnode.begin(),curnode.end(),cmp_depth);
			if (int(curnode.size())>5 || int(curnode.size())<2) continue;
			if (!connected()) continue;
			for (register int i=1;i<=m;i++)
				if (isomorphic(i,Mask))
					valid[curnode[0]][i].pb(Mask);
		}
	}
	int q[48],head,tail,seq[48];
	inline void bfs()
	{
		head=tail=1;q[1]=1;int pt=0;
		while (head<=tail)
		{
			register int x=q[head++];seq[++pt]=x;
			for (register int i=0;i<int(v[x].size());i++) q[++tail]=v[x][i];
		}
	}
	inline void dfs(int cur,int i,int curMask,int val)
	{
		if (cur==m+1) {check_min(dp[i][curMask],val);return;}
		dfs(cur+1,i,curMask,val);
		for (register int j=0;j<int(valid[seq[i]][cur].size());j++)
			dfs(cur+1,i,curMask^valid[seq[i]][cur][j],val+cost[cur]);
	}
	inline void Clear()
	{
		for (register int i=1;i<=48;i++) v[i].clear();
		itot=0;
		for (register int i=1;i<=48;i++)
			for (register int j=1;j<=7;j++)
				valid[i][j].clear();
	}
	public:
		inline int minCost(vector<string> trees,string target,vector<int> Cost)
		{
			Clear();
			doit_target(target);
			m=int(Cost.size());
			for (register int i=1;i<=m;i++) cost[i]=Cost[i-1];
			for (register int i=1;i<=m;i++) doit_tree(trees[i-1],i);
			doit_valid();
			bfs();
			need[1]=0;
			for (register int i=2;i<=n;i++)
			{
				need[i]=need[i-1];
				for (register int j=0;j<int(v[seq[i-1]].size());j++)
				{
					register int y=v[seq[i-1]][j];
					need[i]|=(1<<(ind[seq[i-1]][y]-1));
				}
			}
			int full=(1<<(n-1))-1;
			for (register int i=0;i<=n;i++)
				for (register int Mask=0;Mask<=full;Mask++)
					dp[i][Mask]=INF;
			dp[0][0]=0;
			for (register int i=1;i<=n;i++)
				for (register int Mask=0;Mask<=full;Mask++)
					if ((Mask&need[i])==need[i] && dp[i-1][Mask]<INF)
						dfs(1,i,Mask,dp[i-1][Mask]);
			if (dp[n][full]>=INF) return -1; else return dp[n][full];
		}
};

#ifdef LOCAL
int main ()
{
	freopen ("a.in","r",stdin);
	freopen ("a.out","w",stdout);
	int nn;vector<string> ss;string s;string tt;vector<int> cc;int x;
	ActivateTree A;
	while (cin>>nn)
	{
		// cerr<<nn<<"#"<<endl;
		ss.clear();cc.clear();
		getchar();
		for (register int i=1;i<=nn;i++) getline(cin,s),ss.pb(s);
		for (register int i=1;i<=nn;i++) cin>>x,cc.pb(x);
		getchar();
		getline(cin,tt);
		cout<<A.minCost(ss,tt,cc)<<endl;
	}
	return 0;
}
#endif
