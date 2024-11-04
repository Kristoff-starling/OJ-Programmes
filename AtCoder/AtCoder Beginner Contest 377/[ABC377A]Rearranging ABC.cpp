#include <iostream>
#include <string>

int cnt[26];

int main ()
{
    std::string s;
    std::cin >> s;
    if (int(s.size()) == 3)
    {
        for (int i = 0; i <= 2; i++)
            cnt[s[i] - 'A']++;
        if (cnt[0] == 1 && cnt[1] == 1 && cnt[2] == 1)
        {
            std::cout << "Yes" << "\n";
            return 0;
        }
    }
    std::cout << "No" << "\n";
    return 0;
}