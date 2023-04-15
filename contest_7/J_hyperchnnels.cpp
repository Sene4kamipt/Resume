include <vector>
#include <iostream>
 
struct edge
{
    int vertex;
    bool used;
};
 
void euler(int v, std::vector<std::vector<edge>> &graph, std::vector<int>& answer) {
    for (int i = 0; i < graph[v].size(); ++i) {
        if (!graph[v][i].used) {
            graph[v][i].used = true;
            euler(graph[v][i].vertex, graph, answer);
        }
    }
    answer.push_back(v + 1);
}
 
int main()
{
    int number_of_vertexes, beginning_vertex;
    bool way;
    std::cin >> number_of_vertexes >> beginning_vertex;
    --beginning_vertex;
    std::vector<std::vector<edge>> graph(number_of_vertexes);
    for (int i = 0; i < number_of_vertexes; ++i) {
        for (int j = 0; j < number_of_vertexes; ++j) {
            std::cin >> way;
            if ((i != j) && (!way)) {
                graph[i].push_back(edge{ j,0 });
            }
        }
    }
    std::vector<int> answer;
    euler(beginning_vertex, graph, answer);
    for (int i = 1; i < answer.size(); ++i) {
        std::cout << answer[answer.size()-i] << " " << answer[answer.size()-1-i] << '\n';
    }
}
