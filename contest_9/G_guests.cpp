#include<iostream>
#include<vector>
 
std::pair<int64_t, std::vector<int64_t>> SV(std::vector<std::vector<int64_t>>& graph){
 
    std::pair<int64_t, std::vector<int64_t>> answer;
    int64_t n = graph.size();
 
//    for(int64_t i = 0; i < n; ++i){
//        for(int64_t j = 0; j < graph[i].size(); ++j){
//            if(graph[i][j] == i){
//                std::vector<int64_t> k;
//                return std::make_pair(0, k);
//            }
//        }
//    }
 
    if(n == 2){
        std::vector<int64_t> ans;
        ans.push_back(0);
        int64_t num = graph[0].size();
        return std::make_pair(num, ans);
    }
 
    std::vector<int64_t> A;
    A.push_back(0);
    std::vector<int64_t> connection(n, 0);
    std::vector<bool> used (n, false);
    connection[0] = -1;
    used[0] = true;
    for(int64_t i: graph[0]){
        ++connection[i];
    }
    for(int64_t i = 1; i < n; ++i){
        int64_t max_connected = 0;
        for(int64_t j = 0; j < n; ++j){
            if(connection[max_connected] < connection[j]){
                max_connected = j;
            }
        }
        A.push_back(max_connected);
        used[max_connected] = true;
        connection[max_connected] = -1;
        for(int64_t j: graph[max_connected]){
            if(used[j]){
                continue;
            }
            ++connection[j];
        }
    }
    int64_t max_cur_flow = graph[A[n-1]].size();
    std::vector<int64_t> ans;
    ans.push_back(A[n-1]);
    auto first_answer = std::make_pair(max_cur_flow, ans);
 
    //теперь нужно как то склеить 2 последие вершины
    //и сделать новый граф
    int64_t first = A[n-2];
    int64_t second = A[n-1];
    if(first > second){
        std::swap(first, second);
    }
    std::vector<std::vector<int64_t>> new_graph(n-1);
    for(int64_t i = 0; i < first; ++i){
        for(int64_t j: graph[i]){
            if(j == i){
                continue;
            }
            if(j < second){
                new_graph[i].push_back(j);
            }
            else if(j == second){
                new_graph[i].push_back(first);
            }
            else {
                new_graph[i].push_back(j - 1);
            }
        }
    }
    for(int64_t j: graph[first]){
        if(j == first){
            continue;
        }
        if(j < second){
            new_graph[first].push_back(j);
        }
        else if(j == second){
            continue;
        }
        else {
            new_graph[first].push_back(j - 1);
        }
    }
    for(int64_t i = first + 1; i < second; ++i){
        for(int64_t j: graph[i]){
            if(i == j){
                continue;
            }
            if(j < second){
                new_graph[i].push_back(j);
            }
            else if(j == second){
                new_graph[i].push_back(first);
            }
            else {
                new_graph[i].push_back(j - 1);
            }
        }
    }
    for(int64_t j: graph[second]){
        if(j == first || j == second){
            continue;
        }
        else if(j < second){
            new_graph[first].push_back(j);
        }
        else {
            new_graph[first].push_back(j - 1);
        }
    }
    for(int64_t i = second + 1; i < n; ++i){
        for(int64_t j: graph[i]){
            if(i == j){
                continue;
            }
            if(j < second){
                new_graph[i-1].push_back(j);
            }
            else if(j == second){
                new_graph[i-1].push_back(first);
            }
            else {
                new_graph[i-1].push_back(j - 1);
            }
        }
    }
 
    auto second_answer = SV(new_graph);
    bool flag_1 = false;
    bool flag_2 = false;
    for(int64_t j = 0; j < second_answer.second.size(); ++j){
        if(second_answer.second[j] >= second){
            ++second_answer.second[j];
        }
        if(second_answer.second[j] == first){
            flag_1 = true;
        }
        if(second_answer.second[j] == second){
            flag_2 = true;
        }
    }
    if(flag_1 && !flag_2){
        second_answer.second.push_back(second);
    }
 
    if(first_answer.first < second_answer.first){
        answer = first_answer;
    } else {
        answer = second_answer;
    }
    return answer;
}
 
int main(){
    int64_t n;
    char k;
    std::cin>>n;
    //n = 5;
    std::vector<std::vector<int64_t>> graph (n);
//    graph = {{0,0,1,1,1}, {0,0,0,1,1}, {1,0,0,0,0}, {1,1,0,0,0}, {1,1,0,0,0}};
    for(int64_t i =0 ; i < n; ++i){
        for(int64_t j = 0; j < n; ++j) {
            std::cin >> k;
            if(k == '1'){
                graph[i].push_back(j);
            }
        }
    }
    auto answer = SV(graph);
 
    std::vector<bool> used (n, false);
    for(auto j: answer.second){
        std::cout<<j + 1<<' ';
        used[j] = true;
    } std::cout<<'\n';
    for(int64_t i = 0; i < n; ++i){
        if(!used[i]){
            std::cout<<i + 1<<' ';
        }
    }
}
