class Solution:
    def uniqueMorseRepresentations(self, words: List[str]) -> int:
        alphabet = "abcdefghijklmnopqrstuvwxyz"
        morse = [".-","-...","-.-.","-..",".","..-.","--.","....","..",".---","-.-",".-..","--","-.","---",".--.","--.-",".-.","...","-","..-","...-",".--","-..-","-.--","--.."]
        dic, ans = {}, 0
        for word in words:
            for i, ch in enumerate(alphabet):
                word = word.replace(ch, morse[i])
            if not word in dic:
                ans += 1
                dic[word] = 1
        return ans