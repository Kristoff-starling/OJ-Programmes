#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=(a);i<=(b);++i)
using namespace std;

const int MAXN=1e5;

int n;
int X[MAXN+48],Y[MAXN+48];

int main ()
{
    scanf("%d",&n);
    rep(i,1,n) scanf("%d%d",X+i,Y+i);
    sort(X+1,X+n+1);sort(Y+1,Y+n+1);
    printf("%d %d\n",X[(n+1)>>1],Y[(n+1)>>1]);
    return 0;
}