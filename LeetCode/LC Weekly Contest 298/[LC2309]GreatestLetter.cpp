class Solution {
    int cnt1[48],cnt2[48];
public:
    string greatestLetter(string s) {
        for (int i = 0; i < int(s.size()); i++)
            if ('a' <= s[i] && s[i] <= 'z') cnt1[s[i]-'a'+1]++; else cnt2[s[i]-'A'+1]++;
        for (int i = 26; i >= 1; i--) if (cnt1[i] >= 1 && cnt2[i] >= 1) return string(1, 'A' + i - 1);
        return "";
    }
};