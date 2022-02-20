class Solution:
    def isOneBitCharacter(self, bits: List[int]) -> bool:
        bits = bits[::-1]
        while len(bits) > 1:
            if bits.pop() == 1:
                bits.pop()
        if len(bits) == 1:
            return True
        else:
            return False