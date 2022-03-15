class Solution:
    def findRestaurant(self, list1: List[str], list2: List[str]) -> List[str]:
        common = set(list1) & set(list2)
        sum_index = {item : list1.index(item) + list2.index(item) for item in common}
        return [item for item in common if sum_index[item] == min(sum_index.values())]