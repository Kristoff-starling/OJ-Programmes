#include <cstdio>
#include <iostream>
#include <cstring>
#include <string>
#include <cstdlib>
#include <utility>
#include <cctype>
#include <algorithm>
#include <bitset>
#include <set>
#include <map>
#include <vector>
#include <queue>
#include <deque>
#include <stack>
#include <cmath>
#define LL long long
#define LB long double
#define x first
#define y second
#define Pair pair<int,int>
#define pb push_back
#define pf push_front
#define mp make_pair
#define LOWBIT(x) x & (-x)
using namespace std;

const int MOD=1e9+9;
const LL LINF=2e16;
const int INF=2e9;
const int magic=108;
const double eps=1e-10;
const double pi=3.14159265;

inline int getint()
{
    char ch;int res;bool f;
    while (!isdigit(ch=getchar()) && ch!='-') {}
    if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
    while (isdigit(ch=getchar())) res=res*10+ch-'0';
    return f?res:-res;
}

inline LL getLL()
{
    char ch;LL res;bool f;
    while (!isdigit(ch=getchar()) && ch!='-') {}
    if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
    while (isdigit(ch=getchar())) res=res*10+ch-'0';
    return f?res:-res;
}

int n,q;
LL a[100048];
LL sum[100048],maxn[100048];
LL bmax[248][248];int bnum;

int root[100048],tot;
namespace Trie
{
	struct node
	{
		int lson,rson;
		int num;
	}tree[2000048];
	inline void build(int cur) {tree[cur].lson=tree[cur].rson=0;}
	inline void pushup(int cur) {tree[cur].num=tree[tree[cur].lson].num+tree[tree[cur].rson].num;}
	inline void Insert(int last,int cur,int pos,LL number)
	{
		tree[cur]=tree[last];
		if (!pos) {tree[cur].num++;return;}
		int dir=number&(1ll<<(pos-1));
		if (!dir)
		{
			tree[cur].lson=++tot;
			Insert(tree[last].lson,tree[cur].lson,pos-1,number);
		}
		else
		{
			tree[cur].rson=++tot;
			Insert(tree[last].rson,tree[cur].rson,pos-1,number);
		}
		pushup(cur);
	}
	inline LL query_max(int last,int cur,int pos,LL number)
	{
		if (!pos) return 0;
		int dir=number&(1ll<<(pos-1));
		if (!dir)
		{
			int valid=tree[tree[cur].rson].num-tree[tree[last].rson].num;
			if (valid) return query_max(tree[last].rson,tree[cur].rson,pos-1,number)+(1ll<<(pos-1)); else return query_max(tree[last].lson,tree[cur].lson,pos-1,number);
		}
		else
		{
			int valid=tree[tree[cur].lson].num-tree[tree[last].lson].num;
			if (valid) return query_max(tree[last].lson,tree[cur].lson,pos-1,number)+(1ll<<(pos-1)); else return query_max(tree[last].rson,tree[cur].rson,pos-1,number);
		}
	}
}

inline int getbnum(int pos)
{
	if (pos%magic==0) return pos/magic; else return pos/magic+1;
}

int main ()
{
	int i,j,k,l,r,nl,nr;n=getint();q=getint();
	for (i=1;i<=n;i++) a[i]=getLL(),sum[i]=(sum[i-1]^a[i]),maxn[i]=max(maxn[i-1],sum[i]);
	root[0]=++tot;Trie::build(root[0]);
	for (i=1;i<=n;i++) root[i]=++tot,Trie::Insert(root[i-1],root[i],31,sum[i]);
	bnum=n/magic;
	for (k=1;k<=bnum;k++)
	{
		bmax[k][k]=0;
		for (i=(k-1)*magic+1;i<=k*magic-1;i++)
			for (j=i+1;j<=k*magic;j++)
				bmax[k][k]=max(bmax[k][k],sum[i]^sum[j]);
	}
	for (k=2;k<=bnum;k++)
		for (i=1;i<=bnum-k+1;i++)
		{
			bmax[i][i+k-1]=max(bmax[i][i],bmax[i+1][i+k-1]);
			for (j=(i-1)*magic+1;j<=i*magic;j++)
			{
				LL res=Trie::query_max(root[i*magic],root[(i+k-1)*magic],31,sum[j]);
				bmax[i][i+k-1]=max(bmax[i][i+k-1],res);
			}
		}
	LL lastans=0,ans;
	while (q--)
	{
		l=getint();r=getint();
		nl=min((l+lastans%n)%n+1,(r+lastans%n)%n+1);
		nr=max((l+lastans%n)%n+1,(r+lastans%n)%n+1);
		l=nl;r=nr;l--;
		if (l) nl=l,nr=r; else nl=l+1,nr=r;
		int L=getbnum(nl),R=getbnum(nr);
		ans=0;
		if (R-L>=2) ans=bmax[L+1][R-1];
		for (i=nl;i<=min(L*magic,nr-1);i++) ans=max(ans,Trie::query_max(root[i],root[nr],31,sum[i]));
		for (i=nr;i>=max((R-1)*magic+1,nl+1);i--) ans=max(ans,Trie::query_max(root[nl-1],root[i-1],31,sum[i]));
		if (l==0) ans=max(ans,maxn[nr]);
		printf("%lld\n",ans);
		lastans=ans;
	}
	return 0;
}
