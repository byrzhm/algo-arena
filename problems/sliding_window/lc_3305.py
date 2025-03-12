from collections import defaultdict


class Solution:
    def countOfSubstrings(self, word: str, k: int) -> int:
        vowels = set(["a", "e", "i", "o", "u"])
        n = len(word)

        def count(m: int) -> int:
            res = 0
            vowel_cnt = 0
            consonant_cnt = 0
            cnt = defaultdict(int)
            j = 0
            for i in range(n):
                while j < n and (consonant_cnt < m or vowel_cnt < 5):
                    x = word[j]
                    cnt[x] += 1
                    if x in vowels and cnt[x] == 1:
                        vowel_cnt += 1
                    elif x not in vowels:
                        consonant_cnt += 1
                    j += 1
                if consonant_cnt >= m and vowel_cnt == 5:
                    res += n - j + 1

                x = word[i]
                cnt[x] -= 1
                if x in vowels and cnt[x] == 0:
                    vowel_cnt -= 1
                elif x not in vowels:
                    consonant_cnt -= 1
            return res

        return count(k) - count(k + 1)


# word = "ieaouqqieaouqq"
word = "iqeaouqi"
k = 2

print(Solution().countOfSubstrings(word, k))
