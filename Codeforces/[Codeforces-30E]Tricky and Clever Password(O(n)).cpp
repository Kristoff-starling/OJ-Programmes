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

int len,slen;
char s[300048],ss[300048];
int RL[300048],maxright,pos,maxlen[300048],mlen[300048],minpos[300048];
int fail[300048];
int f[300048];

void getfail()
{
	int k=-1,j=0;
	fail[0]=-1;
	while (j<=slen)
	{
		if (k==-1 || ss[j+1]==ss[k+1])
			fail[++j]=++k;
		else
			k=fail[k];
	}
}

void getRL()
{
	memset(ss,'\0',sizeof(ss));
	int i,cur=1;
	for (i=1;i<=len;i++)
	{
		ss[cur++]='#';
		ss[cur++]=s[i];
	}
	ss[cur]='#';slen=cur;
	maxright=pos=0;
	for (i=1;i<=slen;i++)
	{
		if (i<maxright)
			RL[i]=min(maxright-i,RL[2*pos-i]);
		else
			RL[i]=1;
		while (i-RL[i]>=1 && i+RL[i]<=slen && ss[i-RL[i]]==ss[i+RL[i]]) RL[i]++;
		if (i+RL[i]>maxright)
		{
			maxright=i+RL[i];
			pos=i;
		}
	}
}

int main ()
{
	//freopen ("30e.in","r",stdin);
	//freopen ("30e.out","w",stdout);
	int i,j;
	scanf("%s",s+1);len=strlen(s+1);
	for (i=1;i<=len;i++) ss[i]=s[len-i+1];
	ss[len+1]='$';
	for (i=len+2;i<=len+2+len-1;i++) ss[i]=s[i-len-1];
	slen=strlen(ss+1);
	getfail();
	for (i=len+2;i<=slen;i++) mlen[i-len-1-fail[i]+1]=max(mlen[i-len-1-fail[i]+1],fail[i]);
	for (i=1;i<=len;i++)
		for (j=mlen[i];j>=1 && !minpos[j];j--)
			minpos[j]=i;
	getRL();
	//return 0;
	for (i=1;i<=slen;i++) if (ss[i]!='#') maxlen[i/2]=RL[i]-1;
	//cout<<"*"<<endl;
	for (i=len;i>=1;i--)
		if (minpos[i])
			for (j=minpos[i]+i;j<=len && !f[j];j++)
				f[j]=i;
	//return 0;
	Pair ans1=mp(-1,-1),ans2=mp(-1,-1),ans3=mp(-1,-1);int anslen=0;
	for (i=1;i<=len;i++)
	{
		int ll=i-(maxlen[i]-1)/2,rr=i+(maxlen[i]-1)/2;
		int add=min(len-rr,f[ll]);
		if (maxlen[i]+add+add>anslen)
		{
			anslen=maxlen[i]+add+add;
			ans2=mp(i-(maxlen[i]-1)/2,maxlen[i]);
			if (add)
			{
				ans1=mp(minpos[add],add);
				ans3=mp(len-add+1,add);
			}
			else
				ans1=ans3=mp(-1,-1);
		}
	}
	if (ans1.x==-1)
	{
		printf("1\n");
		printf("%d %d\n",ans2.x,ans2.y);
	}
	else
	{
		printf("3\n");
		printf("%d %d\n",ans1.x,ans1.y);
		printf("%d %d\n",ans2.x,ans2.y);
		printf("%d %d\n",ans3.x,ans3.y);
	}
	return 0;
}