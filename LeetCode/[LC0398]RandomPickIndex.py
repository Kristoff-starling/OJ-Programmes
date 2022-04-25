class Solution:

    def __init__(self, nums: List[int]):
        self.dict = defaultdict(list)
        for i, val in enumerate(nums):
            self.dict[val].append(i)

    def pick(self, target: int) -> int:
        return choice(self.dict[target])