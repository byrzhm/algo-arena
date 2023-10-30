#include <bits/stdc++.h>

struct Node
{
    int symbol;
    int parent;
    int left;
    int right;
} node[27];

#define A2I(x) ((x) == '*' ? 0 : (x) - 'a' + 1)
#define C2A(x) ((x) == '*' ? 0 : (x))

void
preorder(int i)
{
    if (node[i].symbol != 0) {
        std::cout << static_cast<char>(node[i].symbol);
        preorder(node[i].left);
        preorder(node[i].right);
    }
}

int
main()
{
    int n, i;
    std::string input;
    std::cin >> n;

    for (int i = 0; i < n; i++) {
        std::cin >> input;
        node[A2I(input[0])].symbol  = C2A(input[0]);
        node[A2I(input[0])].left    = A2I(input[1]);
        node[A2I(input[0])].right   = A2I(input[2]);

        node[A2I(input[1])].parent  = A2I(input[0]);
        node[A2I(input[1])].symbol  = C2A(input[1]);

        node[A2I(input[2])].parent  = A2I(input[0]);
        node[A2I(input[2])].symbol  = C2A(input[2]);
    }
    node[0].symbol = 0;

    i = 1;
    while ((node[i].symbol != 0) && (node[i].parent != 0)) {
        i = node[i].parent;
    }
    
    preorder(i);
    std::cout << std::endl;

    exit(0);
}
