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

char s[3][48];int l1,l2;
LL Len[3][48][48],hsh[3][48][48];
const int p=19260817,MO=998244353;

inline LL mod(LL x) {while (x>=MO) x-=MO; while (x<0) x+=MO;return x;}
inline LL mul(LL x) {return x%MO;}

inline LL quick_pow(LL x,LL y)
{
	x%=MO;LL res=1;
	while (y)
	{
		if (y&1) res=mul(res*x),y--;
		x=mul(x*x);y>>=1;
	}
	return res;
}

inline LL calc_len(int type,int left,int right)
{
	int cnt=0,i;
	for (i=left;i<=right;i++)
	{
		if (s[type][i]=='[') cnt++;
		if (s[type][i]==']') cnt--;
		if (cnt<0) return -1;
	}
	if (cnt) return -1;
	if (isdigit(s[type][left])) return -1;
	if (s[type][right]==']') return -1;
	if (type==1 && right!=l1 && isdigit(s[type][right+1])) return -1;
	if (type==2 && right!=l2 && isdigit(s[type][right+1])) return -1;
	if (left==right) return 1;
	if (isalpha(s[type][left])) return Len[type][left+1][right]+1;
	cnt=0;
	for (i=left;;i++)
	{
		if (s[type][i]=='[') cnt++;
		if (s[type][i]==']') cnt--;
		if (!cnt) break;
	}
	LL res=Len[type][left+1][i-1];
	LL num=0;
	for (i=i+1;i<=right && isdigit(s[type][i]);i++) num=num*10+s[type][i]-'0';
	res*=num;
	if (i<=right) res+=Len[type][i][right];
	return res;
}

inline LL calc_hash(int type,int left,int right)
{
	if (left==right) return s[type][left];
	if (isalpha(s[type][left]))
	{
		LL nl=Len[type][left+1][right];
		return mod(mul(quick_pow(p,nl)*s[type][left])+hsh[type][left+1][right]);
	}
	int cnt=0;int i;
	for (i=left;;i++)
	{
		if (s[type][i]=='[') cnt++;
		if (s[type][i]==']') cnt--;
		if (!cnt) break;
	}
	LL res1=hsh[type][left+1][i-1],len1=Len[type][left+1][i-1];
	LL num=0;
	for (i=i+1;i<=right && isdigit(s[type][i]);i++) num=num*10+s[type][i]-'0';
	res1=mul(mod(quick_pow(p,num*len1)-1)*res1);
	LL div=mod(quick_pow(p,len1)-1);div=quick_pow(div,MO-2);
	res1=mul(res1*div);
	if (i<=right)
	{
		LL res2=hsh[type][i][right],len2=Len[type][i][right];
		res1=mod(mul(quick_pow(p,len2)*res1)+hsh[type][i][right]);
	}
	return res1;
}

inline LL gethash(int type,int left,int right,LL pos)
{
	if (Len[type][left][right]<pos) return -1;
	if (left==right) return hsh[type][left][right];
	int pre=left-1,pt=left;
	do
	{
		while (Len[type][left][pt]==-1) pt++;
		if (Len[type][left][pt]<pos) pre=pt,pt++;
	}
	while (Len[type][left][pt]<pos);
	LL Le=pos;if (pre>=left) Le-=Len[type][left][pre];
	LL res=0;if (pre>=left) res=hsh[type][left][pre];
	if (pt==pre+1)
	{
		res=mod(mul(res*p)+s[type][pt]);
		return res;
	}
	int ll=pre+2,rr=pt;
	while (s[type][rr]!=']') rr--;rr--;
	LL tl=Len[type][ll][rr],tt=(Le-1)/tl;
	LL h=hsh[type][ll][rr];
	h=mul(h*mod(quick_pow(p,tt*tl)-1));
	LL div=mod(quick_pow(p,tl)-1);div=quick_pow(div,MO-2);
	h=mul(h*div);
	tl*=tt;
	res=mod(mul(res*quick_pow(p,tl))+h);
	LL res1=gethash(type,ll,rr,Le-tl);
	res=mod(mul(res*quick_pow(p,Le-tl))+res1);
	return res;
}

int main ()
{
	int ca,tt=0,i,j;ca=getint();
	while (ca--)
	{
		scanf("%s",s[1]+1);l1=strlen(s[1]+1);
		for (i=1;i<=l1;i++)
			for (j=1;j<=l1-i+1;j++)			
				Len[1][j][j+i-1]=calc_len(1,j,j+i-1);
		for (i=1;i<=l1;i++)
			for (j=1;j<=l1-i+1;j++)
				if (Len[1][j][j+i-1]!=-1) hsh[1][j][j+i-1]=calc_hash(1,j,j+i-1);
		scanf("%s",s[2]+1);l2=strlen(s[2]+1);
		for (i=1;i<=l2;i++)
			for (j=1;j<=l2-i+1;j++)
				Len[2][j][j+i-1]=calc_len(2,j,j+i-1);
		for (i=1;i<=l2;i++)
			for (j=1;j<=l2-i+1;j++)
				if (Len[2][j][j+i-1]!=-1) hsh[2][j][j+i-1]=calc_hash(2,j,j+i-1);
		printf("Case #%d: ",++tt);
		if (hsh[1][1][l1]==hsh[2][1][l2]) {printf("YES\n");continue;}
		printf("NO ");
		LL l=1,r=max(Len[1][1][l1],Len[2][1][l2]),mid,ans;
		while (l<=r)
		{
			mid=(l+r)>>1;
			if (gethash(1,1,l1,mid)!=gethash(2,1,l2,mid)) ans=mid,r=mid-1; else l=mid+1;
		}
		printf("%lld\n",ans);
	}
	return 0;
}
