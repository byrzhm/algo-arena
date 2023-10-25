// Binary Tree Traversals:
// Given the preorder sequence and inorder sequence of a certain binary tree.
// Try to find out its postorder sequence.
#include <bits/stdc++.h>

struct Node {
    int left, right;
    Node(int left = 0, int right = 0) : left(left), right(right) {}
};

void 
build(int root, std::vector<Node>& tree, std::vector<int>& preseq, int prestart, int prelen, std::vector<int>& inseq, int instart, int inlen)
{
    int inidx = instart;
    int leftlen, rightlen;
    while (inidx - instart < inlen && inseq[inidx] != root)
        inidx++;
    assert(inseq[inidx] == root);
    leftlen = inidx - instart;
    rightlen = inlen - (inidx - instart) - 1;

    if (leftlen != 0) {
        tree[root].left = preseq[prestart + 1];
        build(tree[root].left, tree,
            preseq, prestart + 1, leftlen, inseq, instart, leftlen);
    }

    if (rightlen != 0) {
        tree[root].right = preseq[prestart + 1 + leftlen];
        build(tree[root].right, tree, 
            preseq, prestart + 1 + leftlen, leftlen, inseq, instart + 1 + leftlen, rightlen);
    }

}

std::vector<Node>
creat(std::vector<int>& preseq, std::vector<int>& inseq)
{
    std::vector<Node> tree(preseq.size() + 1);

    int root = preseq[0];
    build(root, tree, preseq, 0, preseq.size(), inseq, 0, inseq.size());
    
    return std::move(tree);
}

int postidx;
void 
postorder(int root, const std::vector<Node>& tree, std::vector<int>& postseq)
{
    if (root != 0) {
        postorder(tree[root].left, tree, postseq);
        postorder(tree[root].right, tree, postseq);
        postseq[postidx++] = root;
    }
}

int
main()
{
    int n;
    while (std::cin >> n /* scanf("%d", &n) == 1 */) {
        std::vector<int> preseq(n), inseq(n), postseq(n);
        for (int i = 0; i < n; i++) std::cin >> preseq[i];
        for (int i = 0; i < n; i++) std::cin >> inseq[i];

        std::vector<Node> tree = creat(preseq, inseq);
        postidx = 0;
        postorder(preseq[0], tree, postseq);

        for (int i = 0; i < n; i++)
            std::cout << postseq[i] << (i == n - 1 ? '\n' : ' ');
    }
    
    exit(0);
}