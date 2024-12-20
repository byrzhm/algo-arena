#include <bits/stdc++.h>

struct TreeNode {
    int val;
    int left, right;
};

bool
isSymmetric(const std::vector<TreeNode>& tree, int index, int& nodeNum)
{
    int l, r;
    std::deque<int> dq;
    if (tree[index].left != 0 && tree[index].right != 0) {
        nodeNum = 1;
        dq.push_front(tree[index].left);
        dq.push_back(tree[index].right);
        while (!dq.empty() && nodeNum != -1) {
            if (tree[dq.front()].val != tree[dq.back()].val)
                nodeNum = -1;
            else {
                nodeNum += 2;
                l = dq.front();
                r = dq.back();
                dq.pop_front();
                dq.pop_back();

                if (tree[l].left != 0 && tree[l].right != 0) {
                    if (tree[r].left == 0 || tree[r].right == 0) {
                        nodeNum = -1;
                        break;
                    }
                    dq.push_front(tree[l].right);
                    dq.push_front(tree[l].left);
                    dq.push_back(tree[r].left);
                    dq.push_back(tree[r].right);
                } else if (tree[l].left != 0 && tree[l].right == 0) {
                    if (tree[r].left != 0 || tree[r].right == 0) {
                        nodeNum = -1;
                        break;
                    }
                    dq.push_front(tree[l].left);
                    dq.push_back(tree[r].right);
                } else if (tree[l].left == 0 && tree[l].right != 0) {
                    if (tree[r].left == 0 || tree[r].right != 0) {
                        nodeNum = -1;
                        break;
                    }
                    dq.push_front(tree[l].right);
                    dq.push_back(tree[r].left);
                } else if (tree[l].left == 0 && tree[l].right == 0) {
                    if (tree[r].left != 0 || tree[r].right != 0) {
                        nodeNum = -1;
                        break;
                    }
                }
            }
        }

    }
    else if (tree[index].left == 0 && tree[index].right == 0)
        nodeNum = 1;
    else
        nodeNum = -1;

    // if (nodeNum > 0)
    //     printf("index = %d, tree[index].left = %d, tree[index].right = %d\n",
    //      index, tree[index].left, tree[index].right);
    return nodeNum > 0;
}

int
main()
{
    int n, l, r, idx, nodeNum, max;
    std::queue<int> q;

    std::cin >> n;
    std::vector<TreeNode> tree(n+1);

    for (int i = 1; i <= n; i++)
        std::cin >> tree[i].val;

    for (int i = 1; i <= n; i++) {
        std::cin >> l >> r;
        tree[i].left  = (l != -1 ? l : 0);
        tree[i].right = (r != -1 ? r : 0);
    }

    max = INT_MIN;
    q.push(1);
    while (!q.empty()) {
        idx = q.front(); q.pop();
        if (isSymmetric(tree, idx, nodeNum)) {
            if (nodeNum > max) {
                max = nodeNum;
            }
            continue;
        }

        if (tree[idx].left != 0)
            q.push(tree[idx].left);
        if (tree[idx].right != 0)
            q.push(tree[idx].right);
    }

    std::cout << max << std::endl;

    exit(0);
}