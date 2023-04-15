    #include<iostream>
    #include<vector>
    #include<string>
    #include<queue>
    #include <algorithm>>
     
    class currency {
    public:
        int from;
        float rate;
        float comiss;
     
        currency(int b, float rba, float cba) {
            from = b;
            rate = rba;
            comiss = cba;
        }
    };
     
    void Floyd_Bell(long long start, long long number_of_vertexes, float start_amount, std::vector<std::vector<currency>>& graph) {
        std::vector<std::vector<float>> possible_amount(2, std::vector<float>(number_of_vertexes + 1, 0));
        possible_amount[0][start] = start_amount;
        float new_summ;
        for (long long k = 1; k <= number_of_vertexes; ++k) {
            for (long long v = 0; v < number_of_vertexes; ++v) {
                possible_amount[1][v] = std::max(possible_amount[1][v], possible_amount[0][v]);
                for (int i = 0; i < graph[v].size();++i) {
                    if (possible_amount[0][graph[v][i].from] != 0) {
                        new_summ = (possible_amount[0][graph[v][i].from] - graph[v][i].comiss) * graph[v][i].rate;
                        if (new_summ > 0.0f) {
                            possible_amount[1][v] = std::max(possible_amount[1][v], new_summ);
                        }
                    }
                }
            }
            std::swap(possible_amount[0], possible_amount[1]);
        }
        for (int i = 0; i < number_of_vertexes; ++i) {
            if (possible_amount[0][i] > possible_amount[1][i]) {
                std::cout << "YES";
                return;
            }
        }
        std::cout << "NO";
        return;
    }
     
    int main() {
        int number_of_vertexes, number_of_edges, start_curr;
        float start_amount;
        std::cin >> number_of_vertexes >> number_of_edges >> start_curr >> start_amount;
        std::vector<std::vector<currency>> graph(number_of_vertexes);
        int curr_1, curr_2;
        float rab, cab, rba, cba;
        start_curr -= 1;
        for (int i = 0; i < number_of_edges; ++i) {
            std::cin >> curr_1 >> curr_2 >> rab >> cab >> rba >> cba;
            --curr_1; --curr_2;
            graph[curr_1].push_back(currency{ curr_2, rba, cba });
            graph[curr_2].push_back(currency{ curr_1, rab, cab });
        }
        Floyd_Bell(start_curr, number_of_vertexes, start_amount, graph);
    }
