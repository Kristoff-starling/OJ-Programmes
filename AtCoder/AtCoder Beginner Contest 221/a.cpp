#include <bits/stdc++.h>
using namespace std;

int main ()
{
    int B,A;cin>>A>>B;A-=B;
    int ans=1;while (A--) ans*=32;
    cout<<ans<<endl;return 0;
}