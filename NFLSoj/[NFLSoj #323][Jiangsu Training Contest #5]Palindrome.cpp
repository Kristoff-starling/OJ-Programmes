#include <bits/stdc++.h>
using namespace std;

#define LL long long
#define LB long double
#define ull unsigned long long
#define uint unsigned int
#define x first
#define y second
#define Pair pair<int,int>
#define pLL pair<LL,LL>
#define pii pair<double,double>
#define pb push_back
#define pf push_front
#define mp make_pair
#define LOWBIT(x) x & (-x)

const int INF=2e9;
const LL LINF=2e16;
const int magic=348;
const int MOD=1e9+7;
const double pi=acos(-1);
const double eps=1e-10;

template<typename T> inline void check_max(T &x,T y) {x=(x>y?x:y);}
template<typename T> inline void check_min(T &x,T y) {x=(x<y?x:y);}
template<typename T> inline T gcd(T x,T y) {return (!y)?x:gcd(y,x%y);}
inline int add(int x) {if (x>=MOD) x-=MOD;return x;}
inline int sub(int x) {if (x<0) x+=MOD;return x;}
inline void Add(int &x,int y) {x=add(x+y);}
inline void Sub(int &x,int y) {x=sub(x-y);}

inline int quick_pow(int x,int y)
{
	int res=1;
	while (y)
	{
		if (y&1) res=1ll*res*x%MOD;
		x=1ll*x*x%MOD;y>>=1;
	}
	return res;
}

int n,m;
string s1[1048],s2[1048];
string ins[]={"0","1"};

struct AC_Automaton
{
	struct node
	{
		bool danger;int nxt[2],fail;
		int fa,faedge;
		inline void clear() {danger=false;nxt[0]=nxt[1]=fail=0;}
	}trie[10048];int tot=0;
	inline int Create() {++tot;trie[tot].clear();return tot;}
	inline void init() {tot=0;Create();}
	inline void insert(string s)
	{
		int cur=1,len=int(s.size());
		for (register int i=0;i<len;i++)
		{
			int w=s[i]-'0';
			if (!trie[cur].nxt[w])
			{
				trie[cur].nxt[w]=Create();
				trie[tot].fa=cur;trie[tot].faedge=w;
			}
			cur=trie[cur].nxt[w];
		}
		trie[cur].danger=true;
	}
	int head,tail,q[2048];
	inline void construct_fail()
	{
		head=1;tail=1;q[1]=1;
		while (head<=tail)
		{
			int cur=q[head++];
			trie[cur].danger|=trie[trie[cur].fail].danger;
			for (register int i=0;i<=1;i++)
				if (trie[cur].nxt[i])
				{
					int tmp=trie[cur].fail;
					while (tmp && !trie[tmp].nxt[i]) tmp=trie[tmp].fail;
					trie[trie[cur].nxt[i]].fail=(tmp?trie[tmp].nxt[i]:1);
					q[++tail]=trie[cur].nxt[i];
				}
				else
					trie[cur].nxt[i]=(cur==1?1:trie[trie[cur].fail].nxt[i]);
		}
	}
	inline int go(int cur,int w) {return trie[cur].nxt[w];}
	inline void getstring(int cur,string &s)
	{
		while (cur!=1)
		{
			s+=ins[trie[cur].faedge];
			cur=trie[cur].fa;
		}
	}
	inline bool query(string s)
	{
		int cur=1,len=int(s.size());
		for (register int i=0;i<len;i++)
		{
			int w=s[i]-'0';cur=trie[cur].nxt[w];
			if (trie[cur].danger) return true;
		}
		return false;
	}
}t1,t2;

namespace Correct
{
	const int MAXN=300;
	int dp[2][1048][1048][2],N;bool inq[2][1048][1048][2];
	int ss1[1048],ss2[1048],tot1,tot2;
	queue<int> q;
	inline void solve()
	{
		N=n>>1;memset(dp,0,sizeof(dp));dp[0][1][1][0]=1;
		q.push(0);q.push(1);q.push(1);q.push(0);inq[0][1][1][0]=true;
		int cur=0,nxt=1;
		int last=0;
		while (!q.empty())
		{
			int i=q.front();q.pop();int pt1=q.front();q.pop();int pt2=q.front();q.pop();int sta=q.front();q.pop();
			if (i!=last) cur^=1,nxt^=1,last=i;
			if (i==N) break;
			inq[cur][pt1][pt2][sta]=false;
			for (register int nc=0;nc<=1;nc++)
			{
				int to1=t1.go(pt1,nc),to2=t2.go(pt2,nc),tosta=sta;
				if (t1.trie[to1].danger) tosta++,to1=1;
				if (t2.trie[to2].danger) tosta++,to2=1;
				if (tosta<=1)
				{
					Add(dp[nxt][to1][to2][tosta],dp[cur][pt1][pt2][sta]);
					if (!inq[nxt][to1][to2][tosta])
					{
						inq[nxt][to1][to2][tosta]=true;
						q.push(i+1);q.push(to1);q.push(to2);q.push(tosta);
					}
				}
			}
			dp[cur][pt1][pt2][sta]=0;
		}
		int ans=0;
		string S1,S2;
		for (register int pt1=1;pt1<=t1.tot;pt1++)
			if (!t1.trie[pt1].danger)
				for (register int pt2=1;pt2<=t2.tot;pt2++)
					if (!t2.trie[pt2].danger)
					{
						//sta=0
						Add(ans,1ll*dp[cur][pt1][pt2][0]*((n&1)?2:1)%MOD);
						//sta=1
						S1="";S2="";
						t1.getstring(pt1,S1);t2.getstring(pt2,S2);
						for (register int i=0,j=int(S1.size())-1;i<j;i++,j--) swap(S1[i],S1[j]);
						if (n&1)
						{
							for (register int mid=0;mid<=1;mid++)
							{
								string ss=S1+ins[mid]+S2;
								if (!t1.query(ss)) Add(ans,dp[cur][pt1][pt2][1]);
							}
						}
						else
						{
							S1+=S2;
							if (!t1.query(S1)) Add(ans,dp[cur][pt1][pt2][1]);
						}
					}
		printf("%d\n",ans);
	}
}

int main ()
{
	cin>>n>>m;
	if (m==0) {printf("%d\n",quick_pow(2,(n+1)/2));return 0;}
	for (register int i=1;i<=m;i++)
	{
		cin>>s1[i];s2[i]=s1[i];
		for (register int pt1=0,pt2=int(s2[i].size())-1;pt1<=pt2;pt1++,pt2--) swap(s2[i][pt1],s2[i][pt2]);
	}
	t1.init();t2.init();
	for (register int i=1;i<=m;i++) t1.insert(s1[i]),t2.insert(s2[i]);
	t1.construct_fail();t2.construct_fail();
	Correct::solve();return 0;
}
