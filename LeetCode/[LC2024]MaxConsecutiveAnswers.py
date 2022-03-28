class Solution:
    def maxConsecutiveAnswers(self, answerKey: str, k: int) -> int:
        l, cntT, cntF, ans, dic = 0, 0, 0, 0, defaultdict(int)
        for r, ch in enumerate(answerKey):
            dic[ch] += 1
            while min(dic['T'], dic['F']) > k:
                dic[answerKey[l]] -= 1
                l += 1
            ans = max(ans, r - l + 1)
        return ans