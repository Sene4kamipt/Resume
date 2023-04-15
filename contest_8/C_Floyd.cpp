#include <iostream>
#include <vector>
#include <algorithm>
int main()
{
    int n;
    std::cin >> n;
    std::vector<std::vector<long long>> graph(n, std::vector<long long>(n, 1000000000000));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            std::cin >> graph[i][j];
        }
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            for (int k = 0; k < n; ++k) {
                graph[j][k] = std::min(graph[j][k], graph[j][i] + graph[i][k]);
            }
        }
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            std::cout<<graph[i][j]<<" ";
        }
        std::cout << '\n';
    }
}
