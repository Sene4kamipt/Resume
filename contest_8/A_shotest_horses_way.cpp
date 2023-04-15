    #include <vector>
    #include <string>
    #include <iostream>
    #include <map>
    #include <queue>
     
    std::map <char, int> convertion;
    std::map <int, std::string> back_convertion1;
    std::map <int, std::string> back_convertion2;
     
    void Construction(std::vector<std::vector<int>>& graph) {
        for (int i = 0; i < 64; ++i) {
            if ((i % 8 > 0) && (i / 8 > 1)) {
                graph[i].push_back(i - 17);
                graph[i - 17].push_back(i);
            }
            if ((i % 8 > 1) && (i / 8 > 0)) {
                graph[i].push_back(i - 10);
                graph[i - 10].push_back(i);
            }
            if ((i % 8 < 7) && (i / 8 > 1)) {
                graph[i].push_back(i - 15);
                graph[i - 15].push_back(i);
            }
            if ((i % 8 < 6) && (i / 8 > 0)) {
                graph[i].push_back(i - 6);
                graph[i - 6].push_back(i);
            }
        }
    }
     
    int convert(std::string& str) {
        return convertion[str[0]] + convertion[str[1]] * 8;
    }
     
    std::string back_convert(int n) {
        return back_convertion1[n % 8] + back_convertion2[n / 8];
    }
     
    void bfs(int vertex1, int vertex2, std::vector<std::vector<int>>& graph, std::vector<int>& where_came_from) {
        std::queue <int> qu;
        int curr_vertex = vertex1;
        qu.push(vertex1);
        while (curr_vertex != vertex2) {
            //std::cout << curr_vertex << " ";
            curr_vertex = qu.front();
            qu.pop();
            for (int i = 0; i < graph[curr_vertex].size(); ++i) {
                if (where_came_from[graph[curr_vertex][i]] == -1) {
                    qu.push(graph[curr_vertex][i]);
                    where_came_from[graph[curr_vertex][i]] = curr_vertex;
                }
            }
        }
    }
     
    int main()
    {
        convertion['a'] = 0; convertion['b'] = 1; convertion['c'] = 2; convertion['d'] = 3; convertion['e'] = 4; convertion['f'] = 5; convertion['g'] = 6; convertion['h'] = 7;
        convertion['1'] = 0; convertion['2'] = 1; convertion['3'] = 2; convertion['4'] = 3; convertion['5'] = 4; convertion['6'] = 5; convertion['7'] = 6; convertion['8'] = 7;
        back_convertion1[0] = "a"; back_convertion1[1] = "b"; back_convertion1[2] = "c"; back_convertion1[3] = "d"; back_convertion1[4] = "e"; back_convertion1[5] = "f"; back_convertion1[6] = "g"; back_convertion1[7] = "h";
        back_convertion2[0] = "1"; back_convertion2[1] = "2"; back_convertion2[2] = "3"; back_convertion2[3] = "4"; back_convertion2[4] = "5"; back_convertion2[5] = "6"; back_convertion2[6] = "7"; back_convertion2[7] = "8";
        std::vector<std::vector<int>> graph(64, std::vector<int>(0, 1));
        Construction(graph);
        std::string input;
        int vertex_1, vertex_2;
        std::cin >> input;
        vertex_1 = convert(input);
        std::cin >> input;
        vertex_2 = convert(input);
        std::vector<int> where_came_from(64, -1);
        //std::cout << "1";
        bfs(vertex_1, vertex_2, graph, where_came_from);
        int curr_vertex=vertex_2;
        std::vector<int> ans;
        while (curr_vertex != vertex_1) {
            ans.push_back(curr_vertex);
            curr_vertex = where_came_from[curr_vertex];
        }
        std::cout << back_convert(vertex_1);
        for (int i = 0; i < ans.size(); ++i) {
            std::cout << '\n' <<back_convert(ans[ans.size() - 1 - i]);
        }
    }
