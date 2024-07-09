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
const double pi=3.14159265;

inline int getint()
{
    char ch;int res;bool f;
    while (!isdigit(ch=getchar()) && ch!='-') {}
    if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
    while (isdigit(ch=getchar())) res=res*10+ch-'0';
    return f?res:-res;
}

char ss[300048];
char s[300048];int len;

int RL[300048],maxlen[300048];

int minpos[100048];
LL hsh1[100048],hsh2[100048];
LL hsh3[100048],hsh4[100048];
LL fp1[100048],fp2[100048];
const int p=998244353;
const int MOD1=19260817,MOD2=1e9+7;

void init_hash()
{
	int i;
	fp1[0]=fp2[0]=1;
	for (i=1;i<=len;i++) fp1[i]=(fp1[i-1]*p)%MOD1,fp2[i]=(fp2[i-1]*p)%MOD2;
	for (i=1;i<=len;i++) hsh1[i]=(hsh1[i-1]*p+s[i])%MOD1,hsh2[i]=(hsh2[i-1]*p+s[i])%MOD2;
	for (i=len;i>=1;i--) hsh3[i]=(hsh3[i+1]*p+s[i])%MOD1,hsh4[i]=(hsh4[i+1]*p+s[i])%MOD2;
}

Pair gethash1(int left,int right)
{
	pair<LL,LL> res;
	res.x=((hsh1[right]-(hsh1[left-1]*fp1[right-left+1])%MOD1)%MOD1+MOD1)%MOD1;
	res.y=((hsh2[right]-(hsh2[left-1]*fp2[right-left+1])%MOD2)%MOD2+MOD2)%MOD2;
	return res;
}

Pair gethash2(int left,int right)
{
	pair<LL,LL> res;
	res.x=((hsh3[left]-(hsh3[right+1]*fp1[right-left+1])%MOD1)%MOD1+MOD1)%MOD1;
	res.y=((hsh4[left]-(hsh4[right+1]*fp2[right-left+1])%MOD2)%MOD2+MOD2)%MOD2;
	return res;
}

int main ()
{
	int i,j;
	scanf("%s",s+1);len=strlen(s+1);
	int cur=1;
	for (i=1;i<=len;i++) ss[cur++]='#',ss[cur++]=s[i];
	ss[cur]='#';
	int llen=cur,maxright=0,mpos=0;
	for (i=1;i<=llen;i++)
	{
		if (i<maxright)
			RL[i]=min(RL[2*mpos-i],maxright-i);
		else
			RL[i]=1;
		while (i-RL[i]>=1 && i+RL[i]<=llen && ss[i-RL[i]]==ss[i+RL[i]]) RL[i]++;
		if (i+RL[i]>maxright)
		{
			maxright=i+RL[i];
			mpos=i;
		}
	}
	init_hash();
	for (i=1;i<=llen;i++)
		if (ss[i]!='#') maxlen[i/2]=RL[i]-1;
	for (i=1;i<=len;i++)
	{
		int maxl=0,l=1,r=len,mid;
		while (l<=r)
		{
			mid=(l+r)>>1;
			if (gethash1(i,i+mid-1)==gethash2(len-mid+1,len))
			{
				maxl=mid;
				l=mid+1;
			}
			else
			{
				r=mid-1;
			}
		}
		if (maxl)
		{
			for (j=maxl;j>=1 && !minpos[j];j--) minpos[j]=i;
		}
	}
	int anslen=0;
	Pair ans1=mp(-1,-1),ans2=mp(-1,-1),ans3=mp(-1,-1);
	for (i=1;i<=len;i++)
	{
		if (maxlen[i]>anslen)
		{
			anslen=maxlen[i];
			ans1=ans3=mp(-1,-1);ans2=mp(i-(maxlen[i]-1)/2,i+(maxlen[i]-1)/2);
		}
		int l=1,r=len,maxl=0,mid;
		while (l<=r)
		{
			mid=(l+r)>>1;
			if (len-mid+1>i+(maxlen[i]-1)/2 && minpos[mid] && minpos[mid]+mid-1<i-(maxlen[i]-1)/2)
			{
				maxl=mid;
				l=mid+1;
			}
			else
			{
				r=mid-1;
			}
		}
		if (maxl)
		{
			if (maxl+maxl+maxlen[i]>anslen)
			{
				anslen=maxl+maxl+maxlen[i];
				ans1=mp(minpos[maxl],minpos[maxl]+maxl-1);
				ans2=mp(i-(maxlen[i]-1)/2,i+(maxlen[i]-1)/2);
				ans3=mp(len-maxl+1,len);
			}
		}
	}
	if (ans1.x==-1)
	{
		printf("1\n");
		printf("%d %d\n",ans2.x,ans2.y-ans2.x+1);
	}
	else
	{
		printf("3\n");
		printf("%d %d\n",ans1.x,ans1.y-ans1.x+1);
		printf("%d %d\n",ans2.x,ans2.y-ans2.x+1);
		printf("%d %d\n",ans3.x,ans3.y-ans3.x+1);
	}
	return 0;
}