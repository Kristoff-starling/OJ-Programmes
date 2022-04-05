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

int n;
int a,A,b,B,m,M;

inline int myabs(int x) {return x>=0?x:-x;}

inline bool check_invalid()
{
	if (myabs(a-b)%2==0) return false;
	if (myabs(A-B)%2==0) return false;
	return true;
}

inline bool Contain(int l1,int r1,int l2,int r2)
{
	if (l1>l2 && r1<r2) return true;
	if (l1<l2 && r1>r2) return true;
	return false;
}

inline bool Away(int l1,int r1,int l2,int r2)
{
	if (l1>r1) swap(l1,r1);
	if (l2>r2) swap(l2,r2);
	return r1<l2 || r2<l1;
}

int main ()
{
	n=getint();
	if (n==2)
	{
		printf("? 1\n");fflush(stdout);scanf("%d",&a);
		printf("? 2\n");fflush(stdout);scanf("%d",&A);
		if (a==A) printf("! 1\n"); else printf("! -1\n");
		return 0;
	}
	int la=1,lA=n/2;
	printf("? 1\n");fflush(stdout);scanf("%d",&a);
	printf("? %d\n",lA);fflush(stdout);scanf("%d",&A);
	printf("? %d\n",la+n/2);fflush(stdout);scanf("%d",&b);
	printf("? %d\n",lA+n/2);fflush(stdout);scanf("%d",&B);
	if (a==b)
	{
		printf("! 1\n");
		return 0;
	}
	if (A==B)
	{
		printf("! %d\n",lA);
		return 0;
	}
	if (check_invalid()) {printf("! -1\n");return 0;}
	while (lA-la>1)
	{
		int mid=(la+lA)>>1,to=mid+n/2;
		printf("? %d\n",mid);fflush(stdout);scanf("%d",&m);
		printf("? %d\n",to);fflush(stdout);scanf("%d",&M);
		if (m==M)
		{
			printf("! %d\n",mid);
			return 0;
		}
		if (Contain(a,m,b,M)) {lA=mid;A=m;B=M;continue;}
		if (Contain(m,A,M,B)) {la=mid;a=m;b=M;continue;}
		if (Away(a,m,b,M)) {la=mid;a=m;b=M;continue;}
		if (Away(m,A,M,B)) {lA=mid;A=m;B=M;continue;}
	}
	if (a==b) {printf("! %d\n",la);return 0;}
	if (A==B) {printf("! %d\n",lA);return 0;}
	printf("! -1\n");return 0;
}
