#include <bits/stdc++.h>
using namespace std;

#define LL long long
#define LB long double
#define ull unsigned long long
#define pf push_front
#define pb push_back
#define mp make_pair
#define x first
#define y second
#define Pair pair<int,int>
#define pLL pair<LL,LL>
#define pii pair<double,double>
#define LOWBIT(x) x & (-x)

const int MOD=998244353;
const int INF=2e9;
const LL LINF=2e16;
const int magic=348;
const double eps=1e-10;
const double pi=acos(-1);

inline int getint()
{
	bool f;char ch;int res;
	while (!isdigit(ch=getchar()) && ch!='-') {}
	if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
	while (isdigit(ch=getchar())) res=res*10+ch-'0';
	return f?res:-res;
}

const int MAXN=1e5;

int n,d,m;
char s[MAXN+48];
char chosen[10];int pos[10],tot=0;

struct Rule
{
	int ind1,ind2;
	char c1,c2;
	inline void input() {cin>>ind1>>c1>>ind2>>c2;}
}a[MAXN+48];

vector<int> v[MAXN*4+48];
vector<int> vv[MAXN*4+48];int deg[MAXN*4+48];

inline int getind(int num,char choice)
{
	int res=(num-1)*2;
	if (s[num]=='a') return choice=='B'?res+1:res+2;
	if (s[num]=='b') return choice=='A'?res+1:res+2;
	if (s[num]=='c') return choice=='A'?res+1:res+2;
}

inline int getnum(int Ind) {return (Ind+1)/2;}
inline int getchoice(int Ind) {return Ind%2==1?1:2;}

inline int getanother(int pos,char choice)
{
	char another;
	if (s[pos]=='a') another=(choice=='B'?'C':'B');
	if (s[pos]=='b') another=(choice=='A'?'C':'A');
	if (s[pos]=='c') another=(choice=='A'?'B':'A');
	return getind(pos,another);
}

inline bool isvalid(int pos,char choice) {return s[pos]-choice!=32;}

inline void add_ban(int pos,char choice)
{
	v[getanother(pos,choice)].pb(getind(pos,choice));
}

stack<int> sta;int bel[MAXN*4],dfn[MAXN*4],low[MAXN*4];bool visited[MAXN*4];
vector<int> member[MAXN*4+48];
int Index,ind;
int seq[MAXN*4+48],stot=0;
bool taboo[MAXN*4+48];
vector<int> finalchoice;

int que[MAXN*4+48],head,tail;

inline void tarjan(int cur)
{
	int i,y;
	visited[cur]=true;sta.push(cur);dfn[cur]=low[cur]=++Index;
	for (i=0;i<int(v[cur].size());i++)
	{
		y=v[cur][i];
		if (!dfn[y])
		{
			tarjan(y);
			low[cur]=min(low[cur],low[y]);
		}
		else if (visited[y]) low[cur]=min(low[cur],dfn[y]);
	}
	if (dfn[cur]==low[cur])
	{
		int vv;++ind;
		do
		{
			vv=sta.top();sta.pop();
			visited[vv]=false;
			bel[vv]=ind;
			member[ind].pb(vv);
		}
		while (vv!=cur);
	}
}

inline int solve ()
{
	int i,j,cur,y;
	for (i=1;i<=d;i++) s[pos[i]]=chosen[i];
	for (i=1;i<=n*2;i++) v[i].clear();
	for (i=1;i<=m;i++)
	{
		if (a[i].ind1==a[i].ind2 && a[i].c1==a[i].c2) continue;
		if (!isvalid(a[i].ind1,a[i].c1)) continue;
		if (!isvalid(a[i].ind2,a[i].c2) || (a[i].ind1==a[i].ind2 && a[i].c1!=a[i].c2)) add_ban(a[i].ind1,a[i].c1); else v[getind(a[i].ind2,a[i].c2)].pb(getind(a[i].ind1,a[i].c1)),v[getanother(a[i].ind1,a[i].c1)].pb(getanother(a[i].ind2,a[i].c2));
	}
	for (i=1;i<=n*2;i++) dfn[i]=0;Index=0;ind=0;
	for (i=1;i<=n*2;i++) member[i].clear();
	for (i=1;i<=n*2;i++)
		if (!dfn[i]) tarjan(i);
	for (i=1;i<=n;i++)
	{
		if (s[i]=='a') if (bel[getind(i,'B')]==bel[getind(i,'C')]) return -1;
		if (s[i]=='b') if (bel[getind(i,'A')]==bel[getind(i,'C')]) return -1;
		if (s[i]=='c') if (bel[getind(i,'A')]==bel[getind(i,'B')]) return -1;
	}
	for (i=1;i<=ind;i++) vv[i].clear(),deg[i]=0;
	for (i=1;i<=n*2;i++)
		for (j=0;j<int(v[i].size());j++)
			if (bel[i]!=bel[v[i][j]]) vv[bel[i]].pb(bel[v[i][j]]),deg[bel[v[i][j]]]++;
	head=1;tail=0;
	for (i=1;i<=ind;i++) if (deg[i]==0) que[++tail]=i;
	stot=0;
	while (head<=tail)
	{
		cur=que[head++];seq[++stot]=cur;
		for (i=0;i<int(vv[cur].size());i++)
		{
			deg[vv[cur][i]]--;
			if (!deg[vv[cur][i]]) que[++tail]=vv[cur][i];
		}
	}
	memset(taboo,false,sizeof(taboo));
	for (i=1;i<=ind;i++)
	{
		if (!taboo[seq[i]])
		{
			for (j=0;j<int(member[seq[i]].size());j++) finalchoice.pb(member[seq[i]][j]);
			for (j=0;j<int(member[seq[i]].size());j++)
			{
				int ano=(member[seq[i]][j]%2==1?member[seq[i]][j]+1:member[seq[i]][j]-1);
				taboo[bel[ano]]=true;
			}
		}
		else
			for (j=0;j<int(vv[seq[i]].size());j++)
				taboo[vv[seq[i]][j]]=true;
	}
	sort(finalchoice.begin(),finalchoice.end());
	string ans="";
	for (i=0;i<int(finalchoice.size());i++)
	{
		int num=getchoice(finalchoice[i]);
		if (s[i+1]=='a') ans+=(num==1?string(1,'B'):string(1,'C'));
		if (s[i+1]=='b') ans+=(num==1?string(1,'A'):string(1,'C'));
		if (s[i+1]=='c') ans+=(num==1?string(1,'A'):string(1,'B'));
	}
	cout<<ans<<endl;
	return 1;
}

int main ()
{
	int i,Mask,sub;
	n=getint();d=getint();
	scanf("%s",s+1);for (i=1;i<=n;i++) if (s[i]=='x') pos[++tot]=i;
	m=getint();for (i=1;i<=m;i++) a[i].input();
	for (Mask=0;Mask<=(1<<d)-1;Mask++)
	{
		for (i=1;i<=d;i++)
			if (Mask&(1<<(i-1))) chosen[i]='a'; else chosen[i]='b';
		int res=solve();
		if (res!=-1) return 0;
	}
	puts("-1");return 0;
}
