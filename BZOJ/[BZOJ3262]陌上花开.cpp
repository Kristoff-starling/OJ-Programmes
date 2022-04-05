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
	int num,ind;
	int x,y,z;
	int nx,ny,nz;
	bool operator == (const node cp)
	{
		return (x==cp.x) && (y==cp.y) && (z==cp.z);
	}
}p[100048],a[100048],b[100048],c[100048];

int n,tot=0;
int ans[100048],num[100048],cnt[100048];

bool cmp(node x,node y)
{
	if (x.x!=y.x) return x.x<y.x;
	if (x.y!=y.y) return x.y<y.y;
	return x.z<y.z;
}

void cdq2(int left,int right)
{
	if (left==right) return;
	int i,k1,k2,pt,mid=(left+right)>>1;
	cdq2(left,mid);cdq2(mid+1,right);
	int cnt=0;
	for (k1=left,k2=mid+1,pt=left;pt<=right;pt++)
	{
		if (k2>right || (k1<=mid && k2<=right && b[k1].z<=b[k2].z))
		{
			if (!b[k1].nx) cnt+=b[k1].num;
			c[pt]=b[k1++];
		}
		else
		{
			if (b[k2].nx) ans[b[k2].ind]+=cnt;
			c[pt]=b[k2++];
		}
	}
	for (i=left;i<=right;i++) b[i]=c[i];
}

void cdq1(int left,int right)
{
	if (left==right) return;
	int i,k1,k2,pt,mid=(left+right)>>1;
	cdq1(left,mid);cdq1(mid+1,right);
	for (k1=left,k2=mid+1,pt=left;pt<=right;pt++)
	{
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
	}
	for (i=left;i<=right;i++) a[i]=b[i];
	cdq2(left,right);
}

int main ()
{
	int i;
	n=getint();i=getint();
	for (i=1;i<=n;i++) {p[i].x=getint();p[i].y=getint();p[i].z=getint();}
	sort(p+1,p+n+1,cmp);
	for (i=1;i<=n;i++)
	{
		if (tot==0)
		{
			a[++tot]=p[i];a[tot].num=1;a[tot].ind=tot;
			continue;
		}
		if (a[tot]==p[i])
			a[tot].num++;
		else
		{
			a[++tot]=p[i];a[tot].num=1;a[tot].ind=tot;
		}
	}
	for (i=1;i<=tot;i++) num[i]=a[i].num;
	cdq1(1,tot);
	for (i=1;i<=tot;i++) cnt[ans[i]+num[i]-1]+=num[i];
	for (i=0;i<=n-1;i++) printf("%d\n",cnt[i]);
	return 0;
}
