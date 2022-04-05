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

const int INF=1e9;
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

const int MAXN=50000;

int n,q;
int a[MAXN+48];

namespace SegmentTree
{
	int lson[MAXN*30*15],rson[MAXN*30*15],cnt[MAXN*30*15],tot;
	inline void build(int cur,int l,int r)
	{
		tot=max(tot,cur);
		lson[cur]=rson[cur]=cnt[cur]=0;
		if (l!=r)
		{
			int mid=(l+r)>>1;
			build(cur<<1,l,mid);build(cur<<1|1,mid+1,r);
		}
	}
	inline void updatey(int &cur,int pos,int delta,int l,int r)
	{
		if (!cur) cur=++tot,cnt[cur]=0;
		cnt[cur]+=delta;
		if (l==r) return;
		int mid=(l+r)>>1;
		if (pos<=mid) updatey(lson[cur],pos,delta,l,mid); else updatey(rson[cur],pos,delta,mid+1,r);
	}
	inline void updatex(int cur,int pos,int val,int delta,int l,int r)
	{
		updatey(cur,val,delta,0,1e9);
		if (l==r) return;
		int mid=(l+r)>>1;
		if (pos<=mid) updatex(cur<<1,pos,val,delta,l,mid); else updatex(cur<<1|1,pos,val,delta,mid+1,r);
	}
	vector<int> sgt;
	inline void query_sgt(int cur,int left,int right,int l,int r)
	{
		if (left<=l && r<=right) {sgt.pb(cur);return;}
		int mid=(l+r)>>1;
		if (left<=mid) query_sgt(cur<<1,left,right,l,mid);
		if (mid+1<=right) query_sgt(cur<<1|1,left,right,mid+1,r);
	}
	inline int query_k(int left,int right,int k)
	{
		sgt.clear();query_sgt(1,left,right,1,n);
		int l=0,r=1e9,mid,i;
		while (l<r)
		{
			mid=(l+r)>>1;int sum=0;
			for (i=0;i<int(sgt.size());i++) sum+=cnt[lson[sgt[i]]];
			if (sum>=k)
			{
				r=mid;
				for (i=0;i<int(sgt.size());i++) sgt[i]=lson[sgt[i]];
			}
			else
			{
				k-=sum;
				for (i=0;i<int(sgt.size());i++) sgt[i]=rson[sgt[i]];
				l=mid+1;
			}
		}
		return l;
	}
}

int main ()
{
	int i,x,y,c,ca;
	n=getint();q=getint();char op[5];
	for (i=1;i<=n;i++) a[i]=getint();
	SegmentTree::build(1,1,n);
	for (i=1;i<=n;i++) SegmentTree::updatex(1,i,a[i],1,1,n);
	while (q--)
	{
		scanf("%s",op+1);
		if (op[1]=='C')
		{
			x=getint();y=getint();
			SegmentTree::updatex(1,x,a[x],-1,1,n);
			a[x]=y;
			SegmentTree::updatex(1,x,a[x],1,1,n);
		}
		else
		{
			x=getint();y=getint();c=getint();
			printf("%d\n",SegmentTree::query_k(x,y,c));
		}
	}
	return 0;
}
