class Solution {
public:
    int nextGreaterElement(int n) {
        auto tmp = to_string(n);
        return next_permutation(tmp.begin(), tmp.end()) && stol(tmp) <= INT_MAX ? stol(tmp) : -1;
    }
};