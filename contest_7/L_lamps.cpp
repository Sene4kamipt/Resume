    #include <vector>
    #include <iostream>
    #include <algorithm>
    struct lamp
    {
        bool switched;
        int switcher_1;
        int switcher_2;
    };
     
    void dfs(int v, std::vector<std::vector<int>>& graph, std::vector<int>& colors, std::vector<int>& number_of_component, int& counter) {
        colors[v] = 1;
        number_of_component[v] = counter;
        for (int i = 0; i < graph[v].size(); ++i) {
            if (colors[graph[v][i]] >= 1) {
                continue;
            }
            else {
                dfs(graph[v][i], graph, colors, number_of_component, counter);
            }
        }
        colors[v] = 2;
        return;
    }
     
    int main()
    {
        int number_of_lamps, number_of_switchers, number_switcher_lamp, input_switcher;
        std::cin >> number_of_lamps >> number_of_switchers;
        std::vector<lamp> lamps(number_of_lamps);
        bool input_lamp;
        for (int i = 0; i < number_of_lamps; ++i) {
            std::cin >> input_lamp;
            lamps[i] = lamp{ (input_lamp==1?1:0),-1,-1 };
        }
        std::vector<std::vector<int>> graph(number_of_switchers * 2);
        for (int i = 0; i < number_of_switchers; ++i) {
            std::cin >> number_switcher_lamp;
            for (int j = 0; j < number_switcher_lamp; ++j) {
                std::cin >> input_switcher;
                --input_switcher;
                if (lamps[input_switcher].switcher_1 == -1) {
                    lamps[input_switcher].switcher_1 = i;
                }
                else {
                    lamps[input_switcher].switcher_2 = i;
                    if (lamps[input_switcher].switched == 1) {
                        graph[lamps[input_switcher].switcher_1 * 2].push_back(lamps[input_switcher].switcher_2 * 2);
                        graph[lamps[input_switcher].switcher_2 * 2].push_back(lamps[input_switcher].switcher_1 * 2);
                        graph[lamps[input_switcher].switcher_1 * 2+1].push_back(lamps[input_switcher].switcher_2 * 2+1);
                        graph[lamps[input_switcher].switcher_2 * 2+1].push_back(lamps[input_switcher].switcher_1 * 2+1);
                    }
                    else {
                        graph[lamps[input_switcher].switcher_1 * 2].push_back(lamps[input_switcher].switcher_2 * 2+1);
                        graph[lamps[input_switcher].switcher_2 * 2+1].push_back(lamps[input_switcher].switcher_1 * 2);
                        graph[lamps[input_switcher].switcher_1 * 2 + 1].push_back(lamps[input_switcher].switcher_2 * 2);
                        graph[lamps[input_switcher].switcher_2 * 2].push_back(lamps[input_switcher].switcher_1 * 2 + 1);
                    }
                }
            }
        }
        std::vector<int>colors(number_of_switchers*2, 0);
        std::vector<int> number_of_component(number_of_switchers*2, 0);
        int counter = 1;
        for (int i = 0; i < number_of_switchers*2; ++i) {
            if (colors[i] == 0) {
                dfs(i, graph, colors, number_of_component, counter);
                ++counter;
            }
        }
        bool flag = 0;
        for (int i = 0; i < number_of_switchers; ++i) {
            if (number_of_component[2*i] == number_of_component[2*i + 1]) {
                flag = 1;
                break;
            }
        }
        if (flag) {
            std::cout << "NO";
        }
        else {
            std::cout << "YES";
        }
        //for (int i = 0; i < number_of_switchers*2; ++i) {
            //std::cout << number_of_kss[i] << " ";
        //}
        //for (int i = 0; i < number_of_switchers*2; ++i) {
            //std::cout << i << " ";
            //for (int j = 0; j < graph[i].size(); ++j) {
                //std::cout << graph[i][j] << " ";
            //}
            //std::cout << '\n';
        //}
        
    }
