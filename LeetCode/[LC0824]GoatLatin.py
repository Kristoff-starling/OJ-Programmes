class Solution:
    def toGoatLatin(self, sentence: str) -> str:
        words, goat, vowel = sentence.split(' '), [], "aeiouAEIOU"
        for cnt, word in enumerate(words):
            if word[0] in vowel:
                goat.append(word + "ma" + (cnt+1) * "a")
            else:
                goat.append(word[1:] + word[0] + "ma" + (cnt+1) * "a")
        return ' '.join(goat)