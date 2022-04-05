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

struct node
{
	int x,y,z,w;
	int nx,ny,nz,nw;
	int pnum,qnum,ind;
	bool operator == (const node cp)
	{
		return x==cp.x && y==cp.y && z==cp.z && w==cp.w;
	}
}p[60048],a[60048],b[60048],c[60048],d[60048];
int ans[60048],fans[60048];

int n,q,tot=0,dtot;
int q_ind[30048];

bool cmp(node x,node y)
{
	if (x.x!=y.x) return x.x<y.x;
	if (x.y!=y.y) return x.y<y.y;
	if (x.z!=y.z) return x.z<y.z;
	return x.w<y.w;
}

bool cmp_w(node x,node y)
{
	return x.w<y.w;
}

vector<int> used;
int cc[120048];
inline void update(int x,int delta)
{
	while (x<=dtot)
	{
		cc[x]+=delta;
		used.pb(x);
		x+=LOWBIT(x);
	}
}
inline int query(int x)
{
	int res=0;
	while (x)
	{
		res+=cc[x];
		x-=LOWBIT(x);
	}
	return res;
}
inline int calc(int left,int right)
{
	return query(right)-query(left-1);
}

/*void cdq3(int left,int right)
{
	if (left==right) return;
	int mid=(left+right)>>1;
	cdq3(left,mid);cdq3(mid+1,right);
	int i,k1,k2,pt,cnt=0;
	for (k1=left,k2=mid+1,pt=left;pt<=right;++pt)
		if (k2>right || (k1<=mid && k2<=right && c[k1].w<=c[k2].w))
		{
			d[pt]=c[k1++];
			if (d[pt].nx==0 && d[pt].ny==0) cnt+=d[pt].pnum;
		}
		else
		{
			d[pt]=c[k2++];
			if (d[pt].nx==1 && d[pt].ny==1) ans[d[pt].ind]+=cnt;
		}
	for (i=left;i<=right;i++) c[i]=d[i];
}*/

void cdq2(int left,int right)
{
	if (left==right) return;
	int mid=(left+right)>>1;
	cdq2(left,mid);cdq2(mid+1,right);
	int i,k1,k2,pt;
	used.clear();
	for (k1=left,k2=mid+1,pt=left;pt<=right;++pt)
		if (k2>right || (k1<=mid && k2<=right && b[k1].z<=b[k2].z))
		{
			c[pt]=b[k1++];
			c[pt].ny=0;
			if (!c[pt].nx) update(c[pt].nw,c[pt].pnum);
		}
		else
		{
			c[pt]=b[k2++];
			c[pt].ny=1;
			if (c[pt].nx) ans[c[pt].ind]+=query(c[pt].nw);
		}
	for (i=left;i<=right;i++) b[i]=c[i];
	for (i=0;i<used.size();i++) cc[used[i]]=0;
	//cdq3(left,right);
}

void cdq1(int left,int right)
{
	if (left==right) return;
	int mid=(left+right)>>1;
	cdq1(left,mid);cdq1(mid+1,right);
	int i,k1,k2,pt;
	for (k1=left,k2=mid+1,pt=left;pt<=right;++pt)
		if (k2>right || (k1<=mid && k2<=right && a[k1].y<=a[k2].y))
		{
			b[pt]=a[k1++];
			b[pt].nx=0;
		}
		else
		{
			b[pt]=a[k2++];
			b[pt].nx=1;
		}
	for (i=left;i<=right;i++) a[i]=b[i];
	cdq2(left,right);
}

int main ()
{
	int i;
	n=getint();
	for (i=1;i<=n;i++)
	{
		p[i].x=getint();p[i].y=getint();p[i].z=getint();p[i].w=getint();
		p[i].pnum=1;
	}
	q=getint();
	for (i=n+1;i<=n+q;i++)
	{
		p[i].x=getint();p[i].y=getint();p[i].z=getint();p[i].w=getint();
		p[i].qnum=1;p[i].ind=i-n;
	}
	sort(p+1,p+n+q+1,cmp_w);
	p[1].nw=1;
	for (i=2;i<=n+q;i++) p[i].nw=p[i-1].nw+(p[i].w==p[i-1].w?0:1);
	dtot=p[n+q].nw;
	sort(p+1,p+n+q+1,cmp);
	for (i=1;i<=n+q;i++)
		if (tot==0 || !(a[tot]==p[i]))
		{
			a[++tot]=p[i];a[tot].ind=tot;
			if (p[i].qnum==1) fans[p[i].ind]=a[i].ind;
		}
		else
		{
			if (p[i].pnum==1)
				a[tot].pnum++;
			else
			{
				a[tot].qnum++;
				fans[p[i].ind]=a[i].ind;
			}
		}
	cdq1(1,tot);
	for (i=1;i<=q;i++) printf("%d\n",ans[fans[i]]);
	return 0;
}
