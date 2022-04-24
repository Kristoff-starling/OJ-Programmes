class Solution:
    def binaryGap(self, n: int) -> int:
        ones = [i for i in range(31) if n>>i&1]
        return max([ones[i+1] - ones[i] for i in range(len(ones)-1)], default=0)