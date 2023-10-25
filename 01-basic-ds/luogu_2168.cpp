// k叉哈夫曼树
#include <bits/stdc++.h>

struct Node
{
    int64_t weight;
    int64_t height;
    Node(int64_t weight = 0, int64_t height = 0) :
        weight(weight), height(height) {}
};

bool operator>(const Node& l, const Node& r) {
    return (l.weight == r.weight ? 
        l.height > r.height : l.weight > r.weight);
}


int
main()
{
    int n, k;
    int64_t min;
    std::cin >> n >> k;
    std::vector<Node> nodes(n);
    for (int i = 0; i < n; i++)
        std::cin >> nodes[i].weight;

    std::priority_queue<Node, std::vector<Node>, std::greater<Node>> 
        q(nodes.begin(), nodes.end());

    // 补 0
    while ((q.size() - 1) % (k - 1) != 0)
        q.push(Node());

    min = 0;
    while (q.size() > 1) {
        int64_t sum = 0;
        int64_t h = 0;
        // 合并
        for (int i = 0; i < k; i++) {
            sum += q.top().weight;
            h = std::max(q.top().height, h);
            q.pop();
        }
        q.push(Node(sum, h + 1));
        min += sum;
    }

    std::cout << min << std::endl;
    std::cout << q.top().height << std::endl;
    exit(0);
}