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

char s[100048];
int n;

int cnt[100048][27];
bool isgray[100048][21];
LL cost[100048],score[100048][27];
LL ans=0;

const int p=19260817;
const int MOD1=998244353,MOD2=1e9+7;
LL hsh1[100048],hsh2[100048],fp1[100048],fp2[100048];
int len[20];

void init_hash()
{
	int i;
	fp1[0]=1;
	for (i=1;i<=n;i++) 
	{
		hsh1[i]=hsh1[i-1]*p+s[i];
		fp1[i]=fp1[i-1]*p;
	}
}

LL gethash(int left,int right)
{
	return hsh1[right]-hsh1[left-1]*fp1[right-left+1];
}

bool issame(int s1,int s2,int len)
{
	if (s1>s2) swap(s1,s2);
	if (s2+len-1>n) return false;
	return gethash(s1,s1+len-1)==gethash(s2,s2+len-1);
}

int common(int s1,int s2)
{
	int i,res=0;
	for (i=16;i>=0;i--)
		if (issame(s1,s2,res+(1<<i))) res+=(1<<i);
	return res;
}

void calc_cnt()
{
	int i,j;
	for (i=1;i<=n;i++)
		for (j=1;j<=26;j++)
			cnt[i][j]=cnt[i-1][j]+(s[i]-'a'+1==j?1:0);
}

void calc_gray()
{
	int i,clen,center;LL tmp;
	for (clen=1;clen<=16;clen++)
		for (i=1;i<=n;i++)
			if (i+len[clen]-1<=n)
			{
				center=i+len[clen-1];
				if (clen==1 || (isgray[i][clen-1] && isgray[center+1][clen-1] && issame(i,center+1,len[clen-1]) && cnt[i+len[clen]-1][s[center]-'a'+1]-cnt[center][s[center]-'a'+1]==0))
				{
					tmp=(long long)len[clen]*(long long)len[clen];
					isgray[i][clen]=true;
					cost[i]+=tmp;cost[i+len[clen]]-=tmp;
					ans+=tmp;
				}
			}
	for (i=2;i<=n;i++) cost[i]+=cost[i-1];
}

void calc_score(int starter,int clen)
{
	if (clen==1)
	{
		for (int i=1;i<=26;i++) score[starter][i]++;
		return;
	}
	int center=starter+len[clen-1];
	int s1=starter,s2=center+1;
	LL tmp=(long long)len[clen]*(long long)len[clen];
	//change center
	if (isgray[s1][clen-1] && isgray[s2][clen-1] && issame(s1,s2,len[clen-1]))
	{
		for (int i=1;i<=26;i++)
			if (cnt[starter+len[clen]-1][i]-cnt[center][i]==0)
				score[center][i]+=tmp;
	}
	int ll=common(s1,s2);
	if (s1+ll>=center) return;
	int d1=s1+ll,d2=s2+ll;
	int ll2=common(d1+1,d2+1);
	if (d1+1+ll2<center) return;
	//change left
	if (isgray[s2][clen-1] && cnt[starter+len[clen]-1][s[center]-'a'+1]-cnt[center][s[center]-'a'+1]==0)
		score[d1][s[d2]-'a'+1]+=tmp;
	//change right
	if (isgray[s1][clen-1] && cnt[s1+len[clen-1]-1][s[center]-'a'+1]-cnt[starter-1][s[center]-'a'+1]==0)
		score[d2][s[d1]-'a'+1]+=tmp;
}

int main ()
{
	int i,j,clen;
	scanf("%s",s+1);n=strlen(s+1);
	init_hash();
	len[1]=1;for (i=2;i<=20;i++) len[i]=len[i-1]*2+1;
	calc_cnt();
	calc_gray();
	for (i=1;i<=n;i++)
		for (clen=1;clen<=16;clen++)
			if (i+len[clen]-1<=n) calc_score(i,clen);
	LL delta=0;
	for (i=1;i<=n;i++)
		for (j=1;j<=26;j++)
			delta=max(delta,score[i][j]-cost[i]);
	ans+=delta;
	cout<<ans<<endl;
	return 0;
}