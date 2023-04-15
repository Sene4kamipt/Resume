    #include <vector>
    #include <iostream>
     
    int main()
    {
        int number_of_vertexes, number_of_edges;
        std::cin >> number_of_vertexes >> number_of_edges;
        std::vector<std::vector<bool>> incidency(number_of_vertexes, std::vector<bool>(number_of_edges, false));
        int vertex_1, vertex_2;
        for (int i = 0; i < number_of_edges; ++i) {
            std::cin >> vertex_1 >> vertex_2;
            incidency[vertex_1 - 1][i] = true;
            incidency[vertex_2 - 1][i] = true;
        }
        for (int i = 0; i < number_of_vertexes; ++i) {
            for (int j = 0; j < number_of_edges; ++j) {
                std::cout << incidency[i][j] << " ";
            }
            std::cout << '\n';
        }
    }
