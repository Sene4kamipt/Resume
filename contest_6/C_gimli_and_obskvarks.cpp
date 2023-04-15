    #include<iostream>
    #include<vector>
     
    std::vector<std::vector<int64_t>> multiplication(std::vector<std::vector<int64_t>>& first,
        std::vector<std::vector<int64_t>>& second) {
        std::vector<std::vector<int64_t>> answer(first.size());
        for (int64_t i = 0; i < first.size(); ++i) {
            for (int64_t j = 0; j < first.size(); ++j) {
                answer[i].push_back(0);
                for (int64_t k = 0; k < first.size(); ++k) {
                    answer[i][j] = (answer[i][j] + (first[i][k] * second[k][j]) % 1'000'000'007) % 1'000'000'007;
                }
            }
        }
        return answer;
    }
     
    std::vector<std::vector<int64_t>> fast_power(std::vector<std::vector<int64_t>>& A, int64_t power) {
        if (power == 1) {
            return A;
        }
        std::vector<std::vector<int64_t>> answer = fast_power(A, power / 2);
        if (power % 2 == 0) {
            return multiplication(answer, answer);
        }
        answer = multiplication(answer, answer);
        return multiplication(A, answer);
    }
     
    int main() {
        std::ios::sync_with_stdio(0);
        std::cin.tie(0);
        std::cout.tie(0);
        int64_t size_of_level, number_of_levels, capacity, input;
        std::cin >> size_of_level >> number_of_levels >> capacity;
        std::vector<int64_t> entrance(size_of_level,0);
        for (int64_t i = 0; i < size_of_level; ++i) {
            std::cin >> input;
            entrance[i] = input;
        }
        std::vector<int64_t> middle(size_of_level,0);
        for (int64_t i = 0; i < size_of_level; ++i) {
            std::cin >> input;
            middle[i] = input;
        }
        std::vector<int64_t> exit(size_of_level,0);
        for (int64_t i = 0; i < size_of_level; ++i) {
            std::cin >> input;
            exit[i] = input;
        }
        //std::cout << "0";
        std::vector<std::vector<int64_t>> number_of_ways(capacity, std::vector<int64_t>(capacity, 0));
        std::vector<std::vector<int64_t>> number_of_ways_copy(capacity, std::vector<int64_t>(capacity, 0));
        for (int64_t i = 0; i < size_of_level; ++i) {
            if (middle[i] % capacity == 0) {
                ++number_of_ways[0][0];
            }
            else {
                ++number_of_ways[0][capacity-(middle[i] % capacity)];
            }
            if ((middle[i] + exit[i]) % capacity == 0) {
                ++number_of_ways_copy[0][0];
            }
            else {
                ++number_of_ways_copy[0][capacity-(middle[i] + exit[i]) % capacity];
            }
        }
     
        for (int64_t i = 1; i < capacity; ++i) {
            number_of_ways[i][0] = number_of_ways[i - 1][capacity - 1];
            number_of_ways_copy[i][0] = number_of_ways_copy[i - 1][capacity - 1];
            for (int64_t j = 1; j < capacity; ++j) {
                number_of_ways[i][j] = number_of_ways[i - 1][j - 1];
                number_of_ways_copy[i][j] = number_of_ways_copy[i - 1][j - 1];
            }
        }
        if (number_of_levels == 2) {
            number_of_ways = number_of_ways_copy;
        }
        else {
            number_of_ways = fast_power(number_of_ways, number_of_levels - 2);
            number_of_ways = multiplication(number_of_ways_copy,number_of_ways);
        }
        std::vector<int64_t> start(capacity,0);
        for (int64_t i = 0; i < size_of_level; ++i) {
            start[entrance[i] % capacity] += 1;
        }
        //std::cout << "1";
        int64_t ans=0;
        for (int64_t i = 0; i < capacity; ++i) {
            ans += (number_of_ways[0][i] * start[i]) % 1'000'000'007;
            ans %= 1'000'000'007;
        }
     
        std::cout << ans%1'000'000'007;
    }
