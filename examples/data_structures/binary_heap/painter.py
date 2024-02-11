from graphviz import Digraph

def paint_binary_heap(tree: list):
    dot = Digraph()

    size = len(tree)
    for i in range(size):
        dot.node(name=str(i), label=str(tree[i]))
        if 2 * i + 1 < size:
            dot.edge(str(i), str(2 * i + 1))
        if 2 * i + 2 < size:
            dot.edge(str(i), str(2 * i + 2))

    dot.render('binary_heap', format='png', view=True)

def main():
    # tree = "34 30 29 27 25 17 16 19 22 24".split()
    tree = [34, 30, 29, 27, 25, 17, 16, 19, 22, 24]
    paint_binary_heap(tree)

if __name__ == '__main__':
    main()