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
#define Pair pair<int,LL>
#define pb push_back
#define pf push_front
#define mp make_pair
#define LOWBIT(x) x & (-x)
using namespace std;
 
const int MOD=100003;
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

int nlen,len,k;
string ss;char s[600048];
int sa[600048],rnk[600048],tmp[600048];
char ans[600048];

bool compare_sa(int x,int y)
{
	if (rnk[x]!=rnk[y]) return rnk[x]<rnk[y];
	int tmp1=(x+k<=len?rnk[x+k]:-1),tmp2=(y+k<=len?rnk[y+k]:-1);
	return tmp1<tmp2;
}

void construct_sa()
{
	int i;
	for (i=1;i<=len;i++)
	{
		sa[i]=i;
		rnk[i]=s[i];
	}
	for (k=0;k<=len;k==0?k++:k<<=1)
	{
		sort(sa+1,sa+len+1,compare_sa);int cnt=0;
		tmp[sa[1]]=1;
		for (i=2;i<=len;i++)
		{
			tmp[sa[i]]=tmp[sa[i-1]]+(compare_sa(sa[i-1],sa[i])?1:0);
			cnt+=(tmp[sa[i]]==tmp[sa[i-1]]?0:1);
		}
		for (i=1;i<=len;i++) rnk[i]=tmp[i];
		if (cnt>=len-1) return;
	}
}

int main ()
{
	int i;
	getline(cin,ss);
	for (i=1;i<=int(ss.size());i++) s[i]=ss[i-1];
	nlen=strlen(s+1);len=(nlen<<1);
	for (i=nlen+1;i<=len;i++) s[i]=s[i-nlen];
	construct_sa();int cnt=0;
	for (i=1;i<=len && cnt<=nlen;i++)
	{
		if (!(1<=sa[i] && sa[i]<=nlen)) continue;
		printf("%c",s[sa[i]+nlen-1]);
	}
	printf("\n");
	return 0;
}
