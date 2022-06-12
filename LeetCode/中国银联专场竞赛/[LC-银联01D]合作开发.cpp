#define mp make_pair
#define x first
#define y second
#define ull unsigned long long
const int MOD = 1e9 + 7;
class Solution {
    int n;
    unordered_map<ull, int> m1, m2, m3, m4;
public:
    ull c1(int x) {return x;}
    ull c2(int x, int y) {return x * 1048 + y;}
    ull c3(int x, int y, int z) {return (ull)x * 1048 * 1048 + y * 1048 + z;}
    ull c4(int x, int y, int z, int w) {return (ull)x * 1048 * 1048 * 1048 + (ull)y * 1048 * 1048 + z * 1048 + w;}
    void doit(vector<int> people, int delta)
    {
        int sz = int(people.size());
        if (sz >= 1)
            for (int i = 0; i < sz; i++) m1[c1(people[i])] += delta;
        if (sz >= 2)
            for (int i = 0; i < sz; i++)
                for (int j = i + 1; j < sz; j++)
                    m2[c2(people[i], people[j])] += delta;
        if (sz >= 3)
            for (int i = 0; i < sz; i++)
                for (int j = i + 1; j < sz; j++)
                    for (int k = j + 1; k < sz; k++)
                        m3[c3(people[i], people[j], people[k])] += delta;
        if (sz >= 4)
            m4[c4(people[0], people[1], people[2], people[3])] += delta;
    }
    int coopDevelop(vector<vector<int>>& skills) {
        n = int(skills.size());
        sort(skills.begin(), skills.end(), [&](vector<int> &v1, vector<int> &v2) {return int(v1.size()) < int(v2.size());});
        for (auto people : skills) doit(people, 1);
        int ans = 0, i = 0;
        for (auto people: skills)
        {
            i++;
            int sz = int(people.size());
            if (sz == 1) ans = (ans + n - i + 1 - m1[c1(people[0])]) % MOD, m1[c1(people[0])]--;
            if (sz == 2) ans = (ans + n - i + 1 - m2[c2(people[0], people[1])]) % MOD, m2[c2(people[0], people[1])]--;
            if (sz == 3) ans = (ans + n - i + 1 - m3[c3(people[0], people[1], people[2])]) % MOD, m3[c3(people[0], people[1], people[2])]--;
            if (sz == 4) ans = (ans + n - i + 1 - m4[c4(people[0], people[1], people[2], people[3])]) % MOD, m4[c4(people[0], people[1], people[2], people[3])]--;
        }
        return ans;
    }
};