from graphviz import Digraph

def draw(nums: list):
    checkNums(nums)

    dot = Digraph()

    for i, num in enumerate(nums):
        dot.node(str(i), label=str(i))
        dot.edge(str(i), str(num))

    dot.render('floyd', format='png', view=True)


    
def checkNums(nums: list):
    n = len(nums) - 1
    assert n >= 1, "len(nums) should >= 2"
    for num in nums:
        # python support chained comparison
        assert 1 <= num <= n, "Every integer should be in the range [1, n] inclusive"


if __name__ == "__main__":
    # nums = [1, 3, 4, 2, 2]
    nums = [3,1,3,4,2]
    draw(nums)
