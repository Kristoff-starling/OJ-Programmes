#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=(a);i<=(b);i++)
using namespace std;

int n,a[100],b[100];

int main ()
{
    int ca;scanf("%d",&ca);
    while (ca--)
    {
        scanf("%d",&n);string s;
        rep(i,1,n) cin>>s,a[i]=s[int(s.size())-1]-'0';
        rep(i,1,n) cin>>s,b[i]=s[int(s.size())-1]-'0';
        if (a[n]<=2) puts("NO");
        else
        {
            bool f=true;
            rep(i,1,n)
                if (!(a[i]<=2 && b[i]>=3 || a[i]>=3 && b[i]<=2)) f=false;
            puts(f?"YES":"NO");
        }
    }
    return 0;
}