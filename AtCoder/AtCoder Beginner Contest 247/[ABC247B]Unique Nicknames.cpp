#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=(a);i<=(b);i++)
using namespace std;

int n;
string s[200][2];

int main ()
{
    cin>>n;
    rep(i,1,n) cin>>s[i][0]>>s[i][1];
    bool f=true;
    rep(i,1,n)
    {
        bool f1=true,f2=true;
        rep(j,1,n) rep(k,0,1)
        {
            if (i!=j && s[j][k]==s[i][0]) f1=false;
            if (i!=j && s[j][k]==s[i][1]) f2=false;
        }
        f&=(f1|f2);
    }
    puts(f?"Yes":"No");
    return 0;
}