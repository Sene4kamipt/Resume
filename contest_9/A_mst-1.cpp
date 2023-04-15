    #include <iostream>
    #include <vector>
    #include <algorithm>
     
    int main(){
        int number_of_vertexes, number_of_edges;
        std::cin >> number_of_vertexes >> number_of_edges;
        int answer =0;
        std::vector<int> min_edge_to_used(number_of_vertexes, 100000000);
        std::vector<std::vector<int>> graph(number_of_vertexes, std::vector<int> (number_of_vertexes, 100000000));
        std::vector<bool>used(number_of_vertexes, 0);
        for(int i =0;i<number_of_edges;++i){
            int input_vertex_1, input_vertex_2, cost;
            std::cin >> input_vertex_1 >> input_vertex_2 >> cost;
            graph[input_vertex_1 - 1][input_vertex_2 - 1] = cost;
            graph[input_vertex_2 - 1][input_vertex_1 - 1] = cost;
            if (input_vertex_2==1){
                min_edge_to_used[input_vertex_1 - 1] = cost;
            }
            else {
                if (input_vertex_1 == 1) {
                    min_edge_to_used[input_vertex_2 - 1] = cost;
                }
            }
        }
        used[0] = 1;
        for (int i=1; i<number_of_vertexes;++i){
            int min_vertex = 0;
            int min_edge_cost =10000000;
            for(int j =0;j<number_of_vertexes;++j){
                if (min_edge_to_used[j]<min_edge_cost && !used[j]){
                    min_edge_cost = min_edge_to_used[j];
                    min_vertex = j;
                }
            }
            used[min_vertex] =1;
            for(int j =0;j<number_of_vertexes;++j){
                min_edge_to_used[j] = std::min(min_edge_to_used[j], graph[j][min_vertex]);
            }
            answer +=min_edge_cost;
        }
        std::cout<<answer;
    }


