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

char s[58];int n;
int dp[51][27][27][27][5];Pair pre[51][27][27][27][5];
int pos[5];

inline int myabs(int x) {return x>=0?x:-x;}

inline void update(int i,int j,int k,int m,int r1,int r2,int r3,int newp,int orip,int oriv,int val)
{
	if (r1>r2) swap(j,k),swap(r1,r2);
	if (r1>r3) swap(j,m),swap(r1,r3);
	if (r2>r3) swap(k,m),swap(r2,r3);
	if (dp[i][j][k][m][newp]>val)
	{
		dp[i][j][k][m][newp]=val;
		pre[i][j][k][m][newp]=mp(orip,oriv);
	}
}

inline void print(int pp,int cp,int s1,int s2)
{
	int i;
	if (pp<=cp)
		for (i=1;i<=cp-pp;i++) printf(">");
	else
		for (i=1;i<=pp-cp;i++) printf("<");
	if (s1<s2)
		for (i=1;i<=s2-s1;i++) printf("+");
	else
		for (i=1;i<=s1-s2;i++) printf("-");
	printf(".");
}

inline void getans(int step,int j,int k,int m,int cp)
{
	int i;
	if (step==1)
	{
		print(2,cp,0,s[step]);
		return;
	}
	int Val[5];memset(Val,-1,sizeof(Val));Val[cp]=s[step]-'a'+1;int pt=1;
	while (Val[pt]!=-1) pt++;Val[pt]=j;
	while (Val[pt]!=-1) pt++;Val[pt]=k;
	while (Val[pt]!=-1) pt++;Val[pt]=m;
	int pp=pre[step][j][k][m][cp].x;
	Val[cp]=pre[step][j][k][m][cp].y;
	if (pp==1) getans(step-1,Val[2],Val[3],Val[4],pp);
	if (pp==2) getans(step-1,Val[1],Val[3],Val[4],pp);
	if (pp==3) getans(step-1,Val[1],Val[2],Val[4],pp);
	if (pp==4) getans(step-1,Val[1],Val[2],Val[3],pp);
	print(pp,cp,(Val[cp]==0?Val[cp]:Val[cp]+96),s[step]);
}

int main ()
{
	scanf("%s",s+1);n=strlen(s+1);
	int i,j,k,m,p,cp,np;
	for (i=1;i<=n;i++)
		for (j=0;j<=26;j++)
			for (k=0;k<=26;k++)
				for (m=0;m<=26;m++)
					for (cp=1;cp<=4;cp++)
						dp[i][j][k][m][cp]=INF;
	for (cp=1;cp<=4;cp++) dp[1][0][0][0][cp]=myabs(cp-2)+s[1];
	for (i=1;i<=n-1;i++)
		for (j=0;j<=26;j++)
			for (k=0;k<=26;k++)
				for (m=0;m<=26;m++)
					for (cp=1;cp<=4;cp++)
						if (dp[i][j][k][m][cp]<INF)
						{
							pos[1]=1;if (cp==1) pos[1]=2;
							for (p=2;p<=3;p++)
							{
								pos[p]=pos[p-1]+1;
								if (pos[p]==cp) pos[p]++;
							}
							int jj,kk,mm;
							jj=(j==0?0:j+96);
							kk=(k==0?0:k+96);
							mm=(m==0?0:m+96);
							//stay
							update(i+1,j,k,m,pos[1],pos[2],pos[3],cp,cp,s[i]-'a'+1,dp[i][j][k][m][cp]+myabs(s[i+1]-s[i]));
							//to j
							update(i+1,k,m,s[i]-'a'+1,pos[2],pos[3],cp,pos[1],cp,j,dp[i][j][k][m][cp]+myabs(cp-pos[1])+myabs(s[i+1]-jj));
							//to k
							update(i+1,j,m,s[i]-'a'+1,pos[1],pos[3],cp,pos[2],cp,k,dp[i][j][k][m][cp]+myabs(cp-pos[2])+myabs(s[i+1]-kk));
							//to m
							update(i+1,j,k,s[i]-'a'+1,pos[1],pos[2],cp,pos[3],cp,m,dp[i][j][k][m][cp]+myabs(cp-pos[3])+myabs(s[i+1]-mm));
						}
	int ansj,ansk,ansm,ansp,anslen=INF;
	for (j=0;j<=26;j++)
		for (k=0;k<=26;k++)
			for (m=0;m<=26;m++)
				for (cp=1;cp<=4;cp++)
					if (dp[n][j][k][m][cp]<anslen)
					{
						anslen=dp[n][j][k][m][cp];
						ansj=j;ansk=k;ansm=m;ansp=cp;
					}
	getans(i,ansj,ansk,ansm,ansp);
	puts("");return 0;
}
