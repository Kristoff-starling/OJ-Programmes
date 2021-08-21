#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=a;i<=b;i++)
#define REP(i,a,b) for (int i=a;i>=b;i--)
using namespace std;

const int MAXN=1e5;

char s[MAXN+48],t[MAXN+48];
int n,m;

int main ()
{
    int ca;scanf("%d",&ca);
    while (ca--)
    {
        scanf("%s%s",s+1,t+1);n=strlen(s+1);m=strlen(t+1);
        int pos=n,j=m;
        while (pos>=1 && j>=1)
        {
            while (pos>=1 && s[pos]!=t[j]) pos-=2;
            if (pos<=0) break;
            pos--;j--;
        }
        if (j) puts("NO"); else puts("YES");
    }
    return 0;
}