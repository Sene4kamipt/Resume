    #include<iostream>
    #include<vector>
     
    int find_comp(int n, int m, int i, int j){
        int answer;
        if((i + j) % 2 == 0){
            answer = 1;
        } else {
            answer = 2;
        }
        return answer;
    }
     
    bool augment(int v, std::vector<std::vector<int>>& graph, std::vector<bool>& used, std::vector<int>& match){
        if(used[v]){
            return false;
        }
        used[v] = true;
        for(int to : graph[v]){
            if(match[to] == -1 || augment(match[to], graph, used, match)){
                match[to] = v;
                return true;
            }
        }
        return false;
    }
     
     
     
    int main(){
        int n, m;
        int double_cost, one_cost;
        int missed_tiles = 0;
        std::cin>>n>>m>>double_cost>>one_cost;
        std::vector<std::vector<int>> graph_1_to_2((m*n + 1)/2);
        std::vector<std::vector<bool>> bridge(n, std::vector<bool>(m, false));
        std::vector<std::vector<int>> numbers (n, std::vector<int> (m, 0));
        for(int i = 0; i < n; ++i){
            for(int j = 0; j < m; ++j){
                if(i == 0 && (j == 0 || j == 1)){
                    continue;
                }
                if(m == 1 && i == 1 && j == 0){
                    continue;
                }
                if(m == 1){
                    numbers[i][j] = numbers[i-2][j] + 1;
                    continue;
                }
                if(j == 0){
                    numbers[i][j] = numbers[i-1][m-2] + 1;
                    continue;
                }
                if(j == 1){
                    numbers[i][j] = numbers[i-1][m-1] + 1;
                    continue;
                }
                numbers[i][j] = numbers[i][j-2] + 1;
            }
        }
        char c;
        for(int i = 0; i < n; ++i){
            for(int j = 0; j < m; ++j){
                std::cin>>c;
                if(c == '*'){
                    bridge[i][j] = true;
                    ++missed_tiles;
                }
            }
        }
        if(double_cost > one_cost * 2){
            std::cout<<one_cost * missed_tiles;
            return 0;
        }
        for(int i = 0; i < n; ++i){
            for(int j = 0; j < m; ++j){
                if(!bridge[i][j]){
                    continue;
                }
                if((i + j) % 2 != 0){ // it is second component
                    continue;
                }
                if(i != 0 && bridge[i-1][j]){
                    graph_1_to_2[numbers[i][j]].push_back(numbers[i-1][j]);
                }
                if(i != n-1 && bridge[i+1][j]){
                    graph_1_to_2[numbers[i][j]].push_back(numbers[i+1][j]);
                }
                if(j != 0 && bridge[i][j-1]){
                    graph_1_to_2[numbers[i][j]].push_back(numbers[i][j-1]);
                }
                if(j != m-1 && bridge[i][j+1]){
                    graph_1_to_2[numbers[i][j]].push_back(numbers[i][j+1]);
                }
            }
        }
        int first_size = (n*m + 1)/2;
        int second_size = n*m - first_size;
        std::vector<bool> used (first_size, false);
        std::vector<int> match(second_size, -1);
        for(int i = 0; i < first_size; ++i){
            if(augment(i, graph_1_to_2, used, match)){
                used = std::vector<bool> (first_size, false);
            }
        }
        int answer = 0;
        for(int i = 0; i < second_size; ++i){
            if(match[i] != -1){
                ++answer;
            }
        }
        answer = answer * double_cost + (missed_tiles - answer * 2) * one_cost;
        std::cout<<answer;
    }


