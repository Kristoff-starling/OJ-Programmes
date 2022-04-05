#include <bits/stdc++.h>
using namespace std;

#define LL long long
#define LB long double
#define uint unsigned int
#define ull unsigned long long
#define x first
#define y second
#define Pair pair<int,int>
#define pii pair<double,double>
#define pLL pair<LL,LL>
#define pb push_back
#define pf push_front
#define mp make_pair
#define LOWBIT(x) ((x) & (-x))
// #define LOCAL true

const int INF=2e9;
const LL LINF=2e16;
const int magic=348;
const int MOD=998244353;
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

template<typename T> inline void check_max(T &x,T y) {x=(x>y?x:y);}
template<typename T> inline void check_min(T &x,T y) {x=(x<y?x:y);}

const int MAXN=3e5;

int n;
string A[MAXN+48],B[MAXN+48];
int p1[MAXN+48],p2[MAXN+48];

int N,s[MAXN+48];
set<Pair> S[MAXN+48];

struct Edge
{
	int x,y,c;
	Edge () {}
	inline Edge (int _x,int _y,int _c) {x=_x;y=_y;c=_c;}
	inline bool operator < (const Edge &other) const {return c>other.c;}
}edge[MAXN*10+48];int etot;

int lcp[MAXN+48],rnk[MAXN+48];
namespace SA
{
	int cnt[MAXN+48],fir[MAXN+48],sec[MAXN+48],tmp[MAXN+48],sa[MAXN+48];
	int maxind;
	inline bool compare_sa(int x,int y,int k)
	{
		if (fir[x]!=fir[y]) return fir[x]<fir[y];
		int tmp1=(x+k<=N)?fir[x+k]:(-1),tmp2=(y+k<=N)?fir[y+k]:(-1);
		return tmp1<tmp2;
	}
	inline void construct_sa(int s[],int ch)
	{
		maxind=ch;memset(cnt+1,0,maxind<<2);
		for (register int i=1;i<=N;i++) cnt[s[i]]++;
		for (register int i=1;i<=maxind;i++) cnt[i]+=cnt[i-1];
		for (register int i=N;i>=1;i--) sa[cnt[s[i]]--]=i;
		fir[sa[1]]=1;for (register int i=2;i<=N;i++) fir[sa[i]]=fir[sa[i-1]]+(s[sa[i]]!=s[sa[i-1]]);
		for (register int len=1;len<=N;len<<=1)
		{
			memset(cnt+1,0,maxind<<2);int tot=0;
			for (register int i=N-len+1;i<=N;i++) sec[++tot]=i;
			for (register int i=1;i<=N;i++) if (sa[i]>len) sec[++tot]=sa[i]-len;
			for (register int i=1;i<=tot;i++) cnt[fir[sec[i]]]++;
			for (register int i=1;i<=maxind;i++) cnt[i]+=cnt[i-1];
			for (register int i=N;i>=1;i--) sa[cnt[fir[sec[i]]]--]=sec[i];
			tmp[sa[1]]=1;for (register int i=2;i<=N;i++) tmp[sa[i]]=tmp[sa[i-1]]+compare_sa(sa[i-1],sa[i],len);
			memcpy(fir+1,tmp+1,N<<2);maxind=fir[sa[N]];if (maxind>=N) break;
		}
	}
	inline void construct_lcp()
	{
		int h=0;
		for (register int i=1;i<=N;i++) rnk[sa[i]]=i;
		for (register int i=1;i<=N;i++)
		{
			int j=sa[rnk[i]-1];
			if (h) h--;
			while (i+h<=N && j+h<=N && s[i+h]==s[j+h]) h++;
			lcp[rnk[i]-1]=h;
		}
	}
}

namespace DSU
{
	int pre[MAXN+48],rnk[MAXN+48];
	inline void init() {for (register int i=1;i<=n;i++) pre[i]=i,rnk[i]=1;}
	inline int find_anc(int x) {if (pre[x]!=x) pre[x]=find_anc(pre[x]);return pre[x];}
	inline bool issame(int x,int y) {return find_anc(x)==find_anc(y);}
	inline void update(int x,int y)
	{
		x=find_anc(x);y=find_anc(y);
		if (rnk[x]>rnk[y]) swap(x,y);
		pre[x]=y;rnk[y]++;
	}
}

int ST[MAXN+48][21],Log[MAXN+48];

inline void init_ST()
{
	for (register int i=1;i<=N-1;i++) ST[i][0]=lcp[i];
	Log[0]=Log[1]=0;for (register int i=2;i<=N;i++) Log[i]=Log[i>>1]+1;
	for (register int j=1;j<=20;j++)
		for (register int i=1;i<=N-1;i++)
		{
			ST[i][j]=ST[i][j-1];
			if (i+(1<<(j-1))<=N-1) check_min(ST[i][j],ST[i+(1<<(j-1))][j-1]);
		}
}

inline int query_ST(int left,int right)
{
	int k=right-left+1;
	return min(ST[left][Log[k]],ST[right-(1<<Log[k])+1][Log[k]]);
}

inline int query_lcp(int pos1,int pos2)
{
	if (pos1>pos2) swap(pos1,pos2);
	return query_ST(pos1,pos2-1);
}

inline void update(int val,int cind,int &maxn,int &maxind)
{
	if (val>maxn) maxn=val,maxind=cind;
}

int main ()
{
#ifdef LOCAL
	freopen ("a.in","r",stdin);
	freopen ("a.out","w",stdout);
#endif
	Get(n);
	for (register int i=1;i<=n;i++) cin>>A[i];
	for (register int i=1;i<=n;i++) cin>>B[i];
	int pt=0,ch=200;
	for (register int i=1;i<=n;i++)
	{
		for (register int j=int(B[i].size())-1;j>=0;j--) s[++pt]=B[i][j]; p1[i]=pt+1;
		for (register int j=0;j<=int(A[i].size())-1;j++) s[++pt]=A[i][j];
		s[++pt]=ch++;
		for (register int j=int(A[i].size())-1;j>=0;j--) s[++pt]=A[i][j]; p2[i]=pt+1;
		for (register int j=0;j<=int(B[i].size())-1;j++) s[++pt]=B[i][j];
		s[++pt]=ch++;
	}
	N=pt-1;SA::construct_sa(s,ch);SA::construct_lcp();init_ST();
	/*
	for (register int i=1;i<=n;i++)
		for (register int j=i+1;j<=n;j++)
			if (query_lcp(rnk[p1[i]],rnk[p2[j]])+query_lcp(rnk[p1[j]],rnk[p2[i]])>0) cout<<i<<' '<<j<<endl;
	*/
	for (register int i=1;i<=n;i++)
	{
		int len=int(A[i].size());
		for (register int j=0;j<=len;j++) S[j].insert(mp(rnk[p2[i]-j],i));
	}
	for (register int i=1;i<=n;i++)
	{
		int len=int(B[i].size()),maxn1=-1,mind1=0,maxn2=-1,mind2=0;
		for (register int j=0;j<=len;j++)
		{
			int cr=rnk[p1[i]-j];
			S[j].erase(mp(rnk[p2[i]-j],i));
			set<Pair>::iterator iter=S[j].lower_bound(mp(cr,0));
			if (iter!=S[j].end())
			{
				int val=query_lcp(cr,iter->x);
				if (val>=j) update(val,iter->y,maxn1,mind1);
			}
			if (iter!=S[j].begin())
			{
				--iter;int val=query_lcp(cr,iter->x);
				if (val>=j) update(val,iter->y,maxn2,mind2);
			}
			S[j].insert(mp(rnk[p2[i]-j],i));
		}
		edge[++etot]=Edge(i,mind1,maxn1);
		edge[++etot]=Edge(i,mind2,maxn2);
	}
	for (register int i=0;i<=N;i++) S[i].clear();
	for (register int i=1;i<=n;i++)
	{
		int len=int(B[i].size());
		for (register int j=0;j<=len;j++) S[j].insert(mp(rnk[p1[i]-j],i));
	}
	for (register int i=1;i<=n;i++)
	{
		int len=int(A[i].size()),maxn1=-1,mind1=0,maxn2=-1,mind2=0;
		for (register int j=0;j<=len;j++)
		{
			int cr=rnk[p2[i]-j];
			S[j].erase(mp(rnk[p1[i]-j],i));
			set<Pair>::iterator iter=S[j].lower_bound(mp(cr,0));
			if (iter!=S[j].end())
			{
				int val=query_lcp(cr,iter->x);
				if (val>=j) update(val,iter->y,maxn1,mind1);
			}
			if (iter!=S[j].begin())
			{
				--iter;int val=query_lcp(cr,iter->x);
				if (val>=j) update(val,iter->y,maxn2,mind2);
			}
			S[j].insert(mp(rnk[p1[i]-j],i));
		}
		edge[++etot]=Edge(i,mind1,maxn1);
		edge[++etot]=Edge(i,mind2,maxn2);
	}
	sort(edge+1,edge+etot+1);DSU::init();int cnt=0,ans=0;
	for (register int i=1;i<=etot && cnt<n-1;i++)
	{
		int x=edge[i].x,y=edge[i].y;
		if (DSU::issame(x,y)) continue;
		cnt++;ans+=edge[i].c;DSU::update(x,y);
	}
	printf("%d\n",ans);
	return 0;
}
