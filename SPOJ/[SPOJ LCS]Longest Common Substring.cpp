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
	int next[30];
	int val,fail;
	inline void init()
	{
		fail=val=0;
		for (int i=1;i<=26;i++) next[i]=0;
	}
}SAM[800048];int tot=0;
int root,last;

char s1[250048],s2[250048];
int len1,len2;

inline void extend(int w)
{
	int p=last,np=++tot;SAM[np].init();
	SAM[np].val=SAM[p].val+1;
	while (p && !SAM[p].next[w]) SAM[p].next[w]=np,p=SAM[p].fail;
	if (!p)
		{SAM[np].fail=root;}
	else
	{
		int q=SAM[p].next[w];
		if (SAM[p].val+1==SAM[q].val)
			{SAM[np].fail=q;}
		else
		{
			int nq=++tot;SAM[nq].init();
			memcpy(SAM[nq].next,SAM[q].next,sizeof(SAM[q].next));
			SAM[nq].val=SAM[p].val+1;SAM[nq].fail=SAM[q].fail;
			SAM[q].fail=nq;SAM[np].fail=nq;
			while (p && SAM[p].next[w]==q) SAM[p].next[w]=nq,p=SAM[p].fail;
		}
	}
	last=np;
}			

int main ()
{
	int i;
	scanf("%s%s",s1+1,s2+1);
	len1=strlen(s1+1);len2=strlen(s2+1);
	root=last=++tot;SAM[root].init();
	for (i=1;i<=len1;i++)
		extend(s1[i]-'a'+1);
	int len=0,ans=0,cur=root;
	for (i=1;i<=len2;i++)
	{
		int w=s2[i]-'a'+1;
		if (SAM[cur].next[w])
		{
			cur=SAM[cur].next[w];
			len++;
		}
		else
		{
			while (cur && !SAM[cur].next[w]) cur=SAM[cur].fail;
			if (!cur)
				len=0,cur=root;
			else
			{
				len=SAM[cur].val+1;
				cur=SAM[cur].next[w];
			}
		}
		ans=max(ans,len);
	}
	printf("%d\n",ans);
	return 0;
}

