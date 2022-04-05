#include <cstdio>
#include <iostream>
#include <cstring>
#include <string>
#include <cstdlib>
#include <utility>
#include <cctype>
#include <cmath>
#include <iomanip>
#include <bitset>
#include <sstream>
#include <functional>
#include <algorithm>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <deque>
#include <stack>
#include <list>
#define LL long long
#define LB long double
#define x first
#define y second
#define Pair pair<int,int>
#define pLL pair<LL,LL>
#define pii pair<double,double>
#define pb push_back
#define pf push_front
#define mp make_pair
#define LOWBIT(x) x & (-x)
using namespace std;

const int INF=1e9;
const LL LINF=2e16;
const int magic=348;
const int MOD=1e9+7;
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
char s[MAXN+48];int k,len,K;
int rnk[MAXN+48],tmp[MAXN+48],sa[MAXN+48],lcp[MAXN+48];
int ST[MAXN+48][21],Log[MAXN+48];LL maxn;

int head[MAXN+48],to1[MAXN+48],to2[MAXN+48],nxt[MAXN+48],tot=0;
inline void add(int s,int v1,int v2) {to1[++tot]=v1;to2[tot]=v2;nxt[tot]=head[s];head[s]=tot;}
int Head[MAXN+48],To[MAXN+48],Nxt[MAXN+48],num[MAXN+48],Tot=0;
inline void Add(int s,int v) {To[++Tot]=v;Nxt[Tot]=Head[s];Head[s]=Tot;num[s]++;}
inline Pair getrnk(int x) {return mp(rnk[x],x+k<=len?rnk[x+k]:0);}

inline void Sort()
{
	int i,j;
	for (i=0;i<=max(len,200);i++) head[i]=Head[i]=num[i]=0;tot=Tot=0;
	for (i=1;i<=len;i++)
	{
		Pair res=getrnk(sa[i]);
		add(res.y,res.x,sa[i]);
	}
	for (i=0;i<=max(len,200);i++)
		for (j=head[i];j;j=nxt[j])
			Add(to1[j],to2[j]);
	int tt=0,pt;
	for (i=0;i<=max(len,200);i++)
	{
		for (j=Head[i],pt=0;j;j=Nxt[j],pt++)
			sa[tt+num[i]-pt]=To[j];
		tt+=num[i];
	}
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
			tmp[sa[i]]=tmp[sa[i-1]]+(getrnk(sa[i-1])<getrnk(sa[i])?1:0);
			cnt+=(tmp[sa[i]]!=tmp[sa[i-1]]);
		}
		for (i=1;i<=len;i++) rnk[i]=tmp[i];
		if (cnt==len-1) break;
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

inline void construct_ST()
{
	int i,j;
	Log[0]=Log[1]=0;for (i=2;i<=len;i++) Log[i]=Log[i>>1]+1;
	for (i=1;i<=len-1;i++) ST[i][0]=lcp[i];
	for (j=1;j<=20;j++)
		for (i=1;i<=len-1;i++)
		{
			ST[i][j]=ST[i][j-1];
			if (i+(1<<(j-1))<=len-1) ST[i][j]=min(ST[i][j],ST[i+(1<<(j-1))][j-1]);
		}
}

inline int query_ST(int left,int right)
{
	int k=Log[right-left+1];
	return min(ST[left][k],ST[right-(1<<k)+1][k]);
}

int curnum,curpos;
inline void getstring(LL k)
{
	int i,cc;
	for (i=1;i<=len;i++)
	{
		cc=len-sa[i]+1;if (i) cc-=lcp[i-1];
		if (k>cc) k-=cc; else {curnum=i;curpos=lcp[i-1]+k;return;}
	}
}

inline bool isLarge(int left,int right)
{
	int n1=curnum,n2=rnk[left];
	if (n1>n2) swap(n1,n2);
	int len1=curpos,len2=right-left+1,samelen=(n1!=n2?query_ST(n1,n2-1):min(len1,len2));
	samelen=min(samelen,min(len1,len2));
	if (samelen==min(len1,len2)) return len2>len1;
	return s[left+samelen]>s[sa[curnum]+samelen];
}

inline bool check(int k)
{
	int i,cnt=0,cright=len;
	for (i=len;i>=1;i--)
		if (isLarge(i,cright))
		{
			if (i==cright) return false;
			cright=i;cnt++;
			if (isLarge(i,cright)) return false;
		}
	return cnt+1<=K;
}

int main ()
{
	int ansnum,anspos,i;
	K=getint();scanf("%s",s+1);len=strlen(s+1);
	construct_sa();construct_lcp();construct_ST();
	maxn=0;for (i=1;i<=len;i++) {maxn+=len-sa[i]+1;if (i!=1) maxn-=lcp[i-1];}
	getstring(maxn);
	LL l=1,r=maxn,mid;
	while (l<=r)
	{
		mid=(l+r)>>1;
		getstring(mid);
		if (check(mid)) ansnum=curnum,anspos=curpos,r=mid-1; else l=mid+1;
	}
	for (i=sa[ansnum];i<=sa[ansnum]+anspos-1;i++) printf("%c",s[i]);
	puts("");return 0;
}
