#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=a;i<=b;i++)
using namespace std;

const int MAXN=2e5;

int a[MAXN+48],b[MAXN+48];

bool cmp(int x,int y) {return a[x]>a[y];}

int main ()
{
    int n;scanf("%d",&n);rep(i,1,n) scanf("%d",a+i),b[i]=i;
    sort(b+1,b+n+1,cmp);
    printf("%d\n",b[2]);
    return 0;
}