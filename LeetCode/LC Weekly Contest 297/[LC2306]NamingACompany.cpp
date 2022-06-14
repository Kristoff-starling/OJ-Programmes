class Solution {
    vector<string> name[27];
    unordered_set<string> table;
    int cnt[48][48];
    bool valid[100048][30]; int tot;
public:
    long long distinctNames(vector<string>& ideas) {
        for (auto idea : ideas)
        {
            name[idea[0] - 'a' + 1].push_back(idea);
            table.insert(idea);
        }
        tot = 0;
        for (int i = 1; i <= 26; i++)
        {
            for (auto s : name[i])
            {
                ++tot;
                for (int j = 1; j <= 26; j++)
                {
                    s[0] = 'a' + j - 1;
                    if (table.find(s) == table.end()) valid[tot][j] = true; else valid[tot][j] = false;
                    if (valid[tot][j]) cnt[i][j]++;
                }
            }
        }
        long long ans = 0; tot = 0;
        for (int i = 1; i <= 26; i++)
            for (auto s : name[i])
            {
                ++tot;
                for (int j = 1; j <= 26; j++)
                    if (valid[tot][j]) ans += cnt[j][s[0] - 'a' + 1];
            }
        return ans;
    }
};