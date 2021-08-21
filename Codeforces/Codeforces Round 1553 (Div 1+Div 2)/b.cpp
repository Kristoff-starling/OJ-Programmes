#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=a;i<=b;i++)
#define REP(i,a,b) for (int i=a;i>=b;i--)
using namespace std;

char s[1048],t[1048];int lens,lent;

int main ()
{
    int ca;scanf("%d",&ca);
    while (ca--)
    {
        scanf("%s%s",s+1,t+1);lens=strlen(s+1);lent=strlen(t+1);
        bool f=false;
        rep(i,1,lens) rep(j,1,lens-i+1)
            if (j<=lent && lent-j<=i+j-2)
            {
                bool ff=true;
                rep(k,i,i+j-1) if (s[k]!=t[k-i+1]) {ff=false;break;}
                if (!ff) continue;
                for (int k=i+j-2,pos=j+1;pos<=lent;pos++,k--) if (s[k]!=t[pos]) {ff=false;break;}
                if (ff) f=true;
            }
        if (f) puts("YES"); else puts("NO");
    }
    return 0;
}