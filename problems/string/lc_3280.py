class Solution:
    def convertDateToBinary(self, date: str) -> str:
        splits = date.split(sep="-")
        for i, split in enumerate(splits):
            splits[i] = format(int(split), "b")
        return "-".join(splits)

print(Solution().convertDateToBinary('1900-01-01'))