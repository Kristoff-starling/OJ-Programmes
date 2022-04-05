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
const int INF=1e9;
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

char s[200048];
vector<int> pos[48];
int n,q;

const int p1=998244353,p2=1004535809;
const int m1=1e9+7,m2=1e9+9;
LL hsh1[48][200048],hsh2[48][200048],P1[200048],P2[200048];
inline void init_hash()
{
	int i,j;P1[0]=P2[0]=1;
	for (i=1;i<=n;i++) P1[i]=(P1[i-1]*p1)%m1,P2[i]=(P2[i-1]*p2)%m2;
	for (i=1;i<=26;i++)
		for (j=1;j<=n;j++)
		{
			hsh1[i][j]=(hsh1[i][j-1]*p1+(s[j]=='a'+i-1)*3)%m1;
			hsh2[i][j]=(hsh2[i][j-1]*p2+(s[j]=='a'+i-1)*3)%m2;
		}
}

inline LL mod1(LL x) {while (x>=m1) x-=m1;while (x<0) x+=m1;return x;}
inline LL mod2(LL x) {while (x>=m2) x-=m2;while (x<0) x+=m2;return x;}
inline LL gethash1(int type,int left,int right) {return mod1(hsh1[type][right]-(hsh1[type][left-1]*P1[right-left+1])%m1);}
inline LL gethash2(int type,int left,int right) {return mod2(hsh2[type][right]-(hsh2[type][left-1]*P2[right-left+1])%m2);}

LL val1[48],val2[48];

int main ()
{
	n=getint();q=getint();scanf("%s",s+1);
	init_hash();
	int s1,s2,len,i;
	while (q--)
	{
		s1=getint();s2=getint();len=getint();
		bool ans=true;
		memset(val1,0,sizeof(val1));memset(val2,0,sizeof(val2));
		for (i=1;i<=26;i++) val1[i]=gethash1(i,s1,s1+len-1),val2[i]=gethash1(i,s2,s2+len-1);
		sort(val1+1,val1+27);sort(val2+1,val2+27);
		for (i=1;i<=26;i++) if (val1[i]!=val2[i]) ans=false;
		memset(val1,0,sizeof(val1));memset(val2,0,sizeof(val2));
		for (i=1;i<=26;i++) val1[i]=gethash2(i,s1,s1+len-1),val2[i]=gethash2(i,s2,s2+len-1);
		sort(val1+1,val1+27);sort(val2+1,val2+27);
		for (i=1;i<=26;i++) if (val1[i]!=val2[i]) ans=false;
		if (ans) puts("YES"); else puts("NO");
	}
	return 0;
}
