    #include <iostream>
    #include <vector>
    #include <queue>
    #include <unordered_set>
     
    int main() {
        int number_of_vertexes, number_of_edges, input_1, input_2, dist;
        std::cin >> number_of_vertexes >> number_of_edges;
        std::vector<std::unordered_set<int>> graph(number_of_vertexes);
        std::vector<std::vector<int>>matr(number_of_vertexes, std::vector<int>(number_of_vertexes, 10000000));
        std::vector<std::vector<int>>matr_with_seconds(number_of_vertexes, std::vector<int>(number_of_vertexes, 10000000));
        for (int i = 0; i < number_of_edges; ++i) {
            int input_1, input_2, dist;
            std::cin >> input_1 >> input_2 >> dist;
            --input_1; --input_2;
            graph[input_1].insert(input_2);
            graph[input_2].insert(input_1);
            if (matr[input_1][input_2] > dist) {
                matr_with_seconds[input_1][input_2] = matr[input_1][input_2];
                matr_with_seconds[input_2][input_1] = matr[input_2][input_1];
                matr[input_1][input_2] = dist;
                matr[input_2][input_1] = dist;
            }
            else {
                if (matr_with_seconds[input_1][input_2] > dist) {
                    matr_with_seconds[input_1][input_2] = dist;
                    matr_with_seconds[input_2][input_1] = dist;
                }
            }
        }
        std::vector<bool> checked(number_of_vertexes);
        int answer = 100000000;
        std::vector<std::queue<int>> queues(10 * number_of_vertexes);
        for (int i = 0; i < number_of_vertexes; ++i) {
            std::vector<bool> used(number_of_vertexes, false);
            queues[0].push(i);
            std::vector<int> dist(number_of_vertexes, 100000000);
            dist[i] = 0;
            for (int x = 0; x < 10 * number_of_vertexes; ++x) {
                while (!queues[x].empty()) {
                    int v = queues[x].front();
                    queues[x].pop();
                    if (used[v]) {
                        continue;
                    }
                    used[v] = true;
                    for (auto to : graph[v]) {
                        if (!used[to] && dist[to] < 100000000) {
                            answer = std::min(answer, dist[v] + dist[to] + matr[v][to]);
                        }
                        if (dist[to] > dist[v] + matr[v][to]) {
                            dist[to] = dist[v] + matr[v][to];
                            queues[dist[to]].push(to);
                        }
                    }
                }
            }
        }
        for (int i = 0; i < number_of_vertexes; ++i) {
                 for(int j =0;j<number_of_vertexes;++j){
                    answer = std::min(answer, matr[i][j]+matr_with_seconds[i][j]);
                 }
            }
     
        std::cout << answer;
    }
