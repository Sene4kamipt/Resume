    #include<iostream>
    #include<vector>
    #include<queue>
    #include<unordered_set>
    #include <cmath>;
     
    long long reverse(size_t size, long long s, int start, int finish) {
        long long counter = 1;
        long long ans=0;
        for (int i = 0; i < start; ++i) {
            ans += counter * (s % 10);
            s /= 10;
            counter *= 10;
        }
        counter = std::pow(10, finish);
        for (int i = start; i <= finish; ++i) {
            ans += counter * (s % 10);
            s /= 10;
            counter /= 10;
        }
        counter = std::pow(10, finish + 1);
        for (int i = finish + 1; i < size; ++i) {
            ans += counter * (s % 10);
            s /= 10;
            counter *= 10;
        }
        return ans;
    }
     
    void BFS_2(size_t n, long long first, long long second) {
        std::unordered_set<long long> dist_first;
        std::unordered_set<long long> dist_second;
        dist_first.insert(first);
        dist_second.insert(second);
        std::queue<long long> q1;
        q1.push(first);
        std::queue<long long> q2;
        q2.push(second);
        int iterations = 0;
        int q1_size = 1;
        int q2_size = 1;
        while (true) {
            int count1 = 0;
            q1_size = q1.size();
            for (int i = 0; i < q1_size; ++i) {
                long long curr_perem = q1.front();
                q1.pop();
                for (int start = 0; start < n - 1; ++start) {
                    for (int finish = start + 1; finish < n; ++finish) {
                        long long new_perem = reverse(n, curr_perem, start, finish);
                        if (dist_first.find(new_perem) == dist_first.end()) {
                            dist_first.insert(new_perem);
                            q1.push(new_perem);
                            ++count1;
                        }
                        if (dist_second.find(new_perem) != dist_second.end()) { 
                            std::cout<< 2* iterations + 1;
                            return;
                        }
                    }
                }
            }
            int count2 = 0;
            q2_size = q2.size();
            for (int i = 0; i < q2_size; ++i) {
                long long curr_perem = q2.front();
                q2.pop();
                for (int start = 0; start < n - 1; ++start) {
                    for (int finish = start + 1; finish < n; ++finish) {
                        long long new_perem = reverse(n, curr_perem, start, finish);
                        if (dist_second.find(new_perem) == dist_second.end()) {
                            dist_second.insert(new_perem);
                            if (dist_first.find(new_perem) != dist_first.end()) {
                                std::cout<< 2 * iterations + 2;
                                return;
                            }
                            q2.push(new_perem);
                            ++count2;
                        }
                    }
                }
            }
            iterations+=1;
        }
    }
     
     
    int main() {
        int lenght;
        std::cin >> lenght;
        int input;
        long long peremutation_1 = 0;
        for (int i = 0; i < lenght; ++i) {
            std::cin >> input;
            --input;
            peremutation_1 *= 10;
            peremutation_1 += input;
        }
        long long peremutation_2 = 0;
        for (int i = 0; i < lenght; ++i) {
            std::cin >> input;
            --input;
            peremutation_2 *= 10;
            peremutation_2 += input;
        }
        if (peremutation_1 == peremutation_2) {
            std::cout << "0";
        }
        else {
            BFS_2(lenght, peremutation_1, peremutation_2);
        }
    }
