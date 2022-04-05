#include <cstdio>
#include <iostream>
#include <cstring>
#include <string>
#include <cstdlib>
#include <utility>
#include <vector>
#include <algorithm>
#include <queue>
#include <cmath>
#include <deque>
#include <stack>
#include <cmath>
#include <set>
#include <map>
#define LL long long
#define LB long double
#define Pair pair<int,int>
#define x first
#define y second
#define pb push_back
#define mp make_pair
#define LOWBIT(x) x & (-x)
using namespace std;
 
const int INF=2e9;
const LL LINF=2e16;
const int MOD=1e9+7;
const int magic=348;
const double eps=1e-10;
 
inline int getint()
{
    char ch;int res=0;bool f;
    while (!isdigit(ch=getchar()) && ch!='-') {}
    if (ch=='-') f=false,res=0; else res=ch-'0',f=true;
    while (isdigit(ch=getchar())) res=res*10+ch-'0';
    return f?res:-res;
}

int n,k;
int a[200048],b[400048];
int sa[400048],rank[400048],tmp[400048];

bool compare_sa(int x,int y)
{
	if (rank[x]!=rank[y]) return rank[x]<rank[y];
	int tmp1=x+k<=n?rank[x+k]:-1,tmp2=y+k<=n?rank[y+k]:-1;
	return tmp1<tmp2;
}

void construct_sa()
{
	int i,cnt=0;
	for (i=1;i<=n;i++)
	{
		sa[i]=i;
		rank[i]=b[i];
	}
	for (k=0;k<=n;k==0?k++:k*=2)
	{
		sort(sa+1,sa+n+1,compare_sa);
		tmp[sa[1]]=1;cnt=0;
		for (i=2;i<=n;i++)
		{
			tmp[sa[i]]=tmp[sa[i-1]]+(compare_sa(sa[i-1],sa[i])?1:0);
			cnt+=tmp[sa[i]]==tmp[sa[i-1]]?0:1;
		}
		for (i=1;i<=n;i++) rank[i]=tmp[i];
		//for (i=1;i<=n;i++) cout<<sa[i]<<' ';
		//cout<<endl;
		if (cnt>=n-1) break;
	}
}

int main ()
{
	int i,j;
	n=getint();
	for (i=1;i<=n;i++) a[i]=b[i]=getint();
	for (i=1;i<=n/2;i++) swap(b[i],b[n+1-i]);
	construct_sa();
	int pos;
	for (i=1;i<=n;i++)
		if (sa[i]-1>1)
		{
			pos=i;
			for (j=sa[i];j<=n;j++) printf("%d\n",b[j]);
			break;
		}
	//for (i=sa[1];i<=n;i++) printf("%d\n",b[i]);
	//cout<<"^"<<sa[1]<<endl;
	n=sa[pos]-1;int need=n;
	for (i=n+1;i<=n*2;i++) b[i]=b[i-n];
	n*=2;
	//for (i=1;i<=n;i++) cout<<b[i]<<' ';
	//cout<<endl;
	construct_sa();
	//for (i=1;i<=n;i++) cout<<sa[i]<<' ';
	//cout<<endl;
	for (i=1;i<=n;i++)
		if (2<=sa[i] && sa[i]<=n/2)
		{
			for (j=sa[i];j<=sa[i]+need-1;j++)
				printf("%d\n",b[j]);
			break;
		}
	return 0;
}
