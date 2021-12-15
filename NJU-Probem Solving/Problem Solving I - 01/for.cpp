#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=a;i<=b;i++)
#define REP(i,a,b) for (int i=a;i>=b;i--)
using namespace std;

const int MAXN=100;

int n,a[MAXN+48];

int main ()
{
    scanf("%d",&n);rep(i,1,n) scanf("%d",a+i);
    if (!n) return 0;
    REP(i,n,2) printf("%d ",a[i]);printf("%d\n",a[1]);
    return 0;
}