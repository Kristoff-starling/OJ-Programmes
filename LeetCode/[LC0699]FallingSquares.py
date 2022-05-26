class Solution:
    def fallingSquares(self, positions: List[List[int]]) -> List[int]:
        def overlap(l1, r1, l2, r2) -> bool:
            if l1 > l2: l1, r1, l2, r2 = l2, r2, l1, r1
            if r1 <= l2: return False
            return True
        
        n = len(positions); h = [0] * n
        for i, (left, sidelength) in enumerate(positions):
            right, h[i] = left + sidelength, sidelength
            for j in range(i):
                left1, right1 = positions[j][0], positions[j][0] + positions[j][1]
                if overlap(left, right, left1, right1): h[i] = max(h[i], h[j] + sidelength)
        for i in range(1, n): h[i] = max(h[i], h[i-1])
        return h