#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=a;i<=b;i++)
#define REP(i,a,b) for (int i=a;i>=b;i--)
using namespace std;

int n;
int a[1048],b[1048];

void print(int l1,int r1,int l2,int r2)
{
    if (l1>r1 || l2>r2) return;
    int rt=a[l1];
    int pos=l2;while (b[pos]!=rt) pos++;
    int leftsz=pos-l2;
    print(l1+1,l1+leftsz,l2,pos-1);
    print(l1+leftsz+1,r1,pos+1,r2);
    printf("%d ",rt);
}

int main ()
{
    scanf("%d",&n);rep(i,1,n) scanf("%d",a+i);rep(i,1,n) scanf("%d",b+i);
    print(1,n,1,n);puts("");return 0;
}