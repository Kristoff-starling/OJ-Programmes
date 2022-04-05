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

const int MOD=998244353;
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

int len;
char s[2000048];

namespace Hash
{
	const int p=19260817;
	LL hsh[2000048],pw[2000048];
	inline void init()
	{
		int i;pw[0]=1;
		for (i=1;i<=len*2;i++)
		{
			pw[i]=pw[i-1]*p;
			hsh[i]=hsh[i-1]*p+s[i];
		}
	}
	inline LL gethash(int left,int right)
	{
		return hsh[right]-hsh[left-1]*pw[right-left+1];
	}
}

bool ans[1000048];

int main ()
{
	int i,ca,lastpos,curpos,left,right,curlen;ca=getint();
	while (ca--)
	{
		scanf("%s",s+1);len=strlen(s+1);
		for (i=len+1;i<=len*2;i++) s[i]=s[i-len];
		Hash::init();memset(ans,false,sizeof(ans));
		for (i=1;i<=len && s[i]!=s[i+1];i++) {}
		if (i>len)
		{
			for (curlen=2;curlen<=len;curlen++)
				if (Hash::gethash(1,len-curlen+1)!=Hash::gethash(curlen,len)) ans[len-curlen]=true;
			for (i=0;i<=len-2;i++) if (ans[i]) printf("1"); else printf("0");
			printf("1\n");continue;
		}
		lastpos=i;curpos=i+1;
		while (curpos<=i+len-1)
		{
			while (curpos<=i+len-1 && s[curpos]!=s[curpos+1]) curpos++;
			left=lastpos+1;right=curpos;
			for (curlen=2;curlen<=right-left+1;curlen++)
				if (Hash::gethash(left,right-curlen+1)!=Hash::gethash(left+curlen-1,right))
					ans[len-curlen]=true;
			lastpos=curpos;curpos++;
		}
		for (i=0;i<=len-2;i++) if (ans[i]) printf("1"); else printf("0");
		printf("1\n");
	}
	return 0;
}
