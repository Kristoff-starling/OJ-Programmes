#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=a;i<=b;i++)
using namespace std;

char s[100048];int n;

bool check(int x)
{
    if (s[x]=='1' && s[x+1]=='1' && s[x+2]=='4' && s[x+3]=='5' && s[x+4]=='1' && s[x+5]=='4') return true;
    return false;
}

int main ()
{
    int ca;scanf("%d",&ca);
    while (ca--)
    {
        scanf("%s",s+1);n=strlen(s+1);
        bool f=false;
        rep(i,1,n-5) if (check(i)) {f=true;break;}
        if (f) puts("AAAAAA"); else puts("Abuchulaile");
    }
    return 0;
}