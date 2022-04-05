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

const int MOD=1e9+9;
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

const int T=100;
const double Tmin=1e-8;
const double delta=0.99;
double y;

inline double mypow(double x,int y)
{
	double res=1;
	while (y--) res*=x;
	return res;
}

inline double calc_function(double x) {return 6*mypow(x,7)+8*mypow(x,6)+7*mypow(x,3)+5*mypow(x,2)-x*y;}

int main ()
{
	srand(1968);
	int ca;ca=getint();double ans;
	double t,sol,curres,newsol,newres;int i;
	while (ca--)
	{
		scanf("%lf",&y);
		int Ti=5;ans=LINF;
		while (Ti--)
		{
			sol=double(rand())/RAND_MAX*100;curres=calc_function(sol);ans=min(ans,curres);t=T;
			while (t>Tmin)
			{
				int ti=5;
				while (ti--)
				{
					newsol=sol+mypow(-1,rand()%2)*t;
					if (newsol+eps>0 && newsol<100+eps)
					{
						newres=calc_function(newsol);
						ans=min(ans,newres);
						if (newres-curres<-eps)
						{
							curres=newres;
							sol=newsol;
						}
						else
						{
							double p=1.0/(1+exp(newres-curres)/t);
							if (double(rand())/RAND_MAX<p)
							{
								curres=newres;
								sol=newsol;
							}
						}
					}
				}
				t*=delta;
			}
		}
		printf("%.4lf\n",ans);
	}
	return 0;
}
