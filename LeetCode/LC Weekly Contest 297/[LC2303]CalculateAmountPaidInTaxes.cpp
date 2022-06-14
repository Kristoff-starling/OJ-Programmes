class Solution {
public:
    double calculateTax(vector<vector<int>>& brackets, int income) {
        double ans = 0;
        for (int i = 0; i < int(brackets.size()) && income > 0; i++)
        {
            int lim = brackets[i][0], p = brackets[i][1];
            if (i != 0) lim -= brackets[i-1][0];
            int need = min(lim, income);
            ans += (double)need * 1.0 * p / 100;
            income -= need;
        }
        return ans;
    }
};