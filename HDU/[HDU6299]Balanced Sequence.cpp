#include <bits/stdc++.h>
using namespace std;

#define LL long long
#define LB long double
#define ull unsigned long long
#define x first
#define y second
#define pb push_back
#define pf push_front
#define mp make_pair
#define Pair pair<int,int>
#define pLL pair<LL,LL>
#define pii pair<double,double>
#define LOWBIT(x) x & (-x)

const int INF=2e9;
const LL LINF=2e16;
const int magic=348;
const int MOD=998244353;
const double eps=1e-10;
const double pi=acos(-1);

inline int getint()
{
	bool f;char ch;int res;
	while (!isdigit(ch=getchar()) && ch!='-') {}
	if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
	while (isdigit(ch=getchar())) res=res*10+ch-'0';
	return f?res:-res;
}

const int MAXN=2e5;

int n;
struct node
{
	int l,r,val;
}a[MAXN+48],A[MAXN+48],B[MAXN+48];

char s[MAXN+48];

inline bool cmpa(node x,node y) {return x.r<y.r;}
inline bool cmpb(node x,node y) {return -x.r+x.l-y.r>-y.r+y.l-x.r;}

int main ()
{
	int i,j,ca,len;ca=getint();
	int ans;
	while (ca--)
	{
		n=getint();
		for (i=1;i<=n;i++)
		{
			scanf("%s",s+1);len=strlen(s+1);
			a[i].l=a[i].r=a[i].val=0;
			for (j=1;j<=len;j++)
				if (s[j]==')')
				{
					if (a[i].l) a[i].l--,a[i].val++; else a[i].r++;
				}
				else
				{
					a[i].l++;
				}
		}
			ans=0;
			for (i=1;i<=n;i++) ans+=a[i].val;
			int ta=0,tb=0;
			for (i=1;i<=n;i++)
				if (a[i].l>a[i].r) A[++ta]=a[i]; else B[++tb]=a[i];
			sort(A+1,A+ta+1,cmpa);
			sort(B+1,B+tb+1,cmpb);
			for (i=1;i<=ta;i++) a[i]=A[i];
			for (i=1;i<=tb;i++) a[ta+i]=B[i];
			int num=0;
			for (i=1;i<=n;i++)
			{
				ans+=min(num,a[i].r);
				num=max(0,num-a[i].r);
				num+=a[i].l;
			}
			printf("%d\n",ans*2);
	}
	return 0;
}
