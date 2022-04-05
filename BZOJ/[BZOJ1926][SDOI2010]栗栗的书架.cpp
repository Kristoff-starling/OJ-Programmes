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

const LL MOD=1e9+7;
const LL LINF=2e16;
const int INF=2e9;
const int magic=348;
const double eps=1e-15;
const long double pi=acos(-1);

inline int getint()
{
    char ch;int res;bool f;
    while (!isdigit(ch=getchar()) && ch!='-') {}
    if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
    while (isdigit(ch=getchar())) res=res*10+ch-'0';
    return f?res:-res;
}

int n,m,q;

namespace small
{
	int a[248][248];int sum[201][201][1001],num[201][201][1048];
	inline int getsum(int x1,int y1,int x2,int y2,int k)
	{
		return sum[x2][y2][k]-sum[x2][y1-1][k]-sum[x1-1][y2][k]+sum[x1-1][y1-1][k];
	}
	inline int getnum(int x1,int y1,int x2,int y2,int k)
	{
		return num[x2][y2][k]-num[x2][y1-1][k]-num[x1-1][y2][k]+num[x1-1][y1-1][k];
	}
	inline bool check(int x1,int y1,int x2,int y2,int k,int cmp) {return getsum(x1,y1,x2,y2,k)>=cmp;}
	inline void solve()
	{
		int i,j,k,x1,y1,x2,y2,l,r,h,mid,ansval;
		for (i=1;i<=n;i++)
			for (j=1;j<=m;j++)
				a[i][j]=getint();
		for (k=1;k<=1000;k++)
			for (i=1;i<=n;i++)
			{
				sum[i][0][k]=num[i][0][k]=0;
				for (j=1;j<=m;j++)
				{
					sum[i][j][k]=sum[i][j-1][k]+(a[i][j]>=k?a[i][j]:0);
					num[i][j][k]=num[i][j-1][k]+(a[i][j]>=k?1:0);
				}
				for (j=1;j<=m;j++) sum[i][j][k]+=sum[i-1][j][k],num[i][j][k]+=num[i-1][j][k];
			}
		/*
		for (i=1;i<=n;i++)
		{
			for (j=1;j<=m;j++)
				cout<<sum[i][j][1]<<' ';
			cout<<endl;
		}
		*/
		while (q--)
		{
			x1=getint();y1=getint();x2=getint();y2=getint();h=getint();
			ansval=-1;l=1;r=1000;
			while (l<=r)
			{
				mid=(l+r)>>1;
				if (check(x1,y1,x2,y2,mid,h)) ansval=mid,l=mid+1; else r=mid-1;
			}
			if (ansval==-1) {printf("Poor QLW\n");continue;}
			int cursum=getsum(x1,y1,x2,y2,ansval+1),ans=getnum(x1,y1,x2,y2,ansval+1);cursum=h-cursum;
			if (cursum%ansval==0) ans+=cursum/ansval; else ans+=cursum/ansval+1;
			printf("%d\n",ans);
		}
	}
}

namespace line
{
	int a[500048],root[500048],anspos,ll,tot=0;
	int sum[500048];
	namespace SegmentTree
	{
		struct node
		{
			int lson,rson;
			int sz,sum;
		}tree[7000048];
		inline void pushup(int cur)
		{
			tree[cur].sum=tree[tree[cur].lson].sum+tree[tree[cur].rson].sum;
			tree[cur].sz=tree[tree[cur].lson].sz+tree[tree[cur].rson].sz;
		}
		inline void build(int cur,int left,int right)
		{
			tree[cur].sz=tree[cur].sum=0;
			if (left!=right)
			{
				int mid=(left+right)>>1;
				tree[cur].lson=++tot;build(tot,left,mid);
				tree[cur].rson=++tot;build(tot,mid+1,right);
			}
		}
		inline void Insert(int last,int cur,int pos,int left,int right)
		{
			tree[cur]=tree[last];
			if (left==right)
			{
				tree[cur].sz++;tree[cur].sum+=pos;
				return;
			}
			int mid=(left+right)>>1;
			if (pos<=mid)
			{
				tree[cur].lson=++tot;
				Insert(tree[last].lson,tree[cur].lson,pos,left,mid);
			}
			else
			{
				tree[cur].rson=++tot;
				Insert(tree[last].rson,tree[cur].rson,pos,mid+1,right);
			}
			pushup(cur);
		}
		inline int query(int last,int cur,int need,int left,int right)
		{
			if (left==right)
			{
				anspos=left;ll=need;
				return 0;
			}
			int cursum=tree[tree[cur].rson].sum-tree[tree[last].rson].sum,mid=(left+right)>>1;
			if (cursum>=need)
				return query(tree[last].rson,tree[cur].rson,need,mid+1,right);
			else
				return tree[tree[cur].rson].sz-tree[tree[last].rson].sz+query(tree[last].lson,tree[cur].lson,need-cursum,left,mid);
		}
	}
	inline void solve()
	{
		int i,left,right,h;swap(n,m);
		root[0]=++tot;SegmentTree::build(root[0],1,1000);
		memset(sum,0,sizeof(sum));
		for (i=1;i<=n;i++) a[i]=getint(),root[i]=++tot,SegmentTree::Insert(root[i-1],root[i],a[i],1,1000),sum[i]=sum[i-1]+a[i];
		while (q--)
		{
			left=getint();left=getint();right=getint();right=getint();h=getint();
			if (sum[right]-sum[left-1]<h) {printf("Poor QLW\n");continue;}
			int res=SegmentTree::query(root[left-1],root[right],h,1,1000);
			if (ll%anspos==0) res+=ll/anspos; else res+=ll/anspos+1;
			printf("%d\n",res);
		}
	}
}			

int main ()
{
	int i;
	n=getint();m=getint();q=getint();
	if (n<=200 && m<=200) small::solve(); else line::solve();
	return 0;
}
/*
1 10 3
2 2 5 4 4 7 7 7 9 100
1 1 1 10 109
1 3 1 6 16
1 1 1 10 200
*/
