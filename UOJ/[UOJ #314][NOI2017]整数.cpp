#include <bits/stdc++.h>
using namespace std;

#define LL long long
#define LB long double
#define ull unsigned long long
#define pb push_back
#define pf push_front
#define mp make_pair
#define x first
#define y second
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
	char ch;int res;bool f;
	while (!isdigit(ch=getchar()) && ch!='-') {}
	if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
	while (isdigit(ch=getchar())) res=res*10+ch-'0';
	return f?res:-res;
}

const int MAXN=3e7+48;

int n;

bitset<MAXN+48> Add,Sub;

namespace SegmentTree
{
	//0:same 1:different
	bitset<MAXN*4> tree;
	inline void pushup(int cur)
	{
		if (tree[cur<<1]==1 || tree[cur<<1|1]==1) tree[cur]=1; else tree[cur]=0;
	}
	inline void update(int cur,int left,int right,int l,int r)
	{
		if (l==r) {tree[cur]=(Add[l]==Sub[l]?0:1);return;}
		int mid=(l+r)>>1;
		if (left<=mid) update(cur<<1,left,right,l,mid);
		if (mid+1<=right) update(cur<<1|1,left,right,mid+1,r);
		pushup(cur);
	}
	inline pair<int,Pair> query_ind(int cur,int right,int l,int r)
	{
		if (right==0) return mp(-1,mp(-1,-1));
		if (right==r) return (tree[cur]==1?mp(cur,mp(l,r)):mp(-1,mp(-1,-1)));
		int mid=(l+r)>>1;
		if (right<=mid) return query_ind(cur<<1,right,l,mid);
		pair<int,Pair> res=(tree[cur<<1]==1?mp(cur<<1,mp(l,mid)):mp(-1,mp(-1,-1))),res1;
		res1=query_ind(cur<<1|1,right,mid+1,r);
		return max(res,res1);
	}
	inline int query_pos(int cur,int l,int r)
	{
		if (l==r) return l;
		int mid=(l+r)>>1;
		if (tree[cur<<1|1]==1) return query_pos(cur<<1|1,mid+1,r); else return query_pos(cur<<1,l,mid);
	}
}

inline void modify(int x,int b)
{
	if (x==0) return;
	int L=b,R=b,i,pt;
	if (x>0)
	{
		for (i=0;i<=30;i++)
		{
			int bit=(x&(1<<i))?1:0;
			if (bit)
			{
				for (pt=b+i;Add[pt]==1;pt++) Add[pt]=0;
				Add[pt]=1;R=max(R,pt);
			}
		}
	}
	else
	{
		x=-x;
		for (i=0;i<=30;i++)
		{
			int bit=(x&(1<<i))?1:0;
			if (bit)
			{
				for (pt=b+i;Sub[pt]==1;pt++) Sub[pt]=0;
				Sub[pt]=1;R=max(R,pt);
			}
		}
	}
	SegmentTree::update(1,L,R,1,MAXN);
}

inline bool Get(int b)
{
	pair<int,Pair> res=SegmentTree::query_ind(1,b-1,1,MAXN);
	if (res.x==-1) return false;
	int pos=SegmentTree::query_pos(res.x,res.y.x,res.y.y);
	if (Add[pos]==1) return false; else return true;
}

int main ()
{
	int i,op,x,b,t1,t2,t3;n=getint();t1=getint();t2=getint();t3=getint();
	while (n--)
	{
		op=getint();
		if (op==1)
		{
			x=getint();b=getint();b++;
			modify(x,b);
		}
		else
		{
			b=getint();b++;
			if (!Get(b))
			{
				if (Sub[b]==0) {puts(Add[b]==1?"1":"0");continue;}
				puts(Add[b]==1?"0":"1");
			}
			else
			{
				if (Sub[b]==1) {puts(Add[b]==1?"1":"0");continue;}
				puts(Add[b]==1?"0":"1");
			}
		}
	}
	return 0;
}
