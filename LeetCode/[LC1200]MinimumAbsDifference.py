import numpy as np

class Solution:
    def minimumAbsDifference(self, arr: List[int]) -> List[List[int]]:
        arr.sort()
        delta = min(np.array(arr)[1:] - np.array(arr)[:-1])
        return [[arr[i], arr[i+1]] for i in range(len(arr)-1) if arr[i+1] - arr[i] == delta]