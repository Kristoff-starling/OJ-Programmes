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

int len;
char s[1000048];

const int p1=19260817,p2=23333;
LL hsh[1000048];
LL  p[1000048];
void init_hash()
{
	int i;
	for (i=1;i<=len;i++) hsh[i]=hsh[i-1]*p1+s[i]+p2;
	p[0]=1;
	for (i=1;i<=len;i++) p[i]=p[i-1]*p1;
}
LL get_hash(int left,int right)
{
	return hsh[right]-hsh[left-1]*p[right-left+1];
}

int main ()
{
	int i,ca;
	ca=getint();
	while (ca--)
	{
		scanf("%s",s+1);
		len=strlen(s+1);
		init_hash();
		int ans=0,pos=0;
		while (pos<len/2)
		{
			int cur_len=-1;
			for (i=1;i<=len/2;i++)
				if (pos+i<=len/2 && get_hash(pos+1,pos+i)==get_hash(len-pos-i+1,len-pos))
				{
					cur_len=i;
					break;
				}
			if (cur_len==-1) break;
			ans+=2;
			pos+=cur_len;
		}
		if (pos+pos<len) ans++;
		printf("%d\n",ans);
	}
	return 0;
}
