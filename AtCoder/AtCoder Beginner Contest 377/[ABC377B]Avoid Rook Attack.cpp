#include <iostream>
#include <string>
using namespace std;

int cntx[8], cnty[8];

int main ()
{
    string s;
    for (int i = 0; i < 8; i++)
    {
        cin >> s;
        for (int j = 0; j < 8; j++)
            if (s[j] == '#')
            {
                cntx[i]++;
                cnty[j]++;
            }
    }
    int ans = 0;
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            if (cntx[i] == 0 && cnty[j] == 0)
                ans++;
    cout << ans << "\n";
    return 0;
}