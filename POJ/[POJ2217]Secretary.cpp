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

int len,k;
int sa[200048],rank[200048],tmp[200048],lcp[200048];
string str;char s[200048];

bool compare_sa(int x,int y)
{
	if (rank[x]!=rank[y]) return rank[x]<rank[y];
	int tmp1=x+k<=len?rank[x+k]:-1,tmp2=y+k<=len?rank[y+k]:-1;
	return tmp1<tmp2;
}

void construct_sa()
{
	int i,cnt;
	for (i=1;i<=len;i++)
	{
		sa[i]=i;
		rank[i]=s[i];
	}
	for (k=0;k<=len;k==0?k++:k*=2)
	{
		sort(sa+1,sa+len+1,compare_sa);
		tmp[sa[1]]=1;cnt=0;
		for (i=2;i<=len;i++)
		{
			tmp[sa[i]]=tmp[sa[i-1]]+(compare_sa(sa[i-1],sa[i])?1:0);
			cnt+=(tmp[sa[i]]==tmp[sa[i-1]]?0:1);
		}
		for (i=1;i<=len;i++) rank[i]=tmp[i];
		if (cnt>=len-1) break;
	}
}

void construct_lcp()
{
	int i,j,h=0;
	for (i=1;i<=len;i++) rank[sa[i]]=i;
	for (i=1;i<=len;i++)
	{
		j=sa[rank[i]-1];
		if (h) h--;
		while (i+h<=len && j+h<=len && s[i+h]==s[j+h]) h++;
		lcp[rank[i]-1]=h;
	}
}

int main ()
{
	int i,ca,ff,ss;
	ca=getint();
	while (ca--)
	{
		memset(s,'\0',sizeof(s));
		getline(cin,str);
		for (i=0;i<=str.size()-1;i++) s[i+1]=str[i];
		len=strlen(s+1);
		ff=len;
		s[len+1]='#';len++;ss=len+1;
		getline(cin,str);
		for (i=0;i<=str.size()-1;i++) s[len+i+1]=str[i];
		len=strlen(s+1);
		construct_sa();
		construct_lcp();
		int ans=-1;
		for (i=1;i<=len-1;i++)
			if ((sa[i]<=ff && sa[i+1]>=ss) || (sa[i]>=ss && sa[i+1]<=ff))
				ans=max(ans,lcp[i]);
		printf("Nejdelsi spolecny retezec ma delku %d.\n",ans);
	}
	return 0;
}
