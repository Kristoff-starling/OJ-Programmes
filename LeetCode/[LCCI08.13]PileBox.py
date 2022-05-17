class Solution:
    def pileBox(self, box: List[List[int]]) -> int:
        box, n = sorted(box), len(box)
        dp = [0] * n; dp[0] = box[0][2]
        for i in range(1, n):
            dp[i] = box[i][2]
            for j in range(i):
                if box[i][0] > box[j][0] and box[i][1] > box[j][1] and box[i][2] > box[j][2]:
                    dp[i] = max(dp[i], dp[j] + box[i][2])
        return max(dp)