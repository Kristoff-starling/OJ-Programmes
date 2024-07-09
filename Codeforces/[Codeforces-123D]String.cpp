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

inline int getint()
{
	bool f;char ch;int res;
	while (!isdigit(ch=getchar()) && ch!='-') {}
	if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
	while (isdigit(ch=getchar())) res=res*10+ch-'0';
	return f?res:-res;
}

const int MAXN=1e5;

char s[MAXN+48];
int sa[MAXN+48],rnk[MAXN+48],tmp[MAXN+48],lcp[MAXN+48],k,len;

struct List
{
	int head[MAXN+48],nxt[MAXN+48],cur[MAXN+48],tot;Pair val[MAXN+48];
	inline void init() {memset(head,0,sizeof(head));tot=0;}
	inline void insert(int pos,Pair v)
	{
		if (!head[pos]) {head[pos]=++tot;cur[pos]=head[pos];val[tot]=v;nxt[tot]=0;return;}
		nxt[cur[pos]]=++tot;cur[pos]=tot;
		val[tot]=v;nxt[tot]=0;
	}
}l1,l2;

inline bool compare_sa(int x,int y)
{
	if (rnk[x]!=rnk[y]) return rnk[x]<rnk[y];
	int tmp1=x+k<=len?rnk[x+k]:-1,tmp2=y+k<=len?rnk[y+k]:-1;
	return tmp1<tmp2;
}

inline int getrnk(int x,bool type)
{
	if (!type) return rnk[x];
	return x+k<=len?rnk[x+k]:0;
}

inline void Sort()
{
	int i,j;
	l1.init();
	for (i=1;i<=len;i++) l1.insert(getrnk(sa[i],true),mp(getrnk(sa[i],false),sa[i]));
	l2.init();
	for (i=0;i<=max(len,256);i++)
		for (j=l1.head[i];j;j=l1.nxt[j])
			l2.insert(l1.val[j].x,mp(l1.val[j].y,0));
	int tt=0;
	for (i=0;i<=max(len,256);i++)
		for (j=l2.head[i];j;j=l2.nxt[j])
			sa[++tt]=l2.val[j].x;
}

inline void construct_sa()
{
	int i;
	for (i=1;i<=len;i++) sa[i]=i,rnk[i]=s[i];
	for (k=0;k<=len;k==0?k++:k<<=1)
	{
		Sort();
		tmp[sa[1]]=1;int cnt=0;
		for (i=2;i<=len;i++)
		{
			tmp[sa[i]]=tmp[sa[i-1]]+(compare_sa(sa[i-1],sa[i])?1:0);
			cnt+=(tmp[sa[i]]!=tmp[sa[i-1]]);
		}
		for (i=1;i<=len;i++) rnk[i]=tmp[i];
		if (cnt>=len-1) break;
	}
}

inline void construct_lcp()
{
	int i,j,h=0;
	for (i=1;i<=len;i++) rnk[sa[i]]=i;
	for (i=1;i<=len;i++)
	{
		j=sa[rnk[i]-1];
		if (h) h--;
		while (i+h<=len && j+h<=len && s[i+h]==s[j+h]) h++;
		lcp[rnk[i]-1]=h;
	}
}

stack<pLL> sta;

int main ()
{
	scanf("%s",s+1);len=strlen(s+1);int i;
	construct_sa();construct_lcp();
	LL ans=(1ll*(len+1)*len)/2,curans=0;
	for (i=len-1;i>=1;i--)
	{
		LL curcnt=1;
		while (!sta.empty() && lcp[i]<sta.top().x) curcnt+=sta.top().y,curans-=sta.top().x*sta.top().y,sta.pop();
		curans+=lcp[i]*curcnt;
		ans+=curans;sta.push(mp(lcp[i],curcnt));
	}
	printf("%lld\n",ans);
	return 0;
}
