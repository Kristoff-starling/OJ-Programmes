class Solution:
    def maximumWealth(self, accounts: List[List[int]]) -> int:
        return max([sum(accounts[i]) for i in range(0, len(accounts))])