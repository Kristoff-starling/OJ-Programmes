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

const int MOD=1e9+7;
const LL LINF=2e16;
const int INF=2e9;
const int magic=348;
const double eps=1e-10;

inline int getint()
{
	char ch;int res;bool f;
	while (!isdigit(ch=getchar()) && ch!='-') {}
	if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
	while (isdigit(ch=getchar())) res=res*10+ch-'0';
	return f?res:-res;
}

int n,q;

struct border
{
	int pos,num;
	bool isleft;
	bool type;
}a[1200048];

int len[1200048],tot;
int Left[1200048],Right[1200048];

bool cmp(border x,border y)
{
	if (x.pos!=y.pos) return x.pos<y.pos;
	int tmp1=x.isleft?0:1,tmp2=y.isleft?0:1;
	return tmp1<tmp2;
}

bool cmp_num(border x,border y)
{
	return x.num<y.num;
}

struct Tree
{
	int len;
	int type;
	int ans;
}tree[3000048];

void build(int cur,int left,int right)
{
	tree[cur].type=1;
	if (left!=right)
	{
		int mid=(left+right)>>1;
		build(cur<<1,left,mid);
		build(cur<<1|1,mid+1,right);
		tree[cur].len=tree[cur<<1].len+tree[cur<<1|1].len;
		tree[cur].ans=tree[cur<<1].ans+tree[cur<<1|1].ans;
	}
	else
	{
		tree[cur].len=len[left];
		tree[cur].ans=len[left];
	}
}

void update(int cur,int left,int right,bool type,int ll,int rr)
{
	if (left<=ll && rr<=right)
	{
		tree[cur].type=type;
		if (tree[cur].type) tree[cur].ans=tree[cur].len; else tree[cur].ans=0;
		return;
	}
	if (tree[cur].type<=1)
	{
		tree[cur<<1].type=tree[cur].type;
		tree[cur<<1|1].type=tree[cur].type;
		tree[cur<<1].ans=tree[cur].type?tree[cur<<1].len:0;
		tree[cur<<1|1].ans=tree[cur].type?tree[cur<<1|1].len:0;
	}
	int mid=(ll+rr)>>1;
	if (left<=mid) update(cur<<1,left,right,type,ll,mid);
	if (mid+1<=right) update(cur<<1|1,left,right,type,mid+1,rr);
	if (tree[cur<<1].type==tree[cur<<1|1].type) tree[cur].type=tree[cur<<1].type; else tree[cur].type=2;
	tree[cur].ans=tree[cur<<1].ans+tree[cur<<1|1].ans;
}

int query(int cur,int left,int right,int ll,int rr)
{
	if (tree[cur].type<=1)
		return tree[cur].len*(tree[cur].type?1:0);
	int mid=(ll+rr)>>1;
	int res=0;
	if (left<=mid) res=query(cur<<1,left,right,ll,mid);
	if (mid+1<=right) res+=query(cur<<1|1,left,right,mid+1,rr);
	return res;
}

int main ()
{
	int i,k;
	n=getint();q=getint();
	for (i=1;i<=q;i++)
	{
		a[i*2-1].pos=getint();
		a[i*2-1].num=i;
		a[i*2-1].isleft=true;
		a[i*2].pos=getint();
		a[i*2].num=i;
		a[i*2].isleft=false;
		k=getint();
		if (k==1) a[i*2-1].type=a[i*2].type=false; else a[i*2-1].type=a[i*2].type=true;
	}
	sort(a+1,a+q*2+1,cmp);
	a[0].pos=1;a[0].isleft=true;
	a[q*2+1].pos=n;a[q*2+1].isleft=false;
	for (i=0;i<=q*2;i++)
	{
		if (a[i].isleft && a[i+1].isleft)
		{
			len[i+1]=a[i+1].pos-a[i].pos;
			Left[a[i].num]=i+1;
		}
		if (a[i].isleft && !a[i+1].isleft)
		{
			len[i+1]=a[i+1].pos-a[i].pos+1;
			Left[a[i].num]=Right[a[i+1].num]=i+1;
		}
		if (!a[i].isleft && a[i+1].isleft)
		{
			len[i+1]=a[i+1].pos-a[i].pos-1;
		}
		if (!a[i].isleft && !a[i+1].isleft)
		{
			len[i+1]=a[i+1].pos-a[i].pos;
			Right[a[i+1].num]=i+1;
		}
	}
	build(1,1,q*2+1);
	sort(a+1,a+q*2+1,cmp_num);
	for (i=1;i<=q;i++)
	{
		update(1,Left[i],Right[i],a[i*2-1].type,1,q*2+1);
		printf("%d\n",tree[1].ans);
	}
	return 0;
}
