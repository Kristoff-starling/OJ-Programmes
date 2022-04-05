#include <cstdio>
#include <iostream>
#include <cstring>
#include <string>
#include <cstdlib>
#include <utility>
#include <cctype>
#include <bitset>
#include <sstream>
#include <cmath>
#include <iomanip>
#include <functional>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <queue>
#include <deque>
#include <stack>
#include <list>
#define LL long long
#define LB long double
#define x first
#define y second
#define pb push_back
#define pf push_front
#define mp make_pair
#define Pair pair<int,int>
#define pLL pair<LL,LL>
#define pii pair<double,double>
#define LOBIT(x) x & (-x)
using namespace std;

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

inline LL getLL()
{
	bool f;char ch;LL res;
	while (!isdigit(ch=getchar()) && ch!='-') {}
	if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
	while (isdigit(ch=getchar())) res=res*10+ch-'0';
	return f?res:-res;
}

const int MAXN=160;

int n,len,alphabet;
string ss;

namespace AC
{
	struct node
	{
		bool danger;
		int fail,nxt[30];
		inline void clear() {danger=false;fail=0;for (register int i=1;i<=alphabet;i++) nxt[i]=0;}
	}trie[248];int tot;
	inline void init() {tot=1;trie[1].clear();}
	inline void Insert(string s)
	{
		int cur=1,w,i;int len=int(s.size());
		for (i=0;i<len;i++)
		{
			w=s[i]-'a'+1;
			if (!trie[cur].nxt[w])
			{
				trie[cur].nxt[w]=++tot;
				trie[tot].clear();
			}
			cur=trie[cur].nxt[w];
			if (i==len-1) trie[cur].danger=true;
		}
	}
	int q[MAXN+48],head,tail;
	inline void construct_fail()
	{
		head=tail=1;q[1]=1;int i,cur,tmp;
		while (head<=tail)
		{
			cur=q[head++];
			for (i=1;i<=alphabet;i++)
				if (trie[cur].nxt[i])
				{
					tmp=trie[cur].fail;
					while (tmp && !trie[tmp].nxt[i]) tmp=trie[tmp].fail;
					trie[trie[cur].nxt[i]].fail=(!tmp?1:trie[tmp].nxt[i]);
					q[++tail]=trie[cur].nxt[i];
				}
				else
					trie[cur].nxt[i]=(cur==1?1:trie[trie[cur].fail].nxt[i]);
		}
	}
}

using namespace AC;

int Nxt[248][30],val[248][30];

struct Matrix
{
	LB b[168][168];
	inline void clear() {memset(b,0,sizeof(b));}
	inline void init_I() {clear();for (register int i=1;i<=tot*2;i++) b[i][i]=1;}
	inline Matrix operator + (Matrix ma)
	{
		Matrix res;res.clear();
		for (register int i=1;i<=tot*2;i++)
			for (register int j=2;j<=tot*2;j++)
				res.b[i][j]=b[i][j]+ma.b[i][j];
		return res;
	}
	inline Matrix operator * (Matrix ma)
	{
		Matrix res;res.clear();
		for (register int i=1;i<=tot*2;i++)
			for (register int j=1;j<=tot*2;j++)
				for (register int k=1;k<=tot*2;k++)
					res.b[i][j]+=b[i][k]*ma.b[k][j];
		return res;
	}
}sta,trans;

inline Matrix quick_pow(Matrix x,int y)
{
	Matrix res;res.init_I();
	while (y)
	{
		if (y&1) res=res*x,y--;
		x=x*x;y>>=1;
	}
	return res;
}

int main ()
{
	//freopen ("a.in","r",stdin);
	//freopen ("a.out","w",stdout);
	n=getint();len=getint();alphabet=getint();int i,j,to;
	init();
	for (i=1;i<=n;i++) cin>>ss,Insert(ss);
	construct_fail();
	for (i=1;i<=tot;i++)
		for (j=1;j<=alphabet;j++)
		{
			to=trie[i].nxt[j];
			if (trie[to].danger) Nxt[i][j]=1,val[i][j]=1; else Nxt[i][j]=to,val[i][j]=0;
		}
	trans.clear();
	for (i=1;i<=tot;i++)
		for (j=1;j<=alphabet;j++)
		{
			trans.b[i][Nxt[i][j]]+=(LB)1.0/alphabet;
			trans.b[tot+i][Nxt[i][j]+tot]+=(LB)1.0/alphabet;
			trans.b[i][Nxt[i][j]+tot]+=(LB)1.0/alphabet*val[i][j];
		}
	sta.clear();sta.b[1][1]=1;
	sta=sta*quick_pow(trans,len);
	double ans=0;
	for (i=1;i<=tot;i++) ans+=sta.b[1][i+tot];
	printf("%.9lf\n",ans);
	return 0;
}
